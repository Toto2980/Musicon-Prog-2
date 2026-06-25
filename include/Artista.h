/*
 * ENTIDAD: Artista
 * Hereda de EntidadPadre (hereda _id como primer campo protegido).
 *
 * POR QUE char[] y no std::string:
 *   fwrite(&artista, sizeof(Artista), 1, p) escribe el bloque de memoria del objeto.
 *   std::string es un puntero interno -- fwrite escribiria la direccion, no el texto.
 *   char[] de tamano fijo garantiza que sizeof(Artista) sea constante y predecible.
 *
 * LAYOUT EN MEMORIA (orden de campos):
 *   [_id: 4 bytes] [_nombre: 100 bytes] [_estado: 1 byte] [_nacionalidad: 50 bytes]
 *   Total fijo = sizeof(Artista). Este tamano constante hace posible fseek aritmetico.
 */

#ifndef ARTISTA_H
#define ARTISTA_H

#include <cstring>
#include "EntidadPadre.h"

class Artista : public EntidadPadre {
    private:
        char _nombre[100];       // Fijo: 100 bytes siempre, aunque el nombre sea corto
        bool _estado;            // Eliminacion logica: false = borrado, true = activo
        char _nacionalidad[50];  // Fijo: 50 bytes siempre

    public:
        Artista();
        ~Artista();

        // setNombre valida nullptr y garantiza null-terminator al final del buffer
        void setNombre(const char* nombre) {
            if (nombre == nullptr) {
                _nombre[0] = '\0';
                return;
            }
            strncpy(_nombre, nombre, sizeof(_nombre)-1);
            _nombre[sizeof(_nombre) - 1] = '\0';
        }

        void setEstado(bool estado) { _estado = estado; }
        void setIdArtista(int id);
        void setNacionalidad(const char* nacionalidad);

        const char* getNombre() { return _nombre; }
        bool getEstado() { return _estado; }
        int getIdArtista();
        const char* getNacionalidad();

        // Cargar(): pide datos al usuario por teclado (consola)
        void Cargar();

        // Mostrar(): imprime el registro en pantalla (para listados)
        void Mostrar();
};

#endif // ARTISTA_H
