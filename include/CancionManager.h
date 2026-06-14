/**
 * Este archivo define la clase CancionManager, que maneja todas las operaciones relacionadas con canciones
 * en la aplicación Musicon. Incluye CRUD de canciones, importación/exportación, backups y registro de accesos.
 */

#ifndef CANCIONMANAGER_H
#define CANCIONMANAGER_H

#include "ArchivoCanciones.h"
#include "ArchivoAlbum.h"
#include "ArchivoArtistas.h"
#include "ArchivoGeneros.h"

/** Gestiona todas las operaciones relacionadas con canciones en Musicon, incluyendo CRUD, importación y registro de accesos. */
class CancionManager {
    private:
        ArchivoCanciones _archivoCanciones; // Archivo para operaciones con canciones
        ArchivoAlbum _archivoAlbum; // Archivo para operaciones con álbumes
        ArchivoArtistas _archivoArtistas; // Archivo para operaciones con artistas
        ArchivoGeneros _archivoGeneros; // Archivo para operaciones con géneros

        /** Método privado para crear un álbum rápidamente si no existe. Parámetros: tituloAlbum - El título del álbum a crear. Retorna: El ID del álbum creado o encontrado. */
        int crearAlbumRapido(const char* tituloAlbum);

    public:
        /** Agrega una nueva canción al sistema, creando artista/álbum/género si no existen. */
        void Agregar();

        /** Lista todas las canciones con detalles (artista, álbum, género). */
        void ListarDetallado();

        /** Modifica una canción existente. */
        void Modificar();

        /** Elimina una canción (marcándola como inactiva). */
        void Eliminar();

        /** Lista todas las canciones de forma básica. */
        void Listar();

        /** Registra un acceso a una canción por un suscriptor. Parámetros: idSuscriptor - ID del suscriptor que accede. */
        void RegistrarAcceso(int idSuscriptor);

        /** Crea un backup de las canciones en un archivo .bak. */
        void HacerBackup();

        /** Exporta las canciones a un archivo CSV. */
        void ExportarACSV();

        /** Importa canciones desde un archivo CSV, manejando conflictos. */
        void ImportarDesdeCSV();
};

#endif // CANCIONMANAGER_H
