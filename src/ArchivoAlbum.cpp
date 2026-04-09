#include "../include/ArchivoAlbum.h"
#include "InputHelper.h"
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

// ... (M�todos anteriores se mantienen igual) ...

ArchivoAlbum::ArchivoAlbum(string nombreArchivo) { _nombreArchivo = nombreArchivo; }

bool ArchivoAlbum::Guardar(Album reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

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

int ArchivoAlbum::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Album);
    fclose(p);
    return cant;
}

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

int ArchivoAlbum::BuscarIDPorTitulo(const char* titulo) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Album aux;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(sonIgualesSinMayusculas(aux.getTitulo(), titulo) && aux.getEstado()) {
            fclose(p);
            return aux.getIdAlbum();
        }
    }
    fclose(p);
    return -1;
}

Album ArchivoAlbum::BuscarPorID(int id) {
    Album reg;
    reg.setEstado(false);
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    return reg;
}

// --- IMPLEMENTACI�N INTELIGENTE ---
int ArchivoAlbum::BuscarOCrear(string tituloAlbum, int idArtista) {
    string tituloLimpio = InputHelper::trim(tituloAlbum);
    if (tituloLimpio.empty()) return 0; // O un ID gen�rico "Sin Album"

    // 1. Buscar coincidencia exacta de Titulo Y Artista
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p != NULL) {
        Album aux;
        while(fread(&aux, sizeof(Album), 1, p)) {
            if(aux.getEstado() &&
               aux.getIdArtista() == idArtista &&
               sonIgualesSinMayusculas(aux.getTitulo(), tituloLimpio.c_str())) {
                fclose(p);
                return aux.getIdAlbum(); // ENCONTRADO
            }
        }
        fclose(p);
    }

    // 2. Si no existe, crear
    Album nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdAlbum(nuevoId);
    nuevo.setTitulo(tituloLimpio.c_str());
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0); // A�o desconocido por defecto
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Album creado: " << tituloLimpio << " (ID: " << nuevoId << ")" << endl;

    return nuevoId;
}
