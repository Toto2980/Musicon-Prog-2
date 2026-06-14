/**
 * Este archivo define la clase Genero, que representa un género musical en el sistema Musicon.
 * Contiene atributos como ID, nombre y estado. Incluye métodos para persistencia
 * en archivo binario y búsquedas por nombre/ID.
 */

#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include "EntidadPadre.h"

/** Representa un género musical con atributos como ID, nombre y estado. Incluye métodos para persistencia en archivo binario. */
class Genero : public EntidadPadre {
    private:
        char _nombre[50]; // Nombre del género musical
        bool _estado; // Estado activo/inactivo

    public:
        /** Constructor con parámetros opcionales.
         * Parámetros: id - ID único (por defecto 0), nombre - Nombre del género (por defecto vacío), estado - Estado activo (por defecto true).
         */
        Genero(int id = 0, const char* nombre = "", bool estado = true);

        // --- SETTERS ---
        /** Establece el ID del género.
         * Parámetros: id - ID único.
         */
        void setIdGeneros(int id);

        /** Establece el nombre del género.
         * Parámetros: nombre - Cadena con el nombre.
         */
        void setNombre(const char* nombre);

        /** Establece el estado activo/inactivo.
         * Parámetros: estado - true para activo, false para inactivo.
         */
        void setEstado(bool estado);

        // --- GETTERS ---
        /** Obtiene el ID del género.
         * Retorna: ID único.
         */
        int getIdGeneros() const;

        /** Obtiene el nombre del género.
         * Retorna: Puntero a la cadena del nombre.
         */
        const char* getNombre();

        /** Obtiene el estado activo/inactivo.
         * Retorna: true si activo, false si inactivo.
         */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        /** Solicita al usuario los datos del género. */
        void Cargar();

        /** Muestra los datos del género en la consola (const para no modificar). */
        void Mostrar() const;

        // --- PERSISTENCIA ---
        /** Guarda el género en el archivo binario (agrega al final).
         * Retorna: true si se guardó correctamente, false en caso de error.
         */
        bool Guardar();

        /** Lee un género desde el archivo binario en la posición especificada.
         * Parámetros: pos - Posición en el archivo (basado en 0).
         * Retorna: true si se leyó correctamente, false en caso de error.
         */
        bool Leer(int pos);

        /** Modifica un género en el archivo binario en la posición especificada. Parámetros: pos - Posición a modificar. Retorna: true si se modificó correctamente, false en caso de error. */
        bool Modificar(int pos);

        /** Obtiene la cantidad total de registros (géneros) en el archivo. Retorna: Número de géneros guardados. */
        int ObtenerCantidadRegistros();

        /** Busca el ID de un género por su nombre (comparación insensible a mayúsculas). Parámetros: nombre - Nombre a buscar. Retorna: ID del género si se encuentra, -1 si no. */
        int BuscarIDPorNombre(const char* nombre);

        /** Busca la posición en el archivo de un género por su ID. Parámetros: id - ID del género a buscar. Retorna: Posición en el archivo o -1 si no se encuentra. */
        int BuscarPosicionPorID(int id);
};

#endif // GENEROS_H_INCLUDED
