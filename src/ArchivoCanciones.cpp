/**
 * PATRÓN: Repository
 * Esta clase encapsula todo el acceso al archivo binario de canciones.
 * La capa CancionManager no sabe cómo se guardan los datos — solo pide Guardar/Leer/Buscar.
 *
 * CÓMO FUNCIONA UN ARCHIVO BINARIO EN ESTE PROYECTO:
 *   - Los objetos Canciones se escriben uno tras otro, como un arreglo en disco.
 *   - Cada registro ocupa exactamente sizeof(Canciones) bytes.
 *   - Para acceder al registro 'pos': fseek(p, pos * sizeof(Canciones), SEEK_SET).
 *   - Para saber cuántos hay: ftell(fin_archivo) / sizeof(Canciones).
 *
 * NOTA: Canciones no hereda de EntidadPadre porque su layout de memoria
 * es diferente (el ID no está necesariamente al inicio del struct).
 */

#include "../include/ArchivoCanciones.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo binario que usará esta instancia. */
ArchivoCanciones::ArchivoCanciones(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

/**
 * Agrega una canción al FINAL del archivo.
 * "ab" = append binary: crea el archivo si no existe, escribe al final si existe.
 * fwrite escribe un objeto Canciones completo (sizeof(Canciones) bytes).
 */
bool ArchivoCanciones::Guardar(Canciones reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Canciones), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee la canción en la posición 'pos' del archivo.
 * "rb" = read binary: solo lectura.
 * fseek(p, pos * sizeof(Canciones), SEEK_SET) salta al byte exacto del registro 'pos'.
 * Si el archivo no existe, retorna una canción con estado=false (centinela de error).
 */
Canciones ArchivoCanciones::Leer(int pos) {
    Canciones reg;
    reg.setEstado(false); // Estado por defecto si la lectura falla

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Canciones), SEEK_SET);
    fread(&reg, sizeof(Canciones), 1, p);
    fclose(p);

    return reg;
}

/**
 * Calcula cuántos registros hay en el archivo.
 * Técnica: mover el puntero al final con fseek(SEEK_END), leer la posición
 * en bytes con ftell(), y dividir por el tamaño de cada registro.
 */
int ArchivoCanciones::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);              // Va al final del archivo
    int cant = ftell(p) / sizeof(Canciones); // ftell() devuelve el tamaño total en bytes
    fclose(p);
    return cant;
}

/**
 * Genera un ID autoincremental leyendo el último registro.
 * Si el archivo está vacío o no existe, el primer ID es 1.
 * fseek con offset negativo desde SEEK_END posiciona en el último registro.
 */
int ArchivoCanciones::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1; // Archivo vacío: el primer ID es 1
    }
    // Retrocede al inicio del último registro
    fseek(p, -static_cast<long>(sizeof(Canciones)), SEEK_END);
    Canciones ultimo;
    if (fread(&ultimo, sizeof(Canciones), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdCancion() + 1; // ID siguiente = último + 1
}

/**
 * Busca la posición (índice) de una canción por su ID.
 * Solo considera registros con estado=true (activos).
 * Recorre secuencialmente todo el archivo. Retorna -1 si no la encuentra.
 */
int ArchivoCanciones::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;

    Canciones aux;
    int pos = 0;
    while(fread(&aux, sizeof(Canciones), 1, p)) {
        if(aux.getIdCancion() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Sobrescribe el registro en la posición 'pos' con el nuevo valor.
 * "rb+" permite lectura y escritura sin truncar el archivo.
 * Se usa tanto para modificar datos como para hacer eliminación lógica (estado=false).
 */
bool ArchivoCanciones::Modificar(int pos, Canciones reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Canciones), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Canciones), 1, p);
    fclose(p);
    return ok;
}

/**
 * Retorna el objeto Cancion completo dado su ID.
 * Combina BuscarPosicion + Leer para acceso más directo desde los managers.
 * Si el ID no existe, retorna una canción con estado=false.
 */
Canciones ArchivoCanciones::BuscarPorID(int id) {
    Canciones reg;
    reg.setEstado(false);

    int pos = BuscarPosicion(id);
    if (pos != -1) {
        return Leer(pos);
    }
    return reg;
}

/**
 * Busca si ya existe una canción con el mismo nombre en el mismo álbum.
 * Se usa durante la importación CSV para detectar duplicados antes de insertar.
 * Compara nombre (sin mayúsculas) y ID de álbum. Solo considera activos.
 * Retorna la posición si existe, -1 si no.
 */
int ArchivoCanciones::BuscarPosicionPorNombreYAlbum(const char* nombre, int idAlbum) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;

    Canciones aux;
    int pos = 0;
    while(fread(&aux, sizeof(Canciones), 1, p)) {
        // Verifica que esté activo, sea del mismo álbum y tenga el mismo nombre
        if(aux.getEstado() &&
           aux.getIdAlbum() == idAlbum &&
           InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre)) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
