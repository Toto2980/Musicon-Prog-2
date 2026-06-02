#include "../include/ArchivoSuscriptores.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

ArchivoSuscriptores::ArchivoSuscriptores(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoSuscriptores::Guardar(Suscriptor reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return ok;
}

Suscriptor ArchivoSuscriptores::Leer(int pos) {
    Suscriptor reg;
    reg.setEstado(false);
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Suscriptor), SEEK_SET);
    fread(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return reg;
}

int ArchivoSuscriptores::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Suscriptor);
    fclose(p);
    return cant;
}

int ArchivoSuscriptores::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Suscriptor)), SEEK_END);
    Suscriptor ultimo;
    if (fread(&ultimo, sizeof(Suscriptor), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdSuscriptor() + 1;
}

Suscriptor* ArchivoSuscriptores::LeerTodos(int &cantidad) {
    cantidad = ObtenerCantidadRegistros();
    if (cantidad <= 0) return nullptr;

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) {
        cantidad = 0;
        return nullptr;
    }

    Suscriptor *buffer = new Suscriptor[cantidad];
    int leidos = fread(buffer, sizeof(Suscriptor), cantidad, p);
    fclose(p);

    if (leidos != cantidad) {
        cantidad = leidos;
    }
    return buffer;
}

bool ArchivoSuscriptores::Modificar(int pos, Suscriptor reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Suscriptor), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return ok;
}

int ArchivoSuscriptores::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        if(aux.getIdSuscriptor() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoSuscriptores::BuscarPosicionPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    std::string nombreBuscado = InputHelper::trim(nombre);
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        // DEBUG: Descomenta esto para ver qué lee
        // cout << "Leido: " << aux.getNombre() << " vs Buscado: " << nombreBuscado << endl;

        std::string nombreArchivo = InputHelper::trim(aux.getNombre());
        if(InputHelper::sonIgualesSinMayusculas(nombreArchivo, nombreBuscado) && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoSuscriptores::BuscarPosicionPorDNI(const char* dni) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        if(strcmp(aux.getDni(), dni) == 0 && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
