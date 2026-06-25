/**
 * Este archivo define la clase Genero, que representa un genero musical en el sistema Musicon.
 * Contiene atributos como ID, nombre y estado. Incluye metodos para persistencia
 * en archivo binario y busquedas por nombre/ID.
 */

#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include "EntidadPadre.h"

/** Representa un genero musical con atributos como ID, nombre y estado. Incluye metodos para persistencia en archivo binario. */
class Genero : public EntidadPadre {
    private:
        char _nombre[50]; // Nombre del genero musical
        bool _estado; // Estado activo/inactivo

    public:
        /** Constructor con parametros opcionales.
         * Parametros: id - ID unico (por defecto 0), nombre - Nombre del genero (por defecto vacio), estado - Estado activo (por defecto true).
         */
        Genero(int id = 0, const char* nombre = "", bool estado = true);

        // --- SETTERS ---
        /** Establece el ID del genero.
         * Parametros: id - ID unico.
         */
        void setIdGeneros(int id);

        /** Establece el nombre del genero.
         * Parametros: nombre - Cadena con el nombre.
         */
        void setNombre(const char* nombre);

        /** Establece el estado activo/inactivo.
         * Parametros: estado - true para activo, false para inactivo.
         */
        void setEstado(bool estado);

        // --- GETTERS ---
        /** Obtiene el ID del genero.
         * Retorna: ID unico.
         */
        int getIdGeneros() const;

        /** Obtiene el nombre del genero.
         * Retorna: Puntero a la cadena del nombre.
         */
        const char* getNombre();

        /** Obtiene el estado activo/inactivo.
         * Retorna: true si activo, false si inactivo.
         */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        /** Solicita al usuario los datos del genero. */
        void Cargar();

        /** Muestra los datos del genero en la consola (const para no modificar). */
        void Mostrar() const;
};

#endif // GENEROS_H_INCLUDED
