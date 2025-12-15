#include "Listas.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

Playlist::Playlist() {
    //ctor
    _idPlaylist = 0;
    _nombre[0] = '\0';
    _idSuscriptorCreador = 0;
    _estado = true;
}

Playlist::~Playlist() {
    //dtor
}

void Playlist::setIdPlaylist(int id) { _idPlaylist = id; }

void Playlist::setNombre(const char* n) {
    strcpy(_nombre, n);
}

void Playlist::setIdSuscriptorCreador(int id) { _idSuscriptorCreador = id; }
void Playlist::setEstado(bool estado) { _estado = estado; }

int Playlist::getIdPlaylist() { return _idPlaylist; }
const char* Playlist::getNombre() { return _nombre; }
int Playlist::getIdSuscriptorCreador() { return _idSuscriptorCreador; }
bool Playlist::getEstado() { return _estado; }

void Playlist::Cargar() {
    std::cout << "Nombre de la Playlist: ";
    std::cin.ignore();
    std::cin.getline(_nombre, 50);
    _estado = true;
}

void Playlist::Mostrar() {
    if (_estado) {
        std::cout << "ID Lista: " << _idPlaylist << " | Nombre: " << _nombre << std::endl;
        std::cout << "Creada por ID Usuario: " << _idSuscriptorCreador << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

Listas::Listas() {
    //ctor
    cantidad = 0;
}

void Listas::agregarPlaylist(const char* nombre, int idCreador) {
    if (cantidad >= 100) {
        cout << "No se pueden agregar más playlists." << endl;
        return;
    }

    Playlist nueva;
    nueva.setIdPlaylist(cantidad + 1);
    nueva.setNombre(nombre);
    nueva.setIdSuscriptorCreador(idCreador);
    nueva.setEstado(true);

    listas[cantidad] = nueva;
    cantidad++;

    cout << "Playlist creada con exito (ID: " << cantidad << ")." << endl;
}

void Listas::mostrarPlaylists() {
    if (cantidad == 0) {
        // Carga diferida (Lazy Loading): Solo lee del disco si la memoria esta vacia
        FILE *p = fopen("playlists.dat", "rb");
        if (p) {
            Playlist reg;
            while(fread(&reg, sizeof(Playlist), 1, p) && cantidad < 100) {
                listas[cantidad] = reg;
                cantidad++;
            }
            fclose(p);
        }
    }

    if (cantidad == 0) {
        cout << "No hay playlists cargadas." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        listas[i].Mostrar();
    }
}

void Listas::mostrarMisPlaylists(int idCreador) {
    if (cantidad == 0) {
        FILE *p = fopen("playlists.dat", "rb");
        if (p) {
            Playlist reg;
            while(fread(&reg, sizeof(Playlist), 1, p) && cantidad < 100) {
                listas[cantidad] = reg;
                cantidad++;
            }
            fclose(p);
        }
    }

    bool hay = false;
    cout << "--- MIS PLAYLISTS ---" << endl;
    for (int i = 0; i < cantidad; i++) {
        if (listas[i].getIdSuscriptorCreador() == idCreador && listas[i].getEstado()) {
            listas[i].Mostrar();
            hay = true;
        }
    }
    if (!hay) cout << "No tenes playlists creadas." << endl;
}

int Listas::buscarPlaylist(const char* nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(listas[i].getNombre(), nombre) == 0) {
            return i;
        }
    }
    return -1;
}

bool Listas::eliminarPlaylist(const char* nombre) {
    int pos = buscarPlaylist(nombre);
    if (pos == -1) {
        cout << "Playlist no encontrada." << endl;
        return false;
    }

    listas[pos].setEstado(false);
    cout << "Playlist eliminada (baja logica)." << endl;
    return true;
}
