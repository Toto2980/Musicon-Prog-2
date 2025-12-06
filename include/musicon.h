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

class musicon
{
    public:
        musicon();
        virtual ~musicon();

        // --- MENÚS PÚBLICOS ---
        void mostrarMenuPrincipal();
        void mostrarMenuReportes();

        // --- REPORTES PÚBLICOS ---
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();

    protected:
        // --- FUNCIONES DE VALIDACIÓN Y BÚSQUEDA ---
        bool existeCancion(int idCancion);
        bool existeSuscriptor(int idSuscriptor);
        bool existeArtista(int idArtista);
        bool existeAlbum(int idAlbum);
        bool existeGenero(int idGenero);
        bool existeLista(int idLista);

        // Auxiliares
        int contarRegistros(const char* nombreArchivo, int tamanioRegistro);
        int obtenerNuevoIdCancion();
    private:
        // --- MENÚS INTERNOS ---
        void menuCargas();
        void menuConfiguracion();

        // --- SUBMENÚS ---
        void menuCanciones();
        void menuPlaylists();

        // --- CARGAS Y LISTADOS (ABM) ---
        void cargarNuevaCancionEnLista();
        void modificarCancion();
        void eliminarCancion();
        void listarCanciones();

        // --- OTRAS CARGAS ---
        void cargarNuevaSuscripcion();
        void cargarNuevoAcceso();
        void registrarAcceso();

        // --- PLAYLISTS ---
        void cargarNuevaPlaylist();
        void modificarPlaylist();
        void eliminarPlaylist();
        void agregarCancionAPlaylist();
};

#endif // MUSICON_H
