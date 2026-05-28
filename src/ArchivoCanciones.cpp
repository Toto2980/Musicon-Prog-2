#include "../include/ArchivoCanciones.h"
#include "InputHelper.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

ArchivoCanciones::ArchivoCanciones(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoCanciones::Guardar(Canciones reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Canciones), 1, p);
    fclose(p);
    return ok;
}

Canciones ArchivoCanciones::Leer(int pos) {
    Canciones reg;
    reg.setEstado(false);

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Canciones), SEEK_SET);
    fread(&reg, sizeof(Canciones), 1, p);
    fclose(p);

    return reg;
}

int ArchivoCanciones::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Canciones);
    fclose(p);
    return cant;
}

int ArchivoCanciones::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Canciones)), SEEK_END);
    Canciones ultimo;
    if (fread(&ultimo, sizeof(Canciones), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdCancion() + 1;
}

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

bool ArchivoCanciones::Modificar(int pos, Canciones reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Canciones), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Canciones), 1, p);
    fclose(p);
    return ok;
}

Canciones ArchivoCanciones::BuscarPorID(int id) {
    Canciones reg;
    reg.setEstado(false);

    int pos = BuscarPosicion(id);
    if (pos != -1) {
        return Leer(pos);
    }
    return reg;
}

// NUEVO: Implementación de la búsqueda de duplicados
int ArchivoCanciones::BuscarPosicionPorNombreYAlbum(const char* nombre, int idAlbum) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;

    Canciones aux;
    int pos = 0;
    while(fread(&aux, sizeof(Canciones), 1, p)) {
        // Verificamos estado activo, mismo ID de álbum y mismo nombre
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
