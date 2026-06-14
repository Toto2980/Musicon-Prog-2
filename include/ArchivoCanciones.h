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
        /** Constructor de ArchivoCanciones. Parámetros: nombreArchivo - Nombre del archivo, por defecto "canciones.dat". */
        ArchivoCanciones(std::string nombreArchivo = "canciones.dat");

        /** Guarda una canción en el archivo. Parámetros: reg - Canción a guardar. Retorna: true si guardada, false error. */
        bool Guardar(Canciones reg);
        /** Lee una canción desde el archivo en la posición especificada. Parámetros: pos - Posición. Retorna: La canción leída. */
        Canciones Leer(int pos);
        /** Genera un nuevo ID único para una canción. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Busca la posición de una canción por su ID. Parámetros: id - ID de la canción. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Modifica una canción en el archivo. Parámetros: pos - Posición a modificar, reg - Nueva canción. Retorna: true si modificada, false error. */
        bool Modificar(int pos, Canciones reg);
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de canciones. */
        int ObtenerCantidadRegistros();

        /** Busca una canción por su ID. Parámetros: id - ID de la canción. Retorna: La canción encontrada. */
        Canciones BuscarPorID(int id);

        // Busca la posición física de una canción por su nombre y su álbum.
        // Sirve para detectar duplicados antes de guardar.
        /** Busca la posición de una canción por nombre y álbum. Parámetros: nombre - Nombre de la canción, idAlbum - ID del álbum. Retorna: Posición, -1 si no encontrado. */
        int BuscarPosicionPorNombreYAlbum(const char* nombre, int idAlbum);
};

#endif // ARCHIVOCANCIONES_H
