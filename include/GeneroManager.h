/**
 * Este archivo define la clase GeneroManager, que maneja todas las operaciones CRUD para géneros musicales
 * en la aplicación Musicon. Utiliza la clase Genero para persistencia.
 */

#ifndef GENEROMANAGER_H
#define GENEROMANAGER_H

#include "ArchivoGeneros.h"

/** Gestiona las operaciones CRUD para géneros musicales en el sistema Musicon. */
class GeneroManager {
private:
    ArchivoGeneros _archivoGeneros;

public:
    /** Agrega un nuevo género al sistema. */
    void Agregar();

    /** Modifica un género existente. */
    void Modificar();

    /** Elimina un género (marcándolo como inactivo). */
    void Eliminar();

    /** Lista todos los géneros activos. */
    void Listar();
};

#endif // GENEROMANAGER_H
