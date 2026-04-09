/**
 * Este archivo define la clase ArtistaManager, que maneja todas las operaciones CRUD para artistas
 * en la aplicación Musicon. Utiliza el archivo de artistas para persistencia.
 */

#ifndef ARTISTAMANAGER_H
#define ARTISTAMANAGER_H

#include "ArchivoArtistas.h"

/** Clase que gestiona las operaciones CRUD para artistas en el sistema Musicon. */
class ArtistaManager {
private:
    ArchivoArtistas _archivoArtistas; // Instancia del archivo de artistas

public:
    /** Agrega un nuevo artista al sistema. */
    void Agregar();

    /** Modifica un artista existente. */
    void Modificar();

    /** Elimina un artista (marcándolo como inactivo). */
    void Eliminar();

    /** Lista todos los artistas activos. */
    void Listar();
};

#endif // ARTISTAMANAGER_H
