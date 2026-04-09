/*
 * Archivo: Canciones.h
 * Descripci�n: Header de la clase Canciones, que representa la entidad de una canci�n en el sistema Musicon.
 * Contiene los atributos de una canci�n y m�todos para cargar/mostrar datos desde/hacia el usuario.
 * No maneja persistencia directamente, solo mantiene los datos en memoria.
 */

#ifndef CANCIONES_H
#define CANCIONES_H

#include <string>

/**
 * Este archivo define la clase Canciones, que representa una canción en el sistema Musicon.
 * Mantiene datos como nombre, álbum, género y duración. No maneja persistencia, solo datos en memoria.
 */

/** Representa una canción en el sistema Musicon con atributos como nombre, álbum, género, duración y estado. */
class Canciones {
    private:
        int _idCancion; // Identificador �nico de la canci�n
        char _nombre[100]; // Nombre o t�tulo de la canci�n
        int _idAlbum; // ID del �lbum al que pertenece
        int _idGenero; // ID del g�nero musical
        int _duracionSegundos; // Duraci�n en segundos
        bool _estado; // Estado activo/inactivo (para eliminaci�n l�gica)

    public:
        /** Constructor por defecto de la clase Canciones. */
        Canciones();
        /** Destructor virtual de la clase Canciones. */
        virtual ~Canciones();

        // --- SETTERS ---
        /** Establece el ID de la canción.
         * Parámetros: id - El ID único.
         */
        void setIdCancion(int id);

        /** Establece el nombre de la canción.
         * Parámetros: nombre - Cadena con el nombre.
         */
        void setNombre(const char* nombre);

        /** Establece el ID del álbum.
         * Parámetros: idAl - ID del álbum.
         */
        void setIdAlbum(int idAl);

        /** Establece el ID del género.
         * Parámetros: idGe - ID del género.
         */
        void setIdGenero(int idGe);

        /** Establece la duración en segundos.
         * Parámetros: duracion - Duración en segundos.
         */
        void setDuracionSegundos(int duracion);

        /** Establece el estado activo/inactivo.
         * Parámetros: e - true para activo, false para inactivo.
         */
        void setEstado(bool e);

        // --- GETTERS ---
        /** Obtiene el ID de la canción.
         * Retorna: El ID único.
         */
        int getIdCancion();

        /** Obtiene el nombre de la canción.
         * Retorna: Puntero a la cadena del nombre.
         */
        const char* getNombre();

        /** Obtiene el ID del álbum.
         * Retorna: ID del álbum.
         */
        int getIdAlbum();

        /** Obtiene el ID del género.
         * Retorna: ID del género.
         */
        int getIdGenero();

        /** Obtiene la duración en segundos.
         * Retorna: Duración en segundos.
         */
        int getDuracionSegundos();

        /** Obtiene el estado activo/inactivo.
         * Retorna: true si activo, false si inactivo.
         */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        // Nota: Mantenemos esto aqu� por ahora, pero idealmente ir�a en una "Vista"
        /** Carga los datos de la canción desde la entrada del usuario. */
        void Cargar();

        /** Muestra los datos de la canción en la consola. */
        void Mostrar();
};

#endif // CANCIONES_H
