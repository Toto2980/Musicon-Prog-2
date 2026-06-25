#ifndef ARCHIVOCANCIONES_H
#define ARCHIVOCANCIONES_H

#include "Canciones.h"
#include <string>

// GESTOR DE PERSISTENCIA
// Responsabilidad: Guardar y leer objetos Canciones en disco.
/** Clase para manejar la persistencia de canciones en archivo binario. */
class ArchivoCanciones {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoCanciones. Parametros: nombreArchivo - Nombre del archivo, por defecto "canciones.dat". */
        ArchivoCanciones(std::string nombreArchivo = "canciones.dat");

        /** Guarda una cancion en el archivo. Parametros: reg - Cancion a guardar. Retorna: true si guardada, false error. */
        bool Guardar(Canciones reg);
        /** Lee una cancion desde el archivo en la posicion especificada. Parametros: pos - Posicion. Retorna: La cancion leida. */
        Canciones Leer(int pos);
        /** Genera un nuevo ID unico para una cancion. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Busca la posicion de una cancion por su ID. Parametros: id - ID de la cancion. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Modifica una cancion en el archivo. Parametros: pos - Posicion a modificar, reg - Nueva cancion. Retorna: true si modificada, false error. */
        bool Modificar(int pos, Canciones reg);
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de canciones. */
        int ObtenerCantidadRegistros();

        /** Busca una cancion por su ID. Parametros: id - ID de la cancion. Retorna: La cancion encontrada. */
        Canciones BuscarPorID(int id);

        // Busca la posicion fisica de una cancion por su nombre y su album.
        // Sirve para detectar duplicados antes de guardar.
        /** Busca la posicion de una cancion por nombre y album. Parametros: nombre - Nombre de la cancion, idAlbum - ID del album. Retorna: Posicion, -1 si no encontrado. */
        int BuscarPosicionPorNombreYAlbum(const char* nombre, int idAlbum);
};

#endif // ARCHIVOCANCIONES_H
