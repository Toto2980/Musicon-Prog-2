/*
 * SuscriptorManager.h
 * Operaciones CRUD de suscriptores (usuarios). Usa ArchivoSuscriptores para
 * la persistencia.
 */

#ifndef SUSCRIPTORMANAGER_H
#define SUSCRIPTORMANAGER_H

#include "ArchivoSuscriptores.h"

/** Gestiona altas, bajas, modificaciones y listados de suscriptores. */
class SuscriptorManager {
public:
    /** Filtro para los listados. */
    enum Filtro { ACTIVOS, INACTIVOS, TODOS };

    /** Registra un nuevo suscriptor (valida nombre único). */
    void Agregar();
    /** Modifica un suscriptor existente. */
    void Modificar();
    /** Da de baja (lógica) un suscriptor. */
    void Eliminar();

    /** Lista usuarios activos (alias de ListarActivos). */
    void Listar();
    void ListarActivos();
    void ListarInactivos();
    void ListarTodos();

private:
    ArchivoSuscriptores _archivoSuscriptores;

    /** Imprime los suscriptores que cumplen el filtro indicado. */
    void listarConFiltro(const char* titulo, Filtro filtro);
};

#endif // SUSCRIPTORMANAGER_H
