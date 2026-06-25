/**
 * Este archivo define la clase DetallePlaylist, que representa la asociacion muchos-a-muchos
 * entre playlists y canciones. Mantiene los detalles de que canciones estan en que playlists.
 */

#ifndef DETALLEPLAYLIST_H
#define DETALLEPLAYLIST_H

#include "Fecha.h"

/** Representa la asociacion entre una playlist y una cancion, con fecha de agregado y estado. */
class DetallePlaylist {
    private:
        int _idPlaylist;
        int _idCancion;
        Fecha _fechaAgregado;
        bool _estado;

    public:
        /** Constructor por defecto de DetallePlaylist. */
        DetallePlaylist();

        /** Establece el ID de la playlist. Parametros: id - ID de la playlist. */
        void setIdPlaylist(int id);
        /** Establece el ID de la cancion. Parametros: id - ID de la cancion. */
        void setIdCancion(int id);
        /** Establece la fecha de agregado. Parametros: f - Fecha de agregado. */
        void setFechaAgregado(Fecha f);
        /** Establece el estado. Parametros: e - Estado activo/inactivo. */
        void setEstado(bool e);

        /** Obtiene el ID de la playlist. Retorna: ID de la playlist. */
        int getIdPlaylist();
        /** Obtiene el ID de la cancion. Retorna: ID de la cancion. */
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
        /** Guarda el detalle en archivo. Retorna: true si se guardo correctamente. */
        bool Guardar();
        /** Lee un detalle desde el archivo en la posicion especificada. Parametros: pos - Posicion. Retorna: true si se leyo correctamente. */
        bool Leer(int pos);
        /** Obtiene la cantidad de registros. Retorna: Cantidad total de registros en el archivo. */
        int ObtenerCantidadRegistros();

        /** Busca si una cancion ya esta en una playlist especifica. Parametros: idPlaylist - ID de la playlist, idCancion - ID de la cancion. Retorna: Posicion o -1 si no existe. */
        int BuscarCancionEnPlaylist(int idPlaylist, int idCancion);
};

#endif // DETALLEPLAYLIST_H
