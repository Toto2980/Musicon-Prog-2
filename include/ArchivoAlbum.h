#ifndef ARCHIVOALBUM_H
#define ARCHIVOALBUM_H

#include "Album.h"
#include <string>

/** Clase para manejar la persistencia de albumes en archivo binario. */
class ArchivoAlbum {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoAlbum. Parametros: nombreArchivo - Nombre del archivo binario, por defecto "albumes.dat". */
        ArchivoAlbum(std::string nombreArchivo = "albumes.dat");

        /** Guarda un registro de album en el archivo. Parametros: reg - El album a guardar. Retorna: true si se guardo, false en caso de error. */
        bool Guardar(Album reg);
        /** Lee un album desde el archivo en la posicion especificada. Parametros: pos - Posicion en el archivo. Retorna: El album leido. */
        Album Leer(int pos);
        /** Busca la posicion de un album por su ID. Parametros: id - ID del album. Retorna: Posicion en el archivo, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Busca el ID de un album por su titulo. Parametros: titulo - Titulo del album. Retorna: ID del album, -1 si no encontrado. */
        int BuscarIDPorTitulo(const char* titulo);
        /** Genera un nuevo ID unico para un album. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de albumes. */
        int ObtenerCantidadRegistros();
        /** Busca un album por su ID. Parametros: id - ID del album. Retorna: El album encontrado. */
        Album BuscarPorID(int id);

        // NUEVO: Busca por Titulo Y Artista (para evitar homonimos)
        /** Busca un album por titulo y artista, o lo crea si no existe. Parametros: tituloAlbum - Titulo del album, idArtista - ID del artista. Retorna: ID del album. */
        int BuscarOCrear(std::string tituloAlbum, int idArtista);
};

#endif // ARCHIVOALBUM_H
