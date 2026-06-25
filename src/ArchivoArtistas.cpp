/**
 * PATRON: Repository
 * Esta clase encapsula todo el acceso al archivo binario de artistas.
 * La capa ArtistaManager no sabe como se guardan los datos.
 *
 * REGLA DE ORO DEL ARCHIVO BINARIO:
 *   - Todos los registros tienen el mismo tamano: sizeof(Artista) bytes.
 *   - La posicion del registro 'pos' = pos * sizeof(Artista) bytes desde el inicio.
 *   - La cantidad de registros = tamano total del archivo / sizeof(Artista).
 *
 * MODOS DE FOPEN:
 *   "ab"  -> append binary:  agrega al final, crea si no existe. Para Guardar().
 *   "rb"  -> read binary:    solo lectura. Para Leer(), ObtenerCantidad(), Buscar*().
 *   "rb+" -> read+write:     lee y escribe SIN truncar. Para Modificar() y eliminacion logica.
 *
 * BuscarOCrear es el "cerebro" de la importacion: busca un artista por nombre y,
 * si no existe, lo crea automaticamente. Siempre devuelve un ID valido.
 */

#include "../include/ArchivoArtistas.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

ArchivoArtistas::ArchivoArtistas(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

/**
 * Guardar -- modo "ab" (append binary)
 *
 * fwrite(&reg, sizeof(Artista), 1, p) escribe sizeof(Artista) bytes
 * desde la direccion de memoria &reg. El archivo crece de a bloques fijos.
 *
 * Por que sizeof(Artista) es siempre el mismo:
 *   Los atributos de Artista son char[] de tamano fijo y bool/int.
 *   No hay punteros ni std::string -- el tamano es constante y predecible.
 */
bool ArchivoArtistas::Guardar(Artista reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return ok;
}

/**
 * Leer -- modo "rb" (read binary)
 *
 * fseek(p, pos * sizeof(Artista), SEEK_SET) salta exactamente pos bloques.
 * Ejemplo: pos=3 -> salta 3*sizeof(Artista) bytes -> queda al inicio del bloque 3.
 * Despues fread() copia sizeof(Artista) bytes desde ahi al objeto reg.
 *
 * Si falla (archivo no existe), retorna Artista con estado=false como centinela.
 */
Artista ArchivoArtistas::Leer(int pos) {
    Artista reg;
    reg.setEstado(false); // Centinela: si falla, el llamador detecta con getEstado()
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Artista), SEEK_SET);
    fread(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return reg;
}

/**
 * Modificar -- modo "rb+" (lectura+escritura sin truncar)
 *
 * "rb+" es el unico modo que permite sobreescribir en el medio del archivo.
 * Con "wb+" truncaria (borraria todo) -- NUNCA usar ese modo para modificar.
 *
 * Esto hace posible la ELIMINACION LOGICA:
 *   reg.setEstado(false);
 *   Modificar(pos, reg);   // sobreescribe el registro con estado=false
 *   // El registro sigue en el archivo pero no aparece en los listados.
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
 * ObtenerCantidadRegistros -- cuenta dividiendo tamano del archivo por tamano de un registro.
 *
 * fseek(p, 0, SEEK_END) mueve el cursor al final del archivo.
 * ftell(p) retorna cuantos bytes hay desde el inicio hasta el cursor.
 * Division entera: bytes_totales / sizeof(Artista) = cantidad exacta de registros.
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
 * GenerarIDNuevo -- ID autoincremental sin tabla de secuencias.
 *
 * Idea: el ultimo registro en el archivo tiene el ID mas alto.
 * fseek(p, -sizeof(Artista), SEEK_END) retrocede UN bloque desde el final.
 * Lee ese bloque -> obtiene su ID -> suma 1.
 *
 * Los IDs NUNCA se reutilizan aunque el artista sea eliminado logicamente.
 * Si hay 10 artistas y se borra el 7, el proximo ID es 11.
 */
int ArchivoArtistas::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1; // Archivo vacio -> primer ID es 1
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    // Offset negativo desde SEEK_END = retrocede desde el final del archivo
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
 * BuscarPosicion -- busqueda lineal O(N) por ID.
 *
 * No hay indice ni arbol B -> hay que leer registro por registro hasta encontrar.
 * Solo retorna activos (getEstado() == true) para que los eliminados logicamente
 * no sean "encontrables" por el sistema.
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
 * BuscarPosicionPorNombre -- busqueda lineal O(N) case-insensitive.
 *
 * Usa InputHelper::sonIgualesSinMayusculas() para no distinguir
 * entre "beatles", "Beatles" y "BEATLES".
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

/** Devuelve el ID buscando por nombre. Retorna -1 si no existe (o esta inactivo). */
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

/**
 * BuscarOCrear -- patron clave de la importacion CSV.
 *
 * Flujo:
 *   1. Limpia espacios del nombre con trim().
 *   2. Busca si ya existe un artista con ese nombre.
 *   3a. Si existe -> retorna su ID (no crea duplicado).
 *   3b. Si no existe -> genera ID nuevo, crea el Artista, lo guarda, retorna su ID.
 *
 * Permite importar un CSV donde "The Beatles" aparece en 50 canciones
 * sin crear 50 registros de artista duplicados.
 */
int ArchivoArtistas::BuscarOCrear(string nombreArtista) {
    string nombreLimpio = InputHelper::trim(nombreArtista);
    if (nombreLimpio.empty()) return 0;

    // Paso 2: buscar existente
    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) {
        return idExistente; // Ya existe
    }

    // Paso 3b: crear nuevo
    Artista nuevo;
    int nuevoId = GenerarIDNuevo();

    nuevo.setIdArtista(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    if(Guardar(nuevo)) {
        cout << "   [INFO] Artista nuevo creado: " << nombreLimpio << " (ID: " << nuevoId << ")" << endl;
        return nuevoId;
    }

    return -1; // Error al guardar
}
