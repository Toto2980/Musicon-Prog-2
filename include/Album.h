/** Este archivo implementa la clase Album, que representa un álbum musical en el sistema Musicon.
 * Contiene atributos como título, artista, año de publicación y estado. Incluye métodos
 * para persistencia en archivo binario (guardar, leer, modificar) y búsquedas. */

#ifndef ALBUM_H
#define ALBUM_H

/** Clase que representa un álbum musical con atributos como ID, título, artista, año de publicación y estado. Incluye métodos para persistencia en archivo binario. */
class Album {
    private:
        int _idAlbum; // Identificador único del álbum
        char _titulo[100]; // Título del álbum
        int _idArtista; // ID del artista (clave foránea)
        int _anioPublicacion; // Año de lanzamiento
        bool _estado; // Estado activo/inactivo

    public:
        /** Constructor por defecto de la clase Album. */
        Album();

        // --- SETTERS ---
        /** Establece el ID del álbum. Parámetros: id - ID único del álbum. */
        void setIdAlbum(int id);

        /** Establece el título del álbum. Parámetros: titulo - Cadena con el título. */
        void setTitulo(const char* titulo);

        /** Establece el ID del artista. Parámetros: idAr - ID del artista. */
        void setIdArtista(int idAr);

        /** Establece el año de publicación. Parámetros: anio - Año de lanzamiento. */
        void setAnioPublicacion(int anio);

        /** Establece el estado activo/inactivo. Parámetros: e - true para activo, false para inactivo. */
        void setEstado(bool e);

        // --- GETTERS ---
        /** Obtiene el ID del álbum. Retorna: ID único del álbum. */
        int getIdAlbum();

        /** Obtiene el título del álbum. Retorna: Puntero a la cadena del título. */
        const char* getTitulo();

        /** Obtiene el ID del artista. Retorna: ID del artista. */
        int getIdArtista();

        /** Obtiene el año de publicación. Retorna: Año de lanzamiento. */
        int getAnioPublicacion();

        /** Obtiene el estado activo/inactivo. Retorna: true si activo, false si inactivo. */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        /** Carga los datos del álbum desde la entrada del usuario. */
        void Cargar();

        /** Muestra los datos del álbum en la consola. */
        void Mostrar();

        // --- PERSISTENCIA ---
        /** Guarda el álbum en el archivo binario (agrega al final). Retorna: true si se guardó correctamente, false en caso de error. */
        bool Guardar();

        /** Lee un álbum desde el archivo binario en la posición especificada. Parámetros: pos - Posición en el archivo (basado en 0). Retorna: true si se leyó correctamente, false en caso de error. */
        bool Leer(int pos);

        /** Modifica un álbum en el archivo binario en la posición especificada. Parámetros: pos - Posición a modificar. Retorna: true si se modificó correctamente, false en caso de error. */
        bool Modificar(int pos);

        /** Obtiene la cantidad total de registros (álbumes) en el archivo. Retorna: Número de álbumes guardados. */
        int ObtenerCantidadRegistros();

        /** Busca el ID de un álbum por su título (comparación insensible a mayúsculas). Parámetros: titulo - Título a buscar. Retorna: ID del álbum si se encuentra, -1 si no. */
        int BuscarIDPorTitulo(const char* titulo);

        /** Busca la posición en el archivo de un álbum por su ID. Parámetros: id - ID del álbum a buscar. Retorna: Posición en el archivo (basado en 0), -1 si no se encuentra. */
        int BuscarPosicionPorID(int id);
};

#endif // ALBUM_H
