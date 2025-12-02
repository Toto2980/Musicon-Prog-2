#include "Listas.h"

// --- CLASE PLAYLIST ---

Playlist::Playlist() {
    _idPlaylist = 0;
    _nombre[0] = '\0';
    _idSuscriptorCreador = 0;
    _estado = true;
}

Playlist::~Playlist() { }

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
    cout << "ID Playlist: ";
    cin >> _idPlaylist;
    
    cout << "Nombre de la Playlist: ";
    cin.ignore(); 
    cin.getline(_nombre, 50);

    cout << "ID del Creador (Suscriptor): ";
    cin >> _idSuscriptorCreador;

    _estado = true;
}

void Playlist::Mostrar() {
    if (_estado) {
        cout << "ID Playlist: " << _idPlaylist
             << " | Nombre: " << _nombre
             << " | ID Creador: " << _idSuscriptorCreador
             << " | Estado: " << (_estado ? "Activo" : "Inactivo")
             << endl;
    }
}

// --- CLASE GESTORA (Listas) ---

Listas::Listas() {
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
        cout << "No hay playlists cargadas." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        listas[i].Mostrar();
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
    cout << "Playlist eliminada (baja logica)." << endl;
    return true;
}


