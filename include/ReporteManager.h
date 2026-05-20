/**
 * Este archivo define la clase ReporteManager, responsable de generar todos los reportes y estadísticas
 * de la aplicación Musicon. Utiliza algoritmos optimizados con mapas para evitar bucles O(N²) y proporciona
 * informes sobre reproducciones, rankings y análisis de datos.
 */

#ifndef REPORTEMANAGER_H
#define REPORTEMANAGER_H

#include "ArchivoCanciones.h"
#include "ArchivoAlbum.h"
#include "ArchivoArtistas.h"
#include "ArchivoGeneros.h"
#include "ArchivoSuscriptores.h"
#include "DetallePlaylist.h"
#include "Playlist.h"
#include "Accesos.h"

/** Responsable de generar reportes y estadísticas de Musicon. */
class ReporteManager {
private:
    /** Función helper para verificar si una cadena contiene una subcadena. Parámetros: texto - Texto principal, busqueda - Subcadena a buscar. Retorna: true si contiene. */
    bool contieneSubcadenaLocal(const char* texto, const char* busqueda);

public:
    /** Muestra el menú principal de reportes con opciones para diferentes estadísticas. */
    void MostrarMenuReportes();

    /** Reporte de reproducciones anuales agrupadas por mes. */
    void reporteReproduccionesAnuales();

    /** Reporte de reproducciones por suscriptor. */
    void reporteReproduccionesPorSuscriptor();

    /** Reporte de reproducciones por género. */
    void reporteReproduccionesPorGenero();

    /** Reporte de reproducciones por canción. */
    void reporteReproduccionesPorCancion();

    /** Lista canciones agrupadas por género. */
    void reporteListarCancionesPorGenero();

    /** Cantidad de canciones por artista. */
    void reporteCantidadCancionesPorArtista();

    /** Canciones agregadas por usuario en listas. */
    void reporteCancionesPorUsuarioEnListas();

    /** Búsqueda inteligente de canción en listas. */
    void reporteBuscarCancionEnListasSmart();

    /** Ranking de canciones más reproducidas. */
    void reporteRankingCanciones();
};

#endif // REPORTEMANAGER_H
