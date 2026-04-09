#include "../include/ArchivoArtistas.h"
#include "InputHelper.h" // Necesario para la funci�n trim()
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

/**
 * Compara dos textos sin distinguir mayúsculas y minúsculas.
 */
static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false;
        }
        ++texto1;
        ++texto2;
    }

    return *texto1 == *texto2;
}

ArchivoArtistas::ArchivoArtistas(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoArtistas::Guardar(Artista reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return ok;
}

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

bool ArchivoArtistas::Modificar(int pos, Artista reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Artista), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Artista), 1, p);
    fclose(p);
    return ok;
}

int ArchivoArtistas::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Artista);
    fclose(p);
    return cant;
}

int ArchivoArtistas::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Artista)), SEEK_END);
    Artista ultimo;
    if (fread(&ultimo, sizeof(Artista), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdArtista() + 1;
}

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

int ArchivoArtistas::BuscarPosicionPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Artista aux;
    int pos = 0;
    while(fread(&aux, sizeof(Artista), 1, p)) {
        // getNombre() pertenece directamente a la clase Artista.
        if(sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoArtistas::BuscarIDPorNombre(const char* nombre) {
    int pos = BuscarPosicionPorNombre(nombre);
    if (pos >= 0) {
        return Leer(pos).getIdArtista();
    }
    return -1;
}

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
    if (nombreLimpio.empty()) return 0; // Validaci�n b�sica

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
