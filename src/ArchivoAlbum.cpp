/**
 * PATRÓN: Repository
 * Esta clase encapsula todo el acceso al archivo binario de álbumes.
 * La capa CancionManager no sabe cómo se guardan los álbumes — solo llama a BuscarOCrear.
 *
 * RELACIÓN ARTISTA → ALBUM → CANCION:
 *   - Un álbum pertenece a un artista (_idArtista).
 *   - Una canción pertenece a un álbum (_idAlbum).
 *   - Estos son IDs que actúan como "claves foráneas" (igual que en SQL).
 *   - No almacenamos el nombre del artista en el álbum — solo su ID.
 *     Así, si el artista cambia de nombre, no hay que actualizar todos sus álbumes.
 *
 * BuscarOCrear combina búsqueda y creación para simplificar la importación CSV.
 */

#include "../include/ArchivoAlbum.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo binario que usará esta instancia. */
ArchivoAlbum::ArchivoAlbum(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

/**
 * Agrega un álbum al FINAL del archivo.
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
 * Lee el álbum en la posición 'pos' del archivo.
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
 * Calcula la cantidad total de álbumes guardados.
 * Técnica: ir al final del archivo (SEEK_END) y dividir los bytes por sizeof(Album).
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
 * Genera un ID único leyendo el último registro y sumando 1.
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
 * Busca la posición de un álbum por su ID (solo activos).
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
 * Busca el ID de un álbum por su título (sin distinción de mayúsculas/minúsculas).
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
 * MÉTODO INTELIGENTE: Busca un álbum por título Y artista. Si no existe, lo crea.
 * La búsqueda considera AMBOS criterios porque el mismo título puede pertenecer
 * a artistas distintos (ej: dos artistas tienen un álbum llamado "Vol. 1").
 * Siempre devuelve un ID válido, simplificando la importación CSV.
 */
int ArchivoAlbum::BuscarOCrear(string tituloAlbum, int idArtista) {
    string tituloLimpio = InputHelper::trim(tituloAlbum);
    if (tituloLimpio.empty()) return 0; // ID 0 = "Sin Album" por defecto

    // 1. Buscar coincidencia exacta de título Y artista (ambos deben coincidir)
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

    // 2. Si no existe, crear uno nuevo con año 0 (desconocido)
    Album nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdAlbum(nuevoId);
    nuevo.setTitulo(tituloLimpio.c_str());
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0); // Año desconocido al importar desde CSV
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Album creado: " << tituloLimpio << " (ID: " << nuevoId << ")" << endl;

    return nuevoId;
}
