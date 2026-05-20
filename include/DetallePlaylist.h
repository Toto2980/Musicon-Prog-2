/**
 * Este archivo define la clase DetallePlaylist, que representa la asociación muchos-a-muchos
 * entre playlists y canciones. Mantiene los detalles de qué canciones están en qué playlists.
 */

#ifndef DETALLEPLAYLIST_H
#define DETALLEPLAYLIST_H

#include "Fecha.h"

/** Representa la asociación entre una playlist y una canción, con fecha de agregado y estado. */
class DetallePlaylist {
    private:
        int _idPlaylist;
        int _idCancion;
        Fecha _fechaAgregado;
        bool _estado;

    public:
        /** Constructor por defecto de DetallePlaylist. */
        DetallePlaylist();

        /** Establece el ID de la playlist. Parámetros: id - ID de la playlist. */
        void setIdPlaylist(int id);
        /** Establece el ID de la canción. Parámetros: id - ID de la canción. */
        void setIdCancion(int id);
        /** Establece la fecha de agregado. Parámetros: f - Fecha de agregado. */
        void setFechaAgregado(Fecha f);
        /** Establece el estado. Parámetros: e - Estado activo/inactivo. */
        void setEstado(bool e);

        /** Obtiene el ID de la playlist. Retorna: ID de la playlist. */
        int getIdPlaylist();
        /** Obtiene el ID de la canción. Retorna: ID de la canción. */
        int getIdCancion();
        /** Obtiene la fecha de agregado. Retorna: Fecha de agregado. */
        Fecha getFechaAgregado();
        /** Obtiene el estado. Retorna: Estado activo/inactivo. */
        bool getEstado();

        /** Carga los datos desde el usuario. */
        void Cargar();
        /** Muestra los datos. */
        void Mostrar();

        // --- PERSISTENCIA ---
        /** Guarda el detalle en archivo. Retorna: true si se guardó correctamente. */
        bool Guardar();
        /** Lee un detalle desde el archivo en la posición especificada. Parámetros: pos - Posición. Retorna: true si se leyó correctamente. */
        bool Leer(int pos);
        /** Obtiene la cantidad de registros. Retorna: Cantidad total de registros en el archivo. */
        int ObtenerCantidadRegistros();

        /** Busca si una canción ya está en una playlist específica. Parámetros: idPlaylist - ID de la playlist, idCancion - ID de la canción. Retorna: Posición o -1 si no existe. */
        int BuscarCancionEnPlaylist(int idPlaylist, int idCancion);
};

#endif // DETALLEPLAYLIST_H
