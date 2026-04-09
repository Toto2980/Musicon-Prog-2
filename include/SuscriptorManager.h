/**
 * Este archivo define la clase SuscriptorManager, que maneja todas las operaciones CRUD para suscriptores
 * (usuarios) en la aplicaci�n Musicon. Utiliza ArchivoSuscriptores para persistencia.
 */

#ifndef SUSCRIPORMANAGER_H
#define SUSCRIPORMANAGER_H

#include "ArchivoSuscriptores.h"

/** Gestiona operaciones de suscriptores (agregar, modificar, eliminar, listar). Utiliza ArchivoSuscriptores para acceder a los datos persistentes. */
class SuscriptorManager {
private:
    ArchivoSuscriptores _archivoSuscriptores; // Instancia del archivo de suscriptores

public:
    /** Agrega un nuevo suscriptor al sistema (registro de usuario). */
    void Agregar();

    /** Modifica un suscriptor existente. */
    void Modificar();

    /** Elimina un suscriptor (marcándolo como inactivo). */
    void Eliminar();

    /** Lista todos los suscriptores activos. */
    void Listar();
};

#endif // SUSCRIPORMANAGER_H
