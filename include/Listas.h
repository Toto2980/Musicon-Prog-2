#ifndef LISTAS_H
#define LISTAS_H

#include <iostream>
#include <cstring>
using namespace std;

struct Playlist {
    char nombre[50];
    char creador[50];
};


class Listas {
private:
    Playlist listas[100];
    int cantidad;

public:

    Listas();

    void agregarPlaylist(const char* nombre, const char* creador);
    void mostrarPlaylists();
    int buscarPlaylist(const char* nombre);
    bool eliminarPlaylist(const char* nombre);
};

#endif
