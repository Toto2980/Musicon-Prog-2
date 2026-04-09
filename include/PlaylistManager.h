/**
 * Este archivo define la clase PlaylistManager, que maneja todas las operaciones relacionadas con playlists
 * y sus canciones asociadas. Permite crear, modificar, eliminar playlists y gestionar canciones dentro de ellas.
 */

#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "Playlist.h"
#include "DetallePlaylist.h"

/** Gestiona operaciones CRUD de playlists y gestión de canciones en playlists. */
class PlaylistManager {
private:
    /** Método privado para buscar el ID de una canción por su nombre. Parámetros: nombre - Nombre de la canción. Retorna: ID de la canción o -1. */
    int buscarIdCancionPorNombre(const char* nombre);

public:
    /** Muestra el menú de gestión de playlists para un usuario específico. Parámetros: idUsuario - ID del usuario logueado. */
    void MostrarMenu(int idUsuario);

    /** Muestra todas las playlists de un usuario. Parámetros: idUsuario - ID del usuario. */
    void MostrarMisPlaylists(int idUsuario);

    /** Crea una nueva playlist para un usuario. Parámetros: idUsuario - ID del creador. */
    void CrearPlaylist(int idUsuario);

    /** Modifica una playlist existente de un usuario. Parámetros: idUsuario - ID del propietario. */
    void ModificarPlaylist(int idUsuario);

    /** Elimina una playlist de un usuario. Parámetros: idUsuario - ID del propietario. */
    void EliminarPlaylist(int idUsuario);

    /** Agrega una canción a una playlist existente. */
    void AgregarCancionAPlaylist();
};

#endif // PLAYLISTMANAGER_H
