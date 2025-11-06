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

    Playlist(int idL = 0, const char* n = "", int idCreador = 0, bool est = true, int idP = 0, int idCan = 0) {
        idLista = idL;
        strcpy(nombre, n);
        idSuscriptorCreador = idCreador;
        _estado = est;
        idPlaylist = idP;
        idCancion = idCan;
    }

    void setIdLista(int id) { idLista = id; }
    void setNombre(const char* n) { strcpy(nombre, n); }
    void setIdSuscriptorCreador(int id) { idSuscriptorCreador = id; }
    void setEstado(bool e) { _estado = e; }
    void setIdPlaylist(int id) { idPlaylist = id; }
    void setIdCancion(int id) { idCancion = id; }

    int getIdLista() { return idLista; }
    const char* getNombre() { return nombre; }
    int getIdSuscriptorCreador() { return idSuscriptorCreador; }
    bool getEstado() { return _estado; }
    int getIdPlaylist() { return idPlaylist; }
    int getIdCancion() { return idCancion; }


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
