/**
 * PATRON: Repository
 * Esta clase encapsula todo el acceso al archivo binario de albumes.
 * La capa CancionManager no sabe como se guardan los albumes — solo llama a BuscarOCrear.
 *
 * RELACION ARTISTA → ALBUM → CANCION:
 *   - Un album pertenece a un artista (_idArtista).
 *   - Una cancion pertenece a un album (_idAlbum).
 *   - Estos son IDs que actuan como "claves foraneas" (igual que en SQL).
 *   - No almacenamos el nombre del artista en el album — solo su ID.
 *     Asi, si el artista cambia de nombre, no hay que actualizar todos sus albumes.
 *
 * BuscarOCrear combina busqueda y creacion para simplificar la importacion CSV.
 */

#include "../include/ArchivoAlbum.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo binario que usara esta instancia. */
ArchivoAlbum::ArchivoAlbum(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

/**
 * Agrega un album al FINAL del archivo.
 * Modo "ab" (append binary): crea el archivo si no existe.
 */
bool ArchivoAlbum::Guardar(Album reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee el album en la posicion 'pos' del archivo.
 * Calcula el byte de inicio: pos * sizeof(Album) desde el principio del archivo.
 * Si falla, retorna un Album con estado=false (centinela de error).
 */
Album ArchivoAlbum::Leer(int pos) {
    Album reg;
    reg.setEstado(false);
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Album), SEEK_SET);
    fread(&reg, sizeof(Album), 1, p);
    fclose(p);
    return reg;
}

/**
 * Calcula la cantidad total de albumes guardados.
 * Tecnica: ir al final del archivo (SEEK_END) y dividir los bytes por sizeof(Album).
 */
int ArchivoAlbum::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Album);
    fclose(p);
    return cant;
}

/**
 * Genera un ID unico leyendo el ultimo registro y sumando 1.
 * El cast a long es necesario porque sizeof devuelve size_t (unsigned) y fseek espera long (signed).
 */
int ArchivoAlbum::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Album)), SEEK_END);
    Album ultimo;
    if (fread(&ultimo, sizeof(Album), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdAlbum() + 1;
}

/**
 * Busca la posicion de un album por su ID (solo activos).
 * Recorre secuencialmente todo el archivo. Retorna -1 si no lo encuentra.
 */
int ArchivoAlbum::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Album aux;
    int pos = 0;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(aux.getIdAlbum() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca el ID de un album por su titulo (sin distincion de mayusculas/minusculas).
 * Se usa para verificar si ya existe antes de crear uno nuevo.
 * Retorna el ID si lo encuentra activo, -1 si no existe.
 */
int ArchivoAlbum::BuscarIDPorTitulo(const char* titulo) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Album aux;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getTitulo(), titulo) && aux.getEstado()) {
            fclose(p);
            return aux.getIdAlbum();
        }
    }
    fclose(p);
    return -1;
}

/** Retorna el objeto Album completo dado su ID. Si no existe, retorna estado=false. */
Album ArchivoAlbum::BuscarPorID(int id) {
    Album reg;
    reg.setEstado(false);
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    return reg;
}

/**
 * METODO INTELIGENTE: Busca un album por titulo Y artista. Si no existe, lo crea.
 * La busqueda considera AMBOS criterios porque el mismo titulo puede pertenecer
 * a artistas distintos (ej: dos artistas tienen un album llamado "Vol. 1").
 * Siempre devuelve un ID valido, simplificando la importacion CSV.
 */
int ArchivoAlbum::BuscarOCrear(string tituloAlbum, int idArtista) {
    string tituloLimpio = InputHelper::trim(tituloAlbum);
    if (tituloLimpio.empty()) return 0; // ID 0 = "Sin Album" por defecto

    // 1. Buscar coincidencia exacta de titulo Y artista (ambos deben coincidir)
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p != NULL) {
        Album aux;
        while(fread(&aux, sizeof(Album), 1, p)) {
            if(aux.getEstado() &&
               aux.getIdArtista() == idArtista &&
               InputHelper::sonIgualesSinMayusculas(aux.getTitulo(), tituloLimpio.c_str())) {
                fclose(p);
                return aux.getIdAlbum(); // Encontrado: devolvemos su ID
            }
        }
        fclose(p);
    }

    // 2. Si no existe, crear uno nuevo con ano 0 (desconocido)
    Album nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdAlbum(nuevoId);
    nuevo.setTitulo(tituloLimpio.c_str());
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0); // Ano desconocido al importar desde CSV
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Album creado: " << tituloLimpio << " (ID: " << nuevoId << ")" << endl;

    return nuevoId;
}
