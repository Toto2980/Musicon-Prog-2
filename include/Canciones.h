/*
 * Archivo: Canciones.h
 * Descripcion: Header de la clase Canciones, que representa la entidad de una cancion en el sistema Musicon.
 * Contiene los atributos de una cancion y metodos para cargar/mostrar datos desde/hacia el usuario.
 * No maneja persistencia directamente, solo mantiene los datos en memoria.
 */

#ifndef CANCIONES_H
#define CANCIONES_H

#include <string>
 #include "EntidadPadre.h"

/**
 * Este archivo define la clase Canciones, que representa una cancion en el sistema Musicon.
 * Mantiene datos como nombre, album, genero y duracion. No maneja persistencia, solo datos en memoria.
 */

/** Representa una cancion en el sistema Musicon con atributos como nombre, album, genero, duracion y estado. */
class Canciones : public EntidadPadre {
    private:
        char _nombre[100]; // Nombre o titulo de la cancion
        int _idAlbum; // ID del album al que pertenece
        int _idGenero; // ID del genero musical
        int _duracionSegundos; // Duracion en segundos
        bool _estado; // Estado activo/inactivo (para eliminacion logica)

    public:
        /** Constructor por defecto de la clase Canciones. */
        Canciones();

        // --- SETTERS ---
        /** Establece el ID de la cancion.
         * Parametros: id - El ID unico.
         */
        void setIdCancion(int id);

        /** Establece el nombre de la cancion.
         * Parametros: nombre - Cadena con el nombre.
         */
        void setNombre(const char* nombre);

        /** Establece el ID del album.
         * Parametros: idAl - ID del album.
         */
        void setIdAlbum(int idAl);

        /** Establece el ID del genero.
         * Parametros: idGe - ID del genero.
         */
        void setIdGenero(int idGe);

        /** Establece la duracion en segundos.
         * Parametros: duracion - Duracion en segundos.
         */
        void setDuracionSegundos(int duracion);

        /** Establece el estado activo/inactivo.
         * Parametros: e - true para activo, false para inactivo.
         */
        void setEstado(bool e);

        // --- GETTERS ---
        /** Obtiene el ID de la cancion.
         * Retorna: El ID unico.
         */
        int getIdCancion();

        /** Obtiene el nombre de la cancion.
         * Retorna: Puntero a la cadena del nombre.
         */
        const char* getNombre();

        /** Obtiene el ID del album.
         * Retorna: ID del album.
         */
        int getIdAlbum();

        /** Obtiene el ID del genero.
         * Retorna: ID del genero.
         */
        int getIdGenero();

        /** Obtiene la duracion en segundos.
         * Retorna: Duracion en segundos.
         */
        int getDuracionSegundos();

        /** Obtiene el estado activo/inactivo.
         * Retorna: true si activo, false si inactivo.
         */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        // Nota: Mantenemos esto aque por ahora, pero idealmente iria en una "Vista"
        /** Carga los datos de la cancion desde la entrada del usuario. */
        void Cargar();

        /** Muestra los datos de la cancion en la consola. */
        void Mostrar();
};

#endif // CANCIONES_H
