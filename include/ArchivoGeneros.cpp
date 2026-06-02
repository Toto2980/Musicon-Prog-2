#include "../include/ArchivoGeneros.h"
#include "../include/InputHelper.h" // Necesario para trim
#include <cstdio>
#include <cstring>
#include <iostream> // Para debug cout
#include <cctype>

using namespace std;


ArchivoGeneros::ArchivoGeneros(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

bool ArchivoGeneros::Guardar(Genero reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

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

int ArchivoGeneros::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Genero);
    fclose(p);
    return cant;
}

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

Genero ArchivoGeneros::BuscarPorID(int id) {
    Genero reg;
    reg.setEstado(false);
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    return reg;
}

// --- IMPLEMENTACIÓN INTELIGENTE ---
int ArchivoGeneros::BuscarOCrear(string nombreGenero) {
    string nombreLimpio = InputHelper::trim(nombreGenero);
    if (nombreLimpio.empty()) return 0; // O un ID por defecto para "Sin Genero"

    // 1. Buscar si existe
    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) {
        return idExistente;
    }

    // 2. Si no existe, crear
    Genero nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdGeneros(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Genero creado: " << nombreLimpio << " (ID: " << nuevoId << ")" << endl;

    return nuevoId;
}
