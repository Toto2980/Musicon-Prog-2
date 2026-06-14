/*
 * Constantes.h
 * Valores de configuracion y reglas de negocio centralizados.
 * Reemplaza los "numeros magicos" que antes estaban repartidos por el codigo
 * (limite de playlists, codigos de tipo de usuario, id del administrador, etc.).
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

// Namespace 'cfg' (no "musicon" para no chocar con la clase musicon).
namespace cfg {

/* --- Rutas de los archivos de datos (.dat) --- */
namespace archivos {
    const char* const CANCIONES     = "canciones.dat";
    const char* const SUSCRIPTORES  = "suscriptores.dat";
    const char* const ARTISTAS      = "artistas.dat";
    const char* const ALBUMES       = "albumes.dat";
    const char* const GENEROS       = "generos.dat";
    const char* const PLAYLISTS     = "playlists.dat";
    const char* const DETALLE_PL    = "Listas_Canciones.dat";
    const char* const ACCESOS       = "accesos.dat";
}

/* --- Tipo de suscripcion (se persiste como int para mantener el layout .dat) --- */
enum TipoSuscriptor {
    GRATIS = 1,
    PAGO   = 2
};

/* --- Reglas de negocio --- */
const int LIMITE_PLAYLISTS_GRATIS = 3;   // Playlists maximas para el plan gratuito
const int ID_ADMIN                = -1;  // Id reservado para el administrador
const int ID_VISITANTE            = 0;   // Id para usuario no autenticado
const int TOPE_RANKING            = 5;   // Cantidad de puestos en el ranking

} // namespace cfg

#endif // CONSTANTES_H
