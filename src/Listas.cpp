#include "Listas.h"

Playlist::Playlist() {
    idLista = 0;
    nombre[0] = '\0';
    idSuscriptorCreador = 0;
    _estado = true;
    idPlaylist = 0;
    idCancion = 0;
}

Playlist::~Playlist() { }

void Playlist::setIdLista(int id) {
    idLista = id;
}

void Playlist::setNombre(const char* n) {
    strcpy(nombre, n);
}

void Playlist::setIdSuscriptorCreador(int id) {
    idSuscriptorCreador = id;
}

void Playlist::setEstado(bool estado) {
    _estado = estado;
}

void Playlist::setIdPlaylist(int id) {
    idPlaylist = id;
}

void Playlist::setIdCancion(int id) {
    idCancion = id;
}

int Playlist::getIdLista() { return idLista; }
const char* Playlist::getNombre() { return nombre; }
int Playlist::getIdSuscriptorCreador() { return idSuscriptorCreador; }
bool Playlist::getEstado() { return _estado; }
int Playlist::getIdPlaylist() { return idPlaylist; }
int Playlist::getIdCancion() { return idCancion; }


Listas::Listas() {
    cantidad = 0;
}

void Listas::agregarPlaylist(const char* nombre, int idCreador) {
    if (cantidad >= 100) {
        cout << "No se pueden agregar más playlists." << endl;
        return;
    }

    Playlist nueva;
    nueva.setIdLista(cantidad + 1);
    nueva.setNombre(nombre);
    nueva.setIdSuscriptorCreador(idCreador);
    nueva.setEstado(true);

    listas[cantidad] = nueva;
    cantidad++;

    cout << "Playlist agregada con éxito." << endl;
}

void Listas::mostrarPlaylists() {
    if (cantidad == 0) {
        cout << "No hay playlists cargadas." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        listas[i].mostrar();
    }
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

    cout << "Playlist eliminada (baja lógica)." << endl;
    return true;
}
