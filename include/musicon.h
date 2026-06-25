/**
 * Este archivo define la clase musicon, que actua como controlador principal de la aplicacion.
 * Maneja menus y delegacion de operaciones a los managers especializados.
 */

#pragma once

// NOTA: Se eliminaron iostream y using namespace std de aque para cumplir con la correccion del profesor.
// Solo se incluyen las declaraciones necesarias.

/** Clase principal del sistema Musicon que maneja el menu y la logica general. */
class musicon
{
    public:
        /** Constructor de musicon. */
        musicon();


        // --- MENUS PUBLICOS ---
        /** Inicia el sistema. */
        void iniciarSistema();
        /** Muestra el menu principal. */
        void mostrarMenuPrincipal();
        /** Muestra el menu de reportes. */
        void mostrarMenuReportes();

        // --- REPORTES ---
        // La logica de informes se delega a ReporteManager.

    protected:
        // Helpers de existencia
        /** Verifica si existe una cancion con el ID dado. Parametros: idCancion - ID de la cancion. Retorna: true si existe. */
        bool existeCancion(int idCancion);
        /** Verifica si existe un suscriptor con el ID dado. Parametros: idSuscriptor - ID del suscriptor. Retorna: true si existe. */
        bool existeSuscriptor(int idSuscriptor);
        /** Verifica si existe un artista con el ID dado. Parametros: idArtista - ID del artista. Retorna: true si existe. */
        bool existeArtista(int idArtista);
        /** Verifica si existe un album con el ID dado. Parametros: idAlbum - ID del album. Retorna: true si existe. */
        bool existeAlbum(int idAlbum);
        /** Verifica si existe un genero con el ID dado. Parametros: idGenero - ID del genero. Retorna: true si existe. */
        bool existeGenero(int idGenero);
        /** Verifica si existe una lista con el ID dado. Parametros: idLista - ID de la lista. Retorna: true si existe. */
        bool existeLista(int idLista);

        // Generadores de IDs
        /** Obtiene un nuevo ID para una cancion. Retorna: Nuevo ID. */
        int obtenerNuevoIdCancion();
        /** Obtiene un nuevo ID para un genero. Retorna: Nuevo ID. */
        int obtenerNuevoIdGenero();
        /** Obtiene un nuevo ID para un album. Retorna: Nuevo ID. */
        int obtenerNuevoIdAlbum();
        /** Obtiene un nuevo ID para un artista. Retorna: Nuevo ID. */
        int obtenerNuevoIdArtista();

        // Buscadores internos
        /** Busca el ID de un suscriptor por nombre. Parametros: nombre - Nombre del suscriptor. Retorna: ID o -1. */
        int buscarIdSuscriptorPorNombre(const char* nombre);
        /** Busca el ID de un album por titulo. Parametros: titulo - Titulo del album. Retorna: ID o -1. */
        int buscarIdAlbumPorTitulo(const char* titulo);
        /** Busca el ID de un genero por nombre. Parametros: nombre - Nombre del genero. Retorna: ID o -1. */
        int buscarIdGeneroPorNombre(const char* nombre);
        /** Busca el ID de un artista por nombre. Parametros: nombre - Nombre del artista. Retorna: ID o -1. */
        int buscarIdArtistaPorNombre(const char* nombre);
        /** Busca el ID de una playlist por nombre. Parametros: nombre - Nombre de la playlist. Retorna: ID o -1. */
        int buscarIdPlaylistPorNombre(const char* nombre);
        /** Busca el ID de una cancion por nombre. Parametros: nombre - Nombre de la cancion. Retorna: ID o -1. */
        int buscarIdCancionPorNombre(const char* nombre);

    private:
        int _idUsuarioLogueado;
        char _nombreUsuarioLogueado[50];

        // --- MENUS INTERNOS ---
        /** Muestra el menu de bienvenida. */
        void menuBienvenida();
        /** Maneja el login. */
        void login();

        // --- SUBMENUS DE GESTION (ABMLs) ---
        /** Muestra el menu de cargas. */
        void menuCargas();
        /** Muestra el menu de configuracion. */
        void menuConfiguracion();
        /** Muestra el menu de suscriptores. */
        void menuSuscriptores();

        /** Muestra el menu de canciones. */
        void menuCanciones();
        /** Muestra el menu de playlists. */
        void menuPlaylists();
        /** Muestra el menu de artistas. */
        void menuArtistas();
        /** Muestra el menu de generos. */
        void menuGeneros();

        // --- LOGICA DE NEGOCIO (IMPLEMENTACION) ---

        // CANCIONES
        /** Carga una nueva cancion en lista. */
        void cargarNuevaCancionEnLista();
        /** Crea un album rapidamente. Parametros: tituloAlbum - Titulo del album. Retorna: ID del album. */
        int crearAlbumRapido(const char* tituloAlbum);
        /** Modifica una cancion. */
        void modificarCancion();
        /** Elimina una cancion. */
        void eliminarCancion();
        /** Lista las canciones. */
        void listarCanciones();

        

        // OTROS
        /** Carga una nueva suscripcion. */
        void cargarNuevaSuscripcion(); // Placeholder
        /** Registra un acceso. */
        void registrarAcceso();
        // ARTISTAS Y GENEROS
        // La logica de artistas y generos fue movida a ArtistaManager y GeneroManager.
};


