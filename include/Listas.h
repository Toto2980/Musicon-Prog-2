#ifndef LISTAS_H
#define LISTAS_H

#include <iostream>
#include <cstring>
using namespace std;

class Playlist {
private:
    int _idPlaylist;
    char _nombre[50];
    int _idSuscriptorCreador;
    bool _estado;

public:
    Playlist();
    virtual ~Playlist();

    void setIdPlaylist(int id);
    void setNombre(const char* n);
    void setIdSuscriptorCreador(int id);
    void setEstado(bool estado);

    int getIdPlaylist();
    const char* getNombre();
    int getIdSuscriptorCreador();
    bool getEstado();

    void Cargar();
    void Mostrar();
};

class Listas {
private:
    Playlist listas[100];
    int cantidad;

public:
    Listas();

    void agregarPlaylist(const char* nombre, int idCreador);
    void mostrarPlaylists();
    int buscarPlaylist(const char* nombre);
    bool eliminarPlaylist(const char* nombre);
};

#endif // LISTAS_H
