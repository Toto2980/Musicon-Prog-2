#include "Listas.h"


Listas::Listas() {
    cantidad = 0;
}

void Listas::agregarPlaylist(const char* nombre, const char* creador) {
    if (cantidad >= 100) {
        cout << "No se pueden agregar más playlists (límite alcanzado)." << endl;
        return;
    }

    strcpy(listas[cantidad].nombre, nombre);
    strcpy(listas[cantidad].creador, creador);
    cantidad++;

    cout << "Playlist fue agregada correctamente." << endl;
}


void Listas::mostrarPlaylists() const {
    if (cantidad == 0) {
        cout << "No hay playlists cargadas." << endl;
        return;
    }

    cout << "\n--- LISTA DE PLAYLISTS ---" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << "Nombre: " << listas[i].nombre << endl;
        cout << "Creador: " << listas[i].creador << endl;
        cout << "-------------------------" << endl;
    }
}


int Listas::buscarPlaylist(const char* nombre) const {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(listas[i].nombre, nombre) == 0) {
            return i; 
        }
    }
    return -1;
}


bool Listas::eliminarPlaylist(const char* nombre) {
    int pos = buscarPlaylist(nombre);
    if (pos == -1) return false;


    for (int i = pos; i < cantidad - 1; i++) {
        listas[i] = listas[i + 1];
    }
    cantidad--;

    cout << "Playlist eliminada correctamente." << endl;
    return true;
}
