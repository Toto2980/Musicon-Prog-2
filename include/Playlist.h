#ifndef PLAYLIST_H
#define PLAYLIST_H


#include "Fecha.h" // Necesario para la fecha de creacion
#include "EntidadPadre.h"

/**
 * Este archivo define la clase Playlist, que representa listas de canciones creadas por usuarios.
 * Incluye metodos para guardar, cargar y buscar playlists en archivos.
 */

/** Representa una playlist de canciones creada por un suscriptor. */
class Playlist : public EntidadPadre {
    private:
        char _nombre[50]; /**< Nombre de la playlist */
        int _idSuscriptorCreador; /**< ID del suscriptor que la creo */
        Fecha _fechaCreacion; /**< Fecha de creacion */
        bool _estado; /**< Estado activo/inactivo */

    public:
        /** Constructor por defecto. */
        Playlist();

        // --- SETTERS ---
        /** Establece el ID.
         * Parametros: id - ID unico.
         */
        void setIdPlaylist(int id);
        /** Establece el nombre.
         * Parametros: n - Nombre de la playlist.
         */
        void setNombre(const char* n);
        /** Establece el ID del creador.
         * Parametros: id - ID del suscriptor creador.
         */
        void setIdSuscriptorCreador(int id);
        /** Establece la fecha de creacion.
         * Parametros: f - Fecha de creacion.
         */
        void setFechaCreacion(Fecha f);
        /** Establece el estado.
         * Parametros: estado - true para activo.
         */
        void setEstado(bool estado);

        // --- GETTERS ---
        /** Dice cual es el numero unico de la lista.
         * Retorna: El ID que la identifica.
         */
        int getIdPlaylist();
        /** Dice cual es el nombre de la lista.
         * Retorna: El titulo que el usuario le puso.
         */
        const char* getNombre();
        /** Dice quien creo la lista.
         * Retorna: El ID del usuario que la hizo.
         */
        int getIdSuscriptorCreador();
        /** Dice cuando se creo la lista.
         * Retorna: La fecha y hora de creacion.
         */
        Fecha getFechaCreacion();
        /** Dice si la lista esta disponible para usar.
         * Retorna: Verdadero si se puede acceder a ella.
         */
        bool getEstado();

        /** Pide al usuario que escriba el nombre de la lista. */
        void Cargar();
        /** Muestra la informacion de la lista en la pantalla. */
        void Mostrar();
};

#endif // PLAYLIST_H
