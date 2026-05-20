#ifndef ARCHIVOGENEROS_H
#define ARCHIVOGENEROS_H

#include "Generos.h"
#include <string>

/** Clase para manejar la persistencia de géneros en archivo binario. */
class ArchivoGeneros {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoGeneros. Parámetros: nombreArchivo - Nombre del archivo, por defecto "generos.dat". */
        ArchivoGeneros(std::string nombreArchivo = "generos.dat");

        /** Guarda un género en el archivo. Parámetros: reg - Género a guardar. Retorna: true si guardado, false error. */
        bool Guardar(Genero reg);
        /** Lee un género desde el archivo en la posición especificada. Parámetros: pos - Posición. Retorna: El género leído. */
        Genero Leer(int pos);
        /** Busca la posición de un género por su ID. Parámetros: id - ID del género. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Busca el ID de un género por su nombre. Parámetros: nombre - Nombre del género. Retorna: ID, -1 si no encontrado. */
        int BuscarIDPorNombre(const char* nombre);
        /** Genera un nuevo ID único para un género. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de géneros. */
        int ObtenerCantidadRegistros();
        /** Busca un género por su ID. Parámetros: id - ID del género. Retorna: El género encontrado. */
        Genero BuscarPorID(int id);

        // NUEVO: El Cerebro "Buscar o Crear"
        /** Busca un género por nombre, o lo crea si no existe. Parámetros: nombreGenero - Nombre del género. Retorna: ID del género. */
        int BuscarOCrear(std::string nombreGenero);
};

#endif // ARCHIVOGENEROS_H
