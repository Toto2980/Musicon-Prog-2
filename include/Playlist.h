#ifndef PLAYLIST_H
#define PLAYLIST_H


#include "Fecha.h" // Necesario para la fecha de creación

/**
 * Este archivo define la clase Playlist, que representa listas de canciones creadas por usuarios.
 * Incluye métodos para guardar, cargar y buscar playlists en archivos.
 */

/** Representa una playlist de canciones creada por un suscriptor. */
class Playlist {
    private:
        int _idPlaylist; /**< Identificador único de la playlist */
        char _nombre[50]; /**< Nombre de la playlist */
        int _idSuscriptorCreador; /**< ID del suscriptor que la creó */
        Fecha _fechaCreacion; /**< Fecha de creación */
        bool _estado; /**< Estado activo/inactivo */

    public:
        /** Constructor por defecto. */
        Playlist();

        // --- SETTERS ---
        /** Establece el ID.
         * Parámetros: id - ID único.
         */
        void setIdPlaylist(int id);
        /** Establece el nombre.
         * Parámetros: n - Nombre de la playlist.
         */
        void setNombre(const char* n);
        /** Establece el ID del creador.
         * Parámetros: id - ID del suscriptor creador.
         */
        void setIdSuscriptorCreador(int id);
        /** Establece la fecha de creación.
         * Parámetros: f - Fecha de creación.
         */
        void setFechaCreacion(Fecha f);
        /** Establece el estado.
         * Parámetros: estado - true para activo.
         */
        void setEstado(bool estado);

        // --- GETTERS ---
        /** Dice cuál es el número único de la lista.
         * Retorna: El ID que la identifica.
         */
        int getIdPlaylist();
        /** Dice cuál es el nombre de la lista.
         * Retorna: El título que el usuario le puso.
         */
        const char* getNombre();
        /** Dice quién creó la lista.
         * Retorna: El ID del usuario que la hizo.
         */
        int getIdSuscriptorCreador();
        /** Dice cuándo se creó la lista.
         * Retorna: La fecha y hora de creación.
         */
        Fecha getFechaCreacion();
        /** Dice si la lista está disponible para usar.
         * Retorna: Verdadero si se puede acceder a ella.
         */
        bool getEstado();

        /** Pide al usuario que escriba el nombre de la lista. */
        void Cargar();
        /** Muestra la información de la lista en la pantalla. */
        void Mostrar();

        // --- PERSISTENCIA (Active Record) ---
        // Nota: Idealmente deberíamos mover esto a ArchivoPlaylist en el futuro
        /** Guarda la lista en un archivo para no perderla.
         * Retorna: Verdadero si se guardó sin problemas.
         */
        bool Guardar();
        /** Carga una lista desde el archivo en una posición específica.
         * Parámetros: pos - La posición en la lista de listas guardadas.
         * Retorna: Verdadero si se cargó correctamente.
         */
        bool Leer(int pos);
        /** Actualiza la información de la lista en el archivo.
         * Parámetros: pos - La posición a cambiar.
         * Retorna: Verdadero si se actualizó bien.
         */
        bool Modificar(int pos);
        /** Cuenta cuántas listas hay guardadas en total.
         * Retorna: El número total de listas.
         */
        int ObtenerCantidadRegistros();
        /** Crea un nuevo número único para una lista.
         * Retorna: El siguiente número disponible.
         */
        int GenerarIDNuevo();

        /** Busca una lista por su número identificador.
         * Parámetros: id - El ID a buscar.
         * Retorna: La posición si la encontró, o -1 si no existe.
         */
        int BuscarPorID(int id);
        /** Busca una lista por su nombre.
         * Parámetros: nombre - El nombre a buscar.
         * Retorna: La posición si la encontró, o -1 si no existe.
         */
        int BuscarPorNombre(const char* nombre);
};

#endif // PLAYLIST_H
