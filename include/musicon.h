#ifndef MUSICON_H
#define MUSICON_H

#include <iostream>
#include <string>

// Includes necesarios
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
        musicon();
        virtual ~musicon();

        // --- MENÚS PÚBLICOS ---
        void iniciarSistema(); // Punto de entrada
        void mostrarMenuPrincipal();
        void mostrarMenuReportes();

        // --- REPORTES PÚBLICOS ---
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();
        void reporteCancionesPorUsuarioEnListas();
        void reporteBuscarCancionEnListas();

        // --- RANKING Y EXPORTACION ---
        void reporteRankingCanciones(); // Ranking real con ordenamiento
        void exportarCancionesACSV();   // Exportar a Excel

    protected:
        // --- FUNCIONES DE VALIDACIÓN ---
        bool existeCancion(int idCancion);
        bool existeSuscriptor(int idSuscriptor);
        bool existeArtista(int idArtista);
        bool existeAlbum(int idAlbum);
        bool existeGenero(int idGenero);
        bool existeLista(int idLista);

        // --- AUTOINCREMENTALES ---
        int obtenerNuevoIdCancion();
        int obtenerNuevoIdSuscriptor();
        int obtenerNuevoIdGenero();
        int obtenerNuevoIdAlbum();
        int obtenerNuevoIdArtista();

        // --- BUSCADORES (Helpers) ---
        int buscarIdSuscriptorPorNombre(const char* nombre);
        int buscarIdAlbumPorTitulo(const char* titulo);
        int buscarIdGeneroPorNombre(const char* nombre);
        int buscarIdArtistaPorNombre(const char* nombre);

        // Buscadores para Playlist ABM
        int buscarIdPlaylistPorNombre(const char* nombre);
        int buscarIdCancionPorNombre(const char* nombre);

        // Auxiliares
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

        // --- ABML CANCIONES ---
        void cargarNuevaCancionEnLista();
        int crearAlbumRapido(const char* tituloAlbum);
        void modificarCancion();
        void eliminarCancion();
        void listarCanciones();

        // --- OTROS ---
        void cargarNuevaSuscripcion();
        void registrarAcceso();

        // --- PLAYLISTS ---
        void cargarNuevaPlaylist();
        void modificarPlaylist();
        void eliminarPlaylist();
        void agregarCancionAPlaylist();
};

#endif // MUSICON_H
