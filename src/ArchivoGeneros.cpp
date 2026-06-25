/**
 * PATRON: Repository
 * Esta clase encapsula todo el acceso al archivo binario de generos musicales.
 * La capa GeneroManager no sabe como se guardan los datos — solo pide Guardar/Leer/Buscar.
 *
 * COMO FUNCIONA EL ARCHIVO BINARIO:
 *   - Cada Genero ocupa exactamente sizeof(Genero) bytes en disco.
 *   - La posicion del registro 'pos' en el archivo = pos * sizeof(Genero) bytes desde el inicio.
 *   - La cantidad de registros = tamano del archivo (ftell en SEEK_END) / sizeof(Genero).
 *
 * BuscarOCrear es el metodo "inteligente": si el genero ya existe lo devuelve,
 * si no existe lo crea automaticamente. Muy util durante la importacion CSV.
 */

#include "../include/ArchivoGeneros.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo binario que usara esta instancia. */
ArchivoGeneros::ArchivoGeneros(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

/**
 * Agrega un genero al FINAL del archivo.
 * Modo "ab" (append binary): crea el archivo si no existe.
 */
bool ArchivoGeneros::Guardar(Genero reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee el genero en la posicion 'pos' del archivo.
 * fseek posiciona el puntero en el byte exacto del registro.
 * Si falla, retorna un Genero con estado=false (centinela de error).
 */
Genero ArchivoGeneros::Leer(int pos) {
    Genero reg;
    reg.setEstado(false);
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Genero), SEEK_SET);
    fread(&reg, sizeof(Genero), 1, p);
    fclose(p);
    return reg;
}

/**
 * Calcula la cantidad total de registros.
 * Tecnica: ir al final con SEEK_END, leer bytes con ftell(), dividir por sizeof(Genero).
 */
int ArchivoGeneros::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Genero);
    fclose(p);
    return cant;
}

/**
 * Genera un ID unico leyendo el ultimo registro y sumando 1.
 * Si el archivo no existe o esta vacio, devuelve 1 (primer ID).
 * El cast a long es necesario porque sizeof devuelve size_t (sin signo).
 */
int ArchivoGeneros::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Genero)), SEEK_END);
    Genero ultimo;
    if (fread(&ultimo, sizeof(Genero), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdGeneros() + 1;
}

/**
 * Busca la posicion de un genero por su ID (solo activos).
 * Recorre el archivo de principio a fin hasta encontrar el ID.
 * Retorna -1 si no existe o esta dado de baja.
 */
int ArchivoGeneros::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Genero aux;
    int pos = 0;
    while(fread(&aux, sizeof(Genero), 1, p)) {
        if(aux.getIdGeneros() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca el ID de un genero por su nombre (sin distincion de mayusculas/minusculas).
 * Retorna el ID si lo encuentra activo, -1 si no existe.
 * Se usa antes de crear un genero nuevo para evitar duplicados.
 */
int ArchivoGeneros::BuscarIDPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Genero aux;
    while(fread(&aux, sizeof(Genero), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return aux.getIdGeneros();
        }
    }
    fclose(p);
    return -1;
}

/**
 * Sobrescribe el registro en la posicion 'pos' con el nuevo valor.
 * Modo "rb+" = lectura+escritura sin truncar. Permite modificacion puntual.
 */
bool ArchivoGeneros::Modificar(int pos, Genero reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Genero), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/** Retorna el objeto Genero completo dado su ID. Si no existe, retorna estado=false. */
Genero ArchivoGeneros::BuscarPorID(int id) {
    Genero reg;
    reg.setEstado(false);
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    return reg;
}

/**
 * METODO INTELIGENTE: Busca un genero por nombre. Si no existe, lo crea automaticamente.
 * Siempre devuelve un ID valido, lo que simplifica mucho la importacion CSV.
 * Pasos: 1) limpiar nombre, 2) buscar si existe, 3) si no, crear y guardar.
 */
int ArchivoGeneros::BuscarOCrear(string nombreGenero) {
    string nombreLimpio = InputHelper::trim(nombreGenero);
    if (nombreLimpio.empty()) return 0; // ID 0 = "Sin Genero" por defecto

    // 1. Buscar si ya existe
    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) {
        return idExistente; // Ya existe, devolvemos su ID
    }

    // 2. Si no existe, crear uno nuevo
    Genero nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdGeneros(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Genero creado: " << nombreLimpio << " (ID: " << nuevoId << ")" << endl;

    return nuevoId;
}
