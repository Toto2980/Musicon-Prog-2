/**
 * PATRON: Repository
 * Esta clase encapsula todo el acceso al archivo binario de playlists.
 * La capa PlaylistManager no sabe como se guardan los datos — solo pide Guardar/Leer/Modificar.
 *
 * IMPORTANTE — RELACION MUCHOS-A-MUCHOS:
 *   - Una playlist puede tener MUCHAS canciones.
 *   - Una cancion puede estar en MUCHAS playlists.
 *   - Esta relacion se implementa con la tabla "DetallePlaylist" (archivo Listas_Canciones.dat).
 *   - Este archivo (playlists.dat) solo guarda los datos de la playlist en si
 *     (nombre, creador, fecha), NO las canciones que contiene.
 */

#include "../include/ArchivoPlaylist.h"
#include "../include/InputHelper.h"
#include <cstdio>

using namespace std;

/** Guarda el nombre del archivo binario que usara esta instancia. */
ArchivoPlaylist::ArchivoPlaylist(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

/**
 * Agrega una playlist al FINAL del archivo.
 * Modo "ab" (append binary): crea el archivo si no existe.
 */
bool ArchivoPlaylist::Guardar(Playlist reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee la playlist en la posicion 'pos' del archivo.
 * fseek salta al byte exacto: pos * sizeof(Playlist) desde el inicio.
 * Si falla, retorna una Playlist con estado=false (centinela de error).
 */
Playlist ArchivoPlaylist::Leer(int pos) {
    Playlist reg;
    reg.setEstado(false);
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Playlist), SEEK_SET);
    fread(&reg, sizeof(Playlist), 1, p);
    fclose(p);
    return reg;
}

/**
 * Sobrescribe la playlist en la posicion 'pos' con el nuevo valor.
 * Modo "rb+" = lectura+escritura sin truncar. Permite eliminacion logica
 * (cambiar estado=false sin borrar el registro del archivo).
 */
bool ArchivoPlaylist::Modificar(int pos, Playlist reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Playlist), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Calcula la cantidad total de playlists guardadas.
 * Tecnica: ir al final (SEEK_END), leer bytes con ftell(), dividir por sizeof(Playlist).
 */
int ArchivoPlaylist::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Playlist);
    fclose(p);
    return cant;
}

/**
 * Genera un ID unico leyendo el ultimo registro y sumando 1.
 * Verifica que el archivo tenga al menos un registro antes de leer el ultimo.
 */
int ArchivoPlaylist::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size < static_cast<long>(sizeof(Playlist))) {
        fclose(p);
        return 1; // Archivo vacio o con menos de un registro
    }
    fseek(p, -static_cast<long>(sizeof(Playlist)), SEEK_END);
    Playlist ultimo;
    ultimo.setEstado(false);
    if (fread(&ultimo, sizeof(Playlist), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdPlaylist() + 1;
}

/**
 * Busca la POSICION (indice en el archivo) de una playlist por su ID.
 * Solo considera playlists activas (estado=true).
 * Retorna -1 si no la encuentra.
 */
int ArchivoPlaylist::BuscarPorID(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Playlist aux;
    int i = 0;
    while (fread(&aux, sizeof(Playlist), 1, p)) {
        if (aux.getIdPlaylist() == id && aux.getEstado()) {
            fclose(p);
            return i; // Devuelve la posicion (indice), no el ID
        }
        i++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca la posicion de una playlist por su nombre exacto (sin mayusculas).
 * Retorna -1 si no la encuentra activa.
 * Se usa para navegar a una playlist conociendo solo su nombre.
 */
int ArchivoPlaylist::BuscarPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Playlist aux;
    int i = 0;
    while (fread(&aux, sizeof(Playlist), 1, p)) {
        if (InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
