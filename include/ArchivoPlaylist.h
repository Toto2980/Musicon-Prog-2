#ifndef ARCHIVOPLAYLISTS_H
#define ARCHIVOPLAYLISTS_H

#include "Playlist.h"
#include <string>

/** Maneja la persistencia de playlists en archivo binario. */
class ArchivoPlaylist {
private:
    std::string _nombreArchivo;

public:
    /** Constructor. Parámetros: nombreArchivo - Nombre del archivo, por defecto "playlists.dat". */
    ArchivoPlaylist(std::string nombreArchivo = "playlists.dat");

    /** Guarda una playlist al final del archivo. Retorna: true si OK. */
    bool Guardar(Playlist reg);

    /** Lee la playlist en la posición indicada. Retorna: Playlist leída (estado=false si falla). */
    Playlist Leer(int pos);

    /** Sobreescribe la playlist en la posición indicada. Retorna: true si OK. */
    bool Modificar(int pos, Playlist reg);

    /** Retorna la cantidad total de registros en el archivo. */
    int ObtenerCantidadRegistros();

    /** Genera un nuevo ID único (último ID + 1). */
    int GenerarIDNuevo();

    /** Busca la posición de una playlist por ID. Retorna: posición o -1. */
    int BuscarPorID(int id);

    /** Busca la posición de una playlist por nombre (case-insensitive). Retorna: posición o -1. */
    int BuscarPorNombre(const char* nombre);
};

#endif // ARCHIVOPLAYLISTS_H
