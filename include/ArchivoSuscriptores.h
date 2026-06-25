#ifndef ARCHIVOSUSCRIPTORES_H
#define ARCHIVOSUSCRIPTORES_H

#include "Suscriptor.h"
#include <string>

/** Clase para manejar la persistencia de suscriptores en archivo binario. */
class ArchivoSuscriptores {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoSuscriptores. Parametros: nombreArchivo - Nombre del archivo, por defecto "suscriptores.dat". */
        ArchivoSuscriptores(std::string nombreArchivo = "suscriptores.dat");

        /** Guarda un suscriptor en el archivo. Parametros: reg - Suscriptor a guardar. Retorna: true si guardado, false error. */
        bool Guardar(Suscriptor reg);
        /** Lee un suscriptor desde el archivo en la posicion especificada. Parametros: pos - Posicion. Retorna: El suscriptor leido. */
        Suscriptor Leer(int pos);
        /** Lee todos los suscriptores del archivo. Parametros: cantidad - Referencia para almacenar la cantidad leida. Retorna: Arreglo de suscriptores. */
        Suscriptor* LeerTodos(int &cantidad);
        /** Genera un nuevo ID unico para un suscriptor. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Busca la posicion de un suscriptor por su ID. Parametros: id - ID del suscriptor. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Modifica un suscriptor en el archivo. Parametros: pos - Posicion a modificar, reg - Nuevo suscriptor. Retorna: true si modificado, false error. */
        bool Modificar(int pos, Suscriptor reg);
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de suscriptores. */
        int ObtenerCantidadRegistros();

        // Busquedas especificas de este dominio
        /** Busca la posicion de un suscriptor por su nombre. Parametros: nombre - Nombre del suscriptor. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicionPorNombre(const char* nombre);
        /** Busca la posicion de un suscriptor por su DNI. Parametros: dni - DNI del suscriptor. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicionPorDNI(const char* dni);
};

#endif // ARCHIVOSUSCRIPTORES_H
