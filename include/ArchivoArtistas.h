#ifndef ARCHIVOARTISTAS_H
#define ARCHIVOARTISTAS_H

#include "Artista.h" // Necesario para usar objetos de tipo Artista
#include <string>

/** Clase para manejar la persistencia de artistas en archivo binario. */
class ArchivoArtistas {
    private:
        std::string _nombreArchivo;

    public:
        // Constructor con valor por defecto
        /** Constructor de ArchivoArtistas. Parámetros: nombreArchivo - Nombre del archivo, por defecto "artistas.dat". */
        ArchivoArtistas(std::string nombreArchivo = "artistas.dat");

        // --- ABML Básico ---
        /** Guarda un artista en el archivo. Parámetros: reg - Artista a guardar. Retorna: true si guardado, false en caso de error. */
        bool Guardar(Artista reg);
        /** Lee un artista desde el archivo en la posición especificada. Parámetros: pos - Posición en el archivo. Retorna: El artista leído. */
        Artista Leer(int pos);
        /** Modifica un artista en el archivo en la posición especificada. Parámetros: pos - Posición a modificar, reg - Nuevo artista. Retorna: true si modificado, false error. */
        bool Modificar(int pos, Artista reg);
        /** Genera un nuevo ID único para un artista. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de artistas. */
        int ObtenerCantidadRegistros();

        // --- Búsquedas ---
        /** Busca la posición de un artista por su ID. Parámetros: id - ID del artista. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Busca la posición de un artista por su nombre. Parámetros: nombre - Nombre del artista. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicionPorNombre(const char* nombre);

        // Devuelve el ID del artista si existe, o -1 si no.
        /** Busca el ID de un artista por su nombre. Parámetros: nombre - Nombre del artista. Retorna: ID del artista, -1 si no existe. */
        int BuscarIDPorNombre(const char* nombre);

        // Devuelve el objeto Artista completo dado un ID (útil para reportes)
        /** Busca un artista por su ID. Parámetros: id - ID del artista. Retorna: El artista encontrado. */
        Artista BuscarPorID(int id);

        // --- Lógica Avanzada (Importación) ---
        // Busca un artista por nombre. Si no existe, lo crea automáticamente.
        // Devuelve siempre un ID válido.
        /** Busca un artista por nombre, o lo crea si no existe. Parámetros: nombreArtista - Nombre del artista. Retorna: ID del artista. */
        int BuscarOCrear(std::string nombreArtista);
};

#endif // ARCHIVOARTISTAS_H
