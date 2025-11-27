#ifndef MUSICON_H
#define MUSICON_H

#include <iostream>
#include <string>

#include "Artista.h"
#include "Album.h"
#include "Suscriptor.h"
#include "Listas.h"
#include "Accesos.h"
#include "Fecha.h"



class Canciones;
class Artista;
class Album;
class Genero;
class Suscriptor;

class musicon
{
    public:
        musicon();
        virtual ~musicon();

        // --- MENÚS PÚBLICOS (Para que main.cpp los pueda llamar) ---
        void mostrarMenuPrincipal();
        void mostrarMenuReportes(); // Renombrado y hecho público

        // --- REPORTES PÚBLICOS ---
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();

    protected:
        // --- FUNCIONES DE VALIDACIÓN ---
        bool existeCancion(int idCancion);
        bool existeSuscriptor(int idSuscriptor);
        bool existeArtista(int idArtista);
        bool existeAlbum(int idAlbum);
        bool existeGenero(int idGenero);
        bool existeLista(int idLista);

        // --- FUNCIONES DE BÚSQUEDA ---
        std::string buscarNombreGenero(int idGeneroBuscado);

        bool buscarCancion(int idCancionBuscada, Canciones& regCancion);

        bool buscarArtista(int idArtistaBuscada, Artista& regArtista);
        bool buscarAlbum(int idAlbumBuscado, Album& regAlbum);

        int contarRegistros(const char* nombreArchivo, int tamanioRegistro);

    private:
        // --- MENÚS INTERNOS ---
        void menuCargas();
        void menuConfiguracion();

        // --- CARGAS ---
        void cargarNuevaCancionEnLista();
        void cargarNuevaSuscripcion();
        void cargarNuevoAcceso();
        void registrarAcceso();
        void cargarNuevaPlaylist();
};

#endif // MUSICON_H

