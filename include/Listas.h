#ifndef LISTAS_H
#define LISTAS_H

#include <iostream>
#include <cstring>
using namespace std;

// ENTIDAD: PLAYLIST
// Define los metadatos de la lista (Nombre, Dueño), no el contenido.
class Playlist {
    private:
        int _idPlaylist;
        char _nombre[50];
        int _idSuscriptorCreador; // Usuario dueño
        bool _estado;

    public:
        Playlist();
        virtual ~Playlist();

        // --- SETTERS ---
        void setIdPlaylist(int id);
        void setNombre(const char* n);
        void setIdSuscriptorCreador(int id);
        void setEstado(bool estado);

        // --- GETTERS ---
        int getIdPlaylist();
        const char* getNombre();
        int getIdSuscriptorCreador();
        bool getEstado();

        void Cargar();
        void Mostrar();
};

// CLASE GESTORA (Manager)
class Listas {
    private:
        Playlist listas[100];
        int cantidad;

    public:
        Listas();

        void agregarPlaylist(const char* nombre, int idCreador);
        void mostrarPlaylists(); // Muestra todas
        void mostrarMisPlaylists(int idCreador); // Filtra por usuario logueado
        int buscarPlaylist(const char* nombre);
        bool eliminarPlaylist(const char* nombre);
};

#endif // LISTAS_H
