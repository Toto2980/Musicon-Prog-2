#ifndef MUSICON_H
#define MUSICON_H

#include <iostream>
#include <string>

#include "Artista.h"
#include "Album.h"S
#include "Suscriptor.h"
#include "Listas.h"
#include "Accesos.h"
#include "Fecha.h"
#include "Hora.h"

class Cancion;
class Artista;
class Album;
class Genero;
class Suscriptor;

class musicon
{
    public:
        musicon();
        virtual ~musicon();

        void mostrarMenuPrincipal();

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
        bool buscarCancion(int idCancionBuscada, Cancion& regCancion);
        bool buscarArtista(int idArtistaBuscada, Artista& regArtista);
        bool buscarAlbum(int idAlbumBuscado, Album& regAlbum);

        int contarRegistros(const char* nombreArchivo, int tamanioRegistro);

    private:
        // --- MENÚS ---
        void menuReportes();
        void menuCargas();
        void menuConfiguracion();

        // --- REPORTES ---
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();

        // --- CARGAS  ---
        void cargarNuevaCancionEnLista();
        void cargarNuevaSuscripcion();
};

#endif // MUSICON_H
