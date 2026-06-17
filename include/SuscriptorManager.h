/**
* Este archivo define la clase SuscriptorManager, que maneja todas las operaciones CRUD para suscriptores
* (usuarios) en la aplicación Musicon. Utiliza ArchivoSuscriptores para persistencia.
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
	
	/** Da de baja un suscriptor. */
	void Eliminar();
	
	/** Lista usuarios activos. */
	void Listar();
	
	/** Lista únicamente usuarios activos. */
	void ListarActivos();
	
	/** Lista únicamente usuarios dados de baja. */
	void ListarInactivos();
	
	/** Lista todos los usuarios. */
	void ListarTodos();
};

#endif // SUSCRIPORMANAGER_H
