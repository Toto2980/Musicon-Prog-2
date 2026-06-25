#ifndef ARCHIVOGENEROS_H
#define ARCHIVOGENEROS_H

#include "Generos.h"
#include <string>

/** Clase para manejar la persistencia de generos en archivo binario. */
class ArchivoGeneros {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoGeneros. Parametros: nombreArchivo - Nombre del archivo, por defecto "generos.dat". */
        ArchivoGeneros(std::string nombreArchivo = "generos.dat");

        /** Guarda un genero en el archivo. Parametros: reg - Genero a guardar. Retorna: true si guardado, false error. */
        bool Guardar(Genero reg);
        /** Lee un genero desde el archivo en la posicion especificada. Parametros: pos - Posicion. Retorna: El genero leido. */
        Genero Leer(int pos);
        /** Busca la posicion de un genero por su ID. Parametros: id - ID del genero. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Busca el ID de un genero por su nombre. Parametros: nombre - Nombre del genero. Retorna: ID, -1 si no encontrado. */
        int BuscarIDPorNombre(const char* nombre);
        /** Genera un nuevo ID unico para un genero. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de generos. */
        int ObtenerCantidadRegistros();
        /** Busca un genero por su ID. Parametros: id - ID del genero. Retorna: El genero encontrado. */
        Genero BuscarPorID(int id);

        /** Modifica el genero en la posicion indicada. Parametros: pos - Posicion, reg - Genero con datos nuevos. Retorna: true si OK. */
        bool Modificar(int pos, Genero reg);

        // NUEVO: El Cerebro "Buscar o Crear"
        /** Busca un genero por nombre, o lo crea si no existe. Parametros: nombreGenero - Nombre del genero. Retorna: ID del genero. */
        int BuscarOCrear(std::string nombreGenero);
};

#endif // ARCHIVOGENEROS_H
