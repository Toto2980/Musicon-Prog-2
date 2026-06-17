#include "../include/ArchivoPlaylist.h"
#include "../include/InputHelper.h"
#include <cstdio>

using namespace std;

ArchivoPlaylist::ArchivoPlaylist(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

bool ArchivoPlaylist::Guardar(Playlist reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

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

bool ArchivoPlaylist::Modificar(int pos, Playlist reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Playlist), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

int ArchivoPlaylist::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Playlist);
    fclose(p);
    return cant;
}

int ArchivoPlaylist::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size < static_cast<long>(sizeof(Playlist))) {
        fclose(p);
        return 1;
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

int ArchivoPlaylist::BuscarPorID(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Playlist aux;
    int i = 0;
    while (fread(&aux, sizeof(Playlist), 1, p)) {
        if (aux.getIdPlaylist() == id && aux.getEstado()) {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

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
