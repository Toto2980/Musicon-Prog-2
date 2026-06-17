/**
 * Implementación de la clase base EntidadPadre.
 *
 * PATRÓN: Herencia (clase base)
 * EntidadPadre existe ÚNICAMENTE para evitar duplicar el campo _id y los métodos
 * getId/setId en cada entidad del sistema.
 *
 * POR QUÉ ES TAN PEQUEÑA:
 *   - Solo tiene _id, porque ese es el único campo COMÚN a Artista y Suscriptor.
 *   - Si agregáramos _nombre aquí, Canciones también tendría que heredar (y no quiere).
 *   - El principio es: la clase base contiene SOLO lo que comparten TODAS las subclases.
 *
 * POR QUÉ CANCIONES NO HEREDA DE EntidadPadre:
 *   - El archivo binario de canciones tiene un layout fijo ya existente.
 *   - Agregar una vtable o cambiar el orden de los campos rompería la lectura del archivo.
 *   - Es más seguro que Canciones maneje su propio _id directamente.
 */

#include "EntidadPadre.h"

/** Constructor: inicializa el ID en 0 (sin asignar). */
EntidadPadre::EntidadPadre() : _id(0) {}

/** Destructor: definido explícitamente aunque no haya recursos que liberar. */
EntidadPadre::~EntidadPadre() = default;

/** Asigna el ID de la entidad. Solo lo llaman los setters de las subclases (setIdArtista, etc.). */
void EntidadPadre::setId(int id) {
    _id = id;
}

/** Devuelve el ID de la entidad. Solo lo llaman los getters de las subclases. */
int EntidadPadre::getId() const {
    return _id;
}
