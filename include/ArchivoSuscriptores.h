#ifndef ARCHIVOSUSCRIPTORES_H
#define ARCHIVOSUSCRIPTORES_H

#include "Suscriptor.h"
#include <string>

/** Clase para manejar la persistencia de suscriptores en archivo binario. */
class ArchivoSuscriptores {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoSuscriptores. Parámetros: nombreArchivo - Nombre del archivo, por defecto "suscriptores.dat". */
        ArchivoSuscriptores(std::string nombreArchivo = "suscriptores.dat");

        /** Guarda un suscriptor en el archivo. Parámetros: reg - Suscriptor a guardar. Retorna: true si guardado, false error. */
        bool Guardar(Suscriptor reg);
        /** Lee un suscriptor desde el archivo en la posición especificada. Parámetros: pos - Posición. Retorna: El suscriptor leído. */
        Suscriptor Leer(int pos);
        /** Lee todos los suscriptores del archivo. Parámetros: cantidad - Referencia para almacenar la cantidad leída. Retorna: Arreglo de suscriptores. */
        Suscriptor* LeerTodos(int &cantidad);
        /** Genera un nuevo ID único para un suscriptor. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Busca la posición de un suscriptor por su ID. Parámetros: id - ID del suscriptor. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Modifica un suscriptor en el archivo. Parámetros: pos - Posición a modificar, reg - Nuevo suscriptor. Retorna: true si modificado, false error. */
        bool Modificar(int pos, Suscriptor reg);
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de suscriptores. */
        int ObtenerCantidadRegistros();

        // Búsquedas específicas de este dominio
        /** Busca la posición de un suscriptor por su nombre. Parámetros: nombre - Nombre del suscriptor. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicionPorNombre(const char* nombre);
        /** Busca la posición de un suscriptor por su DNI. Parámetros: dni - DNI del suscriptor. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicionPorDNI(const char* dni);
};

#endif // ARCHIVOSUSCRIPTORES_H
