/**
 * Este archivo define la clase GeneroManager, que maneja todas las operaciones CRUD para generos musicales
 * en la aplicacion Musicon. Utiliza la clase Genero para persistencia.
 */

#ifndef GENEROMANAGER_H
#define GENEROMANAGER_H

#include "ArchivoGeneros.h"

/** Gestiona las operaciones CRUD para generos musicales en el sistema Musicon. */
class GeneroManager {
private:
    ArchivoGeneros _archivoGeneros;

public:
    /** Agrega un nuevo genero al sistema. */
    void Agregar();

    /** Modifica un genero existente. */
    void Modificar();

    /** Elimina un genero (marcandolo como inactivo). */
    void Eliminar();

    /** Lista todos los generos activos. */
    void Listar();
};

#endif // GENEROMANAGER_H
