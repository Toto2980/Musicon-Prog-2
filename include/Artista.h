/**
 * Este archivo define la clase Artista, que representa a un artista musical en el sistema Musicon.
 * Guarda directamente su nombre, estado, ID y nacionalidad.
 */

#ifndef ARTISTA_H
#define ARTISTA_H

 #include <cstring>

/** Representa a un artista musical con nombre, estado, ID y nacionalidad. */
class Artista {
    private:
        char _nombre[100];
        bool _estado;
        int _idArtista;
        char _nacionalidad[50];

    public:
        /** Constructor por defecto de la clase Artista. */
        Artista();
        /** Destructor de la clase Artista. */
        ~Artista();

        /** Establece el nombre del artista. Parámetros: nombre - Nombre a guardar. */
        void setNombre(const char* nombre) {
            if (nombre == nullptr) {
                _nombre[0] = '\0';
                return;
            }
            strncpy(_nombre, nombre, sizeof(_nombre)-1);
            _nombre[sizeof(_nombre) - 1] = '\0';
        }

        /** Establece el estado del artista. Parámetros: estado - true si está activo. */
        void setEstado(bool estado) { _estado = estado; }

        /** Establece el ID del artista. Parámetros: id - El ID único. */
        void setIdArtista(int id);

        /** Establece la nacionalidad del artista. Parámetros: nacionalidad - Cadena con la nacionalidad. */
        void setNacionalidad(const char* nacionalidad);

        /** Obtiene el nombre del artista. Retorna: Nombre del artista. */
        const char* getNombre() { return _nombre; }

        /** Obtiene el estado del artista. Retorna: true si está activo. */
        bool getEstado() { return _estado; }

        /** Obtiene el ID del artista. Retorna: El ID único. */
        int getIdArtista();

        /** Obtiene la nacionalidad del artista. Retorna: Puntero a la cadena de nacionalidad. */
        const char* getNacionalidad();

        /** Solicita al usuario los datos del artista. */
        void Cargar();

        /** Muestra los datos del artista en la consola. */
        void Mostrar();
};

#endif // ARTISTA_H
