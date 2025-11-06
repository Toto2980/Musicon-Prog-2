#ifndef LISTAS_H
#define LISTAS_H

#include <iostream>
#include <cstring>
using namespace std;

class Playlist {
private:
    int idLista;
    char nombre[50];
    int idSuscriptorCreador;
    bool _estado;
    int idPlaylist;
    int idCancion;

public:
    Playlist();
    virtual ~Playlist();

    void setIdLista(int id);
    void setNombre(const char* n);
    void setIdSuscriptorCreador(int id);
    void setEstado(bool estado);
    void setIdPlaylist(int id);
    void setIdCancion(int id);

    int getIdLista();
    const char* getNombre();
    int getIdSuscriptorCreador();
    bool getEstado();
    int getIdPlaylist();
    int getIdCancion();


    void mostrar() {
        cout << "ID Lista: " << idLista
             << " | Nombre: " << nombre
             << " | ID Creador: " << idSuscriptorCreador
             << " | Estado: " << (_estado ? "Activo" : "Inactivo")
             << " | ID Playlist: " << idPlaylist
             << " | ID Canción: " << idCancion
             << endl;
    }
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
