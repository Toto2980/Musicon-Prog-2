/**
 * Este archivo define la clase CancionManager, que maneja todas las operaciones relacionadas con canciones
 * en la aplicacion Musicon. Incluye CRUD de canciones, importacion/exportacion, backups y registro de accesos.
 */

#ifndef CANCIONMANAGER_H
#define CANCIONMANAGER_H

#include "ArchivoCanciones.h"
#include "ArchivoAlbum.h"
#include "ArchivoArtistas.h"
#include "ArchivoGeneros.h"

/** Gestiona todas las operaciones relacionadas con canciones en Musicon, incluyendo CRUD, importacion y registro de accesos. */
class CancionManager {
    private:
        ArchivoCanciones _archivoCanciones; // Archivo para operaciones con canciones
        ArchivoAlbum _archivoAlbum; // Archivo para operaciones con albumes
        ArchivoArtistas _archivoArtistas; // Archivo para operaciones con artistas
        ArchivoGeneros _archivoGeneros; // Archivo para operaciones con generos

        /** Metodo privado para crear un album rapidamente si no existe. Parametros: tituloAlbum - El titulo del album a crear. Retorna: El ID del album creado o encontrado. */
        int crearAlbumRapido(const char* tituloAlbum);

    public:
        /** Agrega una nueva cancion al sistema, creando artista/album/genero si no existen. */
        void Agregar();

        /** Lista todas las canciones con detalles (artista, album, genero). */
        void ListarDetallado();

        /** Modifica una cancion existente. */
        void Modificar();

        /** Elimina una cancion (marcandola como inactiva). */
        void Eliminar();

        /** Lista todas las canciones de forma basica. */
        void Listar();

        /** Muestra el menu interno de gestion de canciones. */
        void MostrarMenu();

        /** Registra un acceso a una cancion por un suscriptor. Parametros: idSuscriptor - ID del suscriptor que accede. */
        void RegistrarAcceso(int idSuscriptor);

        /** Crea un backup de las canciones en un archivo .bak. */
        void HacerBackup();

        /** Exporta las canciones a un archivo CSV. */
        void ExportarACSV();

        /** Importa canciones desde un archivo CSV, manejando conflictos. */
        void ImportarDesdeCSV();
};

#endif // CANCIONMANAGER_H
