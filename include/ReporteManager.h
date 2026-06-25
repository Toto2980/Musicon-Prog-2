/**
 * Este archivo define la clase ReporteManager, responsable de generar todos los reportes y estadisticas
 * de la aplicacion Musicon. Utiliza algoritmos optimizados con mapas para evitar bucles O(N²) y proporciona
 * informes sobre reproducciones, rankings y analisis de datos.
 */

#ifndef REPORTEMANAGER_H
#define REPORTEMANAGER_H

#include "ArchivoCanciones.h"
#include "ArchivoAlbum.h"
#include "ArchivoArtistas.h"
#include "ArchivoGeneros.h"
#include "ArchivoSuscriptores.h"
#include "DetallePlaylist.h"
#include "ArchivoPlaylist.h"
#include "Accesos.h"

/** Responsable de generar reportes y estadisticas de Musicon. */
class ReporteManager {
public:
    /** Muestra el menu principal de reportes con opciones para diferentes estadisticas. */
    void MostrarMenuReportes();

    /** Reporte de reproducciones anuales agrupadas por mes. */
    void reporteReproduccionesAnuales();

    /** Reporte de reproducciones por suscriptor. */
    void reporteReproduccionesPorSuscriptor();

    /** Reporte de reproducciones por genero. */
    void reporteReproduccionesPorGenero();

    /** Reporte de reproducciones por cancion. */
    void reporteReproduccionesPorCancion();

    /** Lista canciones agrupadas por genero. */
    void reporteListarCancionesPorGenero();

    /** Cantidad de canciones por artista. */
    void reporteCantidadCancionesPorArtista();

    /** Canciones agregadas por usuario en listas. */
    void reporteCancionesPorUsuarioEnListas();

    /** Busqueda inteligente de cancion en listas. */
    void reporteBuscarCancionEnListasSmart();

    /** Ranking de canciones mas reproducidas. */
    void reporteRankingCanciones();

    /** Informe completo de suscriptores con sus reproducciones totales. */
    void reporteUsuarios();

    /** Exporta el informe de suscriptores a un archivo CSV. */
    void exportarReporteSuscriptoresCSV();
};

#endif // REPORTEMANAGER_H
