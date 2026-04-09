/**
 * Este archivo define la clase Suscriptor, que representa a un usuario suscriptor en el sistema Musicon.
 * Guarda directamente nombre, estado, DNI, apellido, email y fecha de nacimiento.
 */

#ifndef SUSCRIPTOR_H
#define SUSCRIPTOR_H

#include <cstring>
#include "Fecha.h"

/** Representa a un usuario suscriptor del sistema. */
class Suscriptor {
    private:
        char _nombre[100];
        bool _estado;
        int _idSuscriptor;
        char _dni[15];
        char _apellido[50];
        char _email[100];
        Fecha _fechaNacimiento;

    public:
        /** Constructor por defecto: Inicializa todos los atributos con valores neutros. */
        Suscriptor();

        /** Destructor de la clase Suscriptor. */
        ~Suscriptor();

        /** Establece el nombre del suscriptor. Parámetros: nombre - Nombre a guardar. */
        void setNombre(const char* nombre) {
            if (nombre == nullptr) {
                _nombre[0] = '\0';
                return;
            }
            std::strncpy(_nombre, nombre, sizeof(_nombre) - 1);
            _nombre[sizeof(_nombre) - 1] = '\0';
        }

        /** Establece el estado del suscriptor. Parámetros: estado - true si está activo. */
        void setEstado(bool estado) { _estado = estado; }

        /** Establece el ID del suscriptor. Parámetros: id - ID único. */
        void setIdSuscriptor(int id);
        /** Establece el DNI del suscriptor. Parámetros: dni - Cadena con el DNI. */
        void setDni(const char* dni);
        /** Establece el apellido del suscriptor. Parámetros: apellido - Cadena con el apellido. */
        void setApellido(const char* apellido);
        /** Establece el email del suscriptor. Parámetros: email - Cadena con el email. */
        void setEmail(const char* email);
        /** Establece la fecha de nacimiento del suscriptor. Parámetros: fecha - Objeto Fecha con la fecha. */
        void setFechaNacimiento(Fecha fecha);

        /** Obtiene el nombre del suscriptor. Retorna: Nombre del suscriptor. */
        const char* getNombre() { return _nombre; }
        /** Obtiene el estado del suscriptor. Retorna: true si está activo. */
        bool getEstado() { return _estado; }
        /** Obtiene el ID del suscriptor. Retorna: ID único. */
        int getIdSuscriptor();
        /** Obtiene el DNI del suscriptor. Retorna: Puntero a la cadena del DNI. */
        const char* getDni();
        /** Obtiene el apellido del suscriptor. Retorna: Puntero a la cadena del apellido. */
        const char* getApellido();
        /** Obtiene el email del suscriptor. Retorna: Puntero a la cadena del email. */
        const char* getEmail();
        /** Obtiene la fecha de nacimiento del suscriptor. Retorna: Objeto Fecha con la fecha. */
        Fecha getFechaNacimiento();

        /** Carga los datos del suscriptor desde la entrada del usuario. */
        void Cargar();
        /** Muestra los datos del suscriptor en la consola. */
        void Mostrar();
};

#endif // SUSCRIPTOR_H
