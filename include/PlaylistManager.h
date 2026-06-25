/**
 * Este archivo define la clase PlaylistManager, que maneja todas las operaciones relacionadas con playlists
 * y sus canciones asociadas. Permite crear, modificar, eliminar playlists y gestionar canciones dentro de ellas.
 */

#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "ArchivoPlaylist.h"
#include "DetallePlaylist.h"

/** Gestiona operaciones CRUD de playlists y gestion de canciones en playlists. */
class PlaylistManager {
private:
    ArchivoPlaylist _archivoPlaylist;

    /** Metodo privado para buscar el ID de una cancion por su nombre. Parametros: nombre - Nombre de la cancion. Retorna: ID de la cancion o -1. */
    int buscarIdCancionPorNombre(const char* nombre);

public:
    /** Muestra el menu de gestion de playlists para un usuario especifico. Parametros: idUsuario - ID del usuario logueado. */
    void MostrarMenu(int idUsuario);

    /** Muestra todas las playlists de un usuario. Parametros: idUsuario - ID del usuario. */
    void MostrarMisPlaylists(int idUsuario);

    /** Crea una nueva playlist para un usuario. Parametros: idUsuario - ID del creador. */
    void CrearPlaylist(int idUsuario);

    /** Modifica una playlist existente de un usuario. Parametros: idUsuario - ID del propietario. */
    void ModificarPlaylist(int idUsuario);

    /** Elimina una playlist de un usuario. Parametros: idUsuario - ID del propietario. */
    void EliminarPlaylist(int idUsuario);

    /** Agrega una cancion a una playlist existente. */
    void AgregarCancionAPlaylist();
};

#endif // PLAYLISTMANAGER_H
