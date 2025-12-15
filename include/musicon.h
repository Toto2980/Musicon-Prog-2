#ifndef MUSICON_H
#define MUSICON_H

#include <iostream>
#include <string>

// Includes de las entidades del sistema
#include "Canciones.h"
#include "DetallePlaylist.h"
#include "Artista.h"
#include "Album.h"
#include "Suscriptor.h"
#include "Listas.h"
#include "Accesos.h"
#include "Fecha.h"
#include "Generos.h"


class musicon
{
    public:
        /** Default constructor */
        musicon();
        /** Default destructor */
        virtual ~musicon();

        // --- MENÚS PÚBLICOS ---
        /** Inicia la ejecucion del programa */
        void iniciarSistema();
        /** Muestra el menu principal luego del login */
        void mostrarMenuPrincipal();
        /** Submenu de estadisticas */
        void mostrarMenuReportes();

        // --- REPORTES ---
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();
        void reporteCancionesPorUsuarioEnListas();
        void reporteBuscarCancionEnListas();

        // --- RANKING Y EXPORTACION ---
        void reporteRankingCanciones();
        void exportarCancionesACSV();

    protected:
        // Helpers para verificar existencia de IDs
        bool existeCancion(int idCancion);
        bool existeSuscriptor(int idSuscriptor);
        bool existeArtista(int idArtista);
        bool existeAlbum(int idAlbum);
        bool existeGenero(int idGenero);
        bool existeLista(int idLista);

        // Generadores de IDs autoincrementales
        int obtenerNuevoIdCancion();
        int obtenerNuevoIdSuscriptor();
        int obtenerNuevoIdGenero();
        int obtenerNuevoIdAlbum();
        int obtenerNuevoIdArtista();

        // Buscadores internos que retornan ID o -1
        int buscarIdSuscriptorPorNombre(const char* nombre);
        int buscarIdAlbumPorTitulo(const char* titulo);
        int buscarIdGeneroPorNombre(const char* nombre);
        int buscarIdArtistaPorNombre(const char* nombre);
        int buscarIdPlaylistPorNombre(const char* nombre);
        int buscarIdCancionPorNombre(const char* nombre);

        // Utilidad para contar registros en archivo
        int contarRegistros(const char* nombreArchivo, int tamanioRegistro);

    private:
        int _idUsuarioLogueado;
        char _nombreUsuarioLogueado[50];

        // --- MENÚS INTERNOS ---
        void menuBienvenida();
        void login();
        void registrarse();
        void menuCargas();
        void menuConfiguracion();

        // --- SUBMENÚS ---
        void menuCanciones();
        void menuPlaylists();

        // --- ABML Y LOGICA DE NEGOCIO ---
        void cargarNuevaCancionEnLista();
        int crearAlbumRapido(const char* tituloAlbum); // Logica Smart de carga
        void modificarCancion();
        void eliminarCancion();
        void listarCanciones();

        void cargarNuevaSuscripcion();
        void registrarAcceso();

        void cargarNuevaPlaylist();
        void modificarPlaylist();
        void eliminarPlaylist();
        void agregarCancionAPlaylist();
};

#endif // MUSICON_H
