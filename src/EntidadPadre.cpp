/**
 * Implementacion de la clase base EntidadPadre.
 *
 * PATRON: Herencia (clase base)
 * EntidadPadre existe UNICAMENTE para evitar duplicar el campo _id y los metodos
 * getId/setId en cada entidad del sistema.
 *
 * POR QUE ES TAN PEQUENA:
 *   - Solo tiene _id, porque ese es el unico campo COMUN a Artista y Suscriptor.
 *   - Si agregaramos _nombre aqui, Canciones tambien tendria que heredar (y no quiere).
 *   - El principio es: la clase base contiene SOLO lo que comparten TODAS las subclases.
 *
 * POR QUE CANCIONES NO HEREDA DE EntidadPadre:
 *   - El archivo binario de canciones tiene un layout fijo ya existente.
 *   - Agregar una vtable o cambiar el orden de los campos romperia la lectura del archivo.
 *   - Es mas seguro que Canciones maneje su propio _id directamente.
 */

#include "EntidadPadre.h"

/** Constructor: inicializa el ID en 0 (sin asignar). */
EntidadPadre::EntidadPadre() : _id(0) {}

/** Destructor: definido explicitamente aunque no haya recursos que liberar. */
EntidadPadre::~EntidadPadre() = default;

/** Asigna el ID de la entidad. Solo lo llaman los setters de las subclases (setIdArtista, etc.). */
void EntidadPadre::setId(int id) {
    _id = id;
}

/** Devuelve el ID de la entidad. Solo lo llaman los getters de las subclases. */
int EntidadPadre::getId() const {
    return _id;
}
