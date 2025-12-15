#ifndef DETALLEPLAYLIST_H
#define DETALLEPLAYLIST_H

#include "Fecha.h"

// CLASE DE ASOCIACION (Link)
// Resuelve la relación Muchos a Muchos entre Playlists y Canciones.
class DetallePlaylist {
    private:
        int _idPlaylist;
        int _idCancion;
        Fecha _fechaAgregado;
        bool _estado;

    public:
        DetallePlaylist();

        // --- SETTERS ---
        void setIdPlaylist(int id);
        void setIdCancion(int id);
        void setFechaAgregado(Fecha f);
        void setEstado(bool e);

        // --- GETTERS ---
        int getIdPlaylist();
        int getIdCancion();
        Fecha getFechaAgregado();
        bool getEstado();

        // --- E/S ---
        void Cargar();
        void Mostrar();
};

#endif // DETALLEPLAYLIST_H
