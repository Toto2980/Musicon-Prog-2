/**
 * PATRÓN: Repository
 * Esta clase encapsula todo el acceso al archivo binario de artistas.
 * La capa ArtistaManager no sabe cómo se guardan los datos — solo pide Guardar/Leer/Buscar.
 *
 * REGLA DE ORO DEL ARCHIVO BINARIO:
 *   - Todos los registros tienen el mismo tamaño: sizeof(Artista) bytes.
 *   - La posición del registro 'pos' = pos * sizeof(Artista) bytes desde el inicio.
 *   - La cantidad de registros = tamaño total del archivo / sizeof(Artista).
 *
 * BuscarOCrear es el "cerebro" de la importación: busca un artista por nombre y,
 * si no existe, lo crea automáticamente. Siempre devuelve un ID válido.
 */

#include "../include/ArchivoArtistas.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo binario que usará esta instancia. */
ArchivoArtistas::ArchivoArtistas(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

/**
 * Agrega un artista al FINAL del archivo.
 * Modo "ab" (append binary): crea el archivo si no existe.
 */
bool ArchivoArtistas::Guardar(Artista reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee el artista en la posición 'pos' del archivo.
 * fseek salta pos * sizeof(Artista) bytes desde el inicio del archivo.
 * Si el archivo no existe, retorna un Artista con estado=false (centinela de error).
 */
Artista ArchivoArtistas::Leer(int pos) {
    Artista reg;
    reg.setEstado(false); // Estado por defecto si falla lectura
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Artista), SEEK_SET);
    fread(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return reg;
}

/**
 * Sobrescribe el artista en la posición 'pos' con el nuevo valor.
 * Modo "rb+" = lectura+escritura sin truncar. Permite eliminación lógica.
 */
bool ArchivoArtistas::Modificar(int pos, Artista reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Artista), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return ok;
}

/**
 * Calcula la cantidad total de artistas en el archivo.
 * Técnica: ir al final (SEEK_END), obtener tamaño con ftell(), dividir por sizeof(Artista).
 */
int ArchivoArtistas::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Artista);
    fclose(p);
    return cant;
}

/**
 * Genera un ID autoincremental leyendo el último registro.
 * Si el archivo no existe o está vacío, devuelve 1 (primer ID).
 */
int ArchivoArtistas::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    // Retrocede al inicio del último registro con offset negativo desde el final
    fseek(p, -static_cast<long>(sizeof(Artista)), SEEK_END);
    Artista ultimo;
    if (fread(&ultimo, sizeof(Artista), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdArtista() + 1;
}

/**
 * Busca la posición de un artista por su ID (solo activos).
 * Recorre secuencialmente hasta encontrar el ID. Retorna -1 si no lo encuentra.
 */
int ArchivoArtistas::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Artista aux;
    int pos = 0;
    while(fread(&aux, sizeof(Artista), 1, p)) {
        if(aux.getIdArtista() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca la posición de un artista por su nombre (case-insensitive).
 * Devuelve la posición en el archivo, no el ID.
 */
int ArchivoArtistas::BuscarPosicionPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Artista aux;
    int pos = 0;
    while(fread(&aux, sizeof(Artista), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/** Devuelve el ID de un artista buscando por nombre. Retorna -1 si no existe. */
int ArchivoArtistas::BuscarIDPorNombre(const char* nombre) {
    int pos = BuscarPosicionPorNombre(nombre);
    if (pos >= 0) {
        return Leer(pos).getIdArtista();
    }
    return -1;
}

/** Retorna el objeto Artista completo dado su ID. Si no existe, retorna estado=false. */
Artista ArchivoArtistas::BuscarPorID(int id) {
    Artista reg;
    reg.setEstado(false);
    int pos = BuscarPosicion(id);
    if (pos >= 0) {
        return Leer(pos);
    }
    return reg;
}

// --- CEREBRO: BUSCAR O CREAR ---
int ArchivoArtistas::BuscarOCrear(string nombreArtista) {
    // 1. Limpiar el nombre (quitar espacios extra)
    string nombreLimpio = InputHelper::trim(nombreArtista);
    if (nombreLimpio.empty()) return 0; // Validación básica

    // 2. Buscar si ya existe
    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) {
        return idExistente; // Ya existe, retornamos su ID
    }

    // 3. Si no existe, CREAR
    Artista nuevo;
    int nuevoId = GenerarIDNuevo(); // ID Autoincremental

    nuevo.setIdArtista(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    if(Guardar(nuevo)) {
        cout << "   [INFO] Artista nuevo creado: " << nombreLimpio << " (ID: " << nuevoId << ")" << endl;
        return nuevoId;
    }

    return -1; // Error al guardar
}
