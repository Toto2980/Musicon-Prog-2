/**
 * Este archivo define la clase musicon, que actúa como controlador principal de la aplicación.
 * Maneja menús y delegación de operaciones a los managers especializados.
 */

#ifndef MUSICON_H
#define MUSICON_H

// NOTA: Se eliminaron iostream y using namespace std de aqu� para cumplir con la correcci�n del profesor.
// Solo se incluyen las declaraciones necesarias.

/** Clase principal del sistema Musicon que maneja el menú y la lógica general. */
class musicon
{
    public:
        /** Constructor de musicon. */
        musicon();
        /** Destructor virtual de musicon. */
        virtual ~musicon();

        // --- MEN�S P�BLICOS ---
        /** Inicia el sistema. */
        void iniciarSistema();
        /** Muestra el menú principal. */
        void mostrarMenuPrincipal();
        /** Muestra el menú de reportes. */
        void mostrarMenuReportes();

        // --- REPORTES ---
        // La l�gica de informes se delega a ReporteManager.

    protected:
        // Helpers de existencia
        /** Verifica si existe una canción con el ID dado. Parámetros: idCancion - ID de la canción. Retorna: true si existe. */
        bool existeCancion(int idCancion);
        /** Verifica si existe un suscriptor con el ID dado. Parámetros: idSuscriptor - ID del suscriptor. Retorna: true si existe. */
        bool existeSuscriptor(int idSuscriptor);
        /** Verifica si existe un artista con el ID dado. Parámetros: idArtista - ID del artista. Retorna: true si existe. */
        bool existeArtista(int idArtista);
        /** Verifica si existe un álbum con el ID dado. Parámetros: idAlbum - ID del álbum. Retorna: true si existe. */
        bool existeAlbum(int idAlbum);
        /** Verifica si existe un género con el ID dado. Parámetros: idGenero - ID del género. Retorna: true si existe. */
        bool existeGenero(int idGenero);
        /** Verifica si existe una lista con el ID dado. Parámetros: idLista - ID de la lista. Retorna: true si existe. */
        bool existeLista(int idLista);

        // Generadores de IDs
        /** Obtiene un nuevo ID para una canción. Retorna: Nuevo ID. */
        int obtenerNuevoIdCancion();
        /** Obtiene un nuevo ID para un género. Retorna: Nuevo ID. */
        int obtenerNuevoIdGenero();
        /** Obtiene un nuevo ID para un álbum. Retorna: Nuevo ID. */
        int obtenerNuevoIdAlbum();
        /** Obtiene un nuevo ID para un artista. Retorna: Nuevo ID. */
        int obtenerNuevoIdArtista();

        // Buscadores internos
        /** Busca el ID de un suscriptor por nombre. Parámetros: nombre - Nombre del suscriptor. Retorna: ID o -1. */
        int buscarIdSuscriptorPorNombre(const char* nombre);
        /** Busca el ID de un álbum por título. Parámetros: titulo - Título del álbum. Retorna: ID o -1. */
        int buscarIdAlbumPorTitulo(const char* titulo);
        /** Busca el ID de un género por nombre. Parámetros: nombre - Nombre del género. Retorna: ID o -1. */
        int buscarIdGeneroPorNombre(const char* nombre);
        /** Busca el ID de un artista por nombre. Parámetros: nombre - Nombre del artista. Retorna: ID o -1. */
        int buscarIdArtistaPorNombre(const char* nombre);
        /** Busca el ID de una playlist por nombre. Parámetros: nombre - Nombre de la playlist. Retorna: ID o -1. */
        int buscarIdPlaylistPorNombre(const char* nombre);
        /** Busca el ID de una canción por nombre. Parámetros: nombre - Nombre de la canción. Retorna: ID o -1. */
        int buscarIdCancionPorNombre(const char* nombre);

    private:
        int _idUsuarioLogueado;
        char _nombreUsuarioLogueado[50];

        // --- MEN�S INTERNOS ---
        /** Muestra el menú de bienvenida. */
        void menuBienvenida();
        /** Maneja el login. */
        void login();

        // --- SUBMEN�S DE GESTI�N (ABMLs) ---
        /** Muestra el menú de cargas. */
        void menuCargas();
        /** Muestra el menú de configuración. */
        void menuConfiguracion();
        /** Muestra el menú de suscriptores. */
        void menuSuscriptores();

        /** Muestra el menú de canciones. */
        void menuCanciones();
        /** Muestra el menú de playlists. */
        void menuPlaylists();
        /** Muestra el menú de artistas. */
        void menuArtistas();
        /** Muestra el menú de géneros. */
        void menuGeneros();

        // --- L�GICA DE NEGOCIO (IMPLEMENTACI�N) ---

        // CANCIONES
        /** Carga una nueva canción en lista. */
        void cargarNuevaCancionEnLista();
        /** Crea un álbum rápidamente. Parámetros: tituloAlbum - Título del álbum. Retorna: ID del álbum. */
        int crearAlbumRapido(const char* tituloAlbum);
        /** Modifica una canción. */
        void modificarCancion();
        /** Elimina una canción. */
        void eliminarCancion();
        /** Lista las canciones. */
        void listarCanciones();

        // PLAYLISTS
        // La l�gica de playlists fue movida a PlaylistManager.

        // OTROS
        /** Carga una nueva suscripción. */
        void cargarNuevaSuscripcion(); // Placeholder
        /** Registra un acceso. */
        void registrarAcceso();

        // ARTISTAS Y GENEROS
        // La l�gica de artistas y g�neros fue movida a ArtistaManager y GeneroManager.
};

#endif // MUSICON_H
