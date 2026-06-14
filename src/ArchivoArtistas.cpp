/*
 * ArchivoArtistas.cpp
 * Persistencia de artistas sobre ArchivoBinario<Artista>.
 */

#include "../include/ArchivoArtistas.h"
#include "../include/ArchivoBinario.h"
#include "../include/Texto.h"
#include <iostream>
#include <vector>

using namespace std;

ArchivoArtistas::ArchivoArtistas(string nombreArchivo) : _nombreArchivo(nombreArchivo) {}

bool ArchivoArtistas::Guardar(Artista reg) {
    return ArchivoBinario<Artista>(_nombreArchivo).agregar(reg);
}

Artista ArchivoArtistas::Leer(int pos) {
    Artista reg;
    reg.setEstado(false);
    ArchivoBinario<Artista>(_nombreArchivo).leer(pos, reg);
    return reg;
}

bool ArchivoArtistas::Modificar(int pos, Artista reg) {
    return ArchivoBinario<Artista>(_nombreArchivo).escribir(pos, reg);
}

int ArchivoArtistas::ObtenerCantidadRegistros() {
    return ArchivoBinario<Artista>(_nombreArchivo).contar();
}

int ArchivoArtistas::GenerarIDNuevo() {
    ArchivoBinario<Artista> af(_nombreArchivo);
    int n = af.contar();
    if (n <= 0) return 1;
    Artista ultimo;
    if (!af.leer(n - 1, ultimo)) return 1;
    return ultimo.getIdArtista() + 1;
}

int ArchivoArtistas::BuscarPosicion(int id) {
    vector<Artista> todos = ArchivoBinario<Artista>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getIdArtista() == id && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoArtistas::BuscarPosicionPorNombre(const char* nombre) {
    vector<Artista> todos = ArchivoBinario<Artista>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (Texto::igualesSinMayusculas(todos[i].getNombre(), nombre) && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoArtistas::BuscarIDPorNombre(const char* nombre) {
    int pos = BuscarPosicionPorNombre(nombre);
    if (pos >= 0) return Leer(pos).getIdArtista();
    return -1;
}

Artista ArchivoArtistas::BuscarPorID(int id) {
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    Artista reg;
    reg.setEstado(false);
    return reg;
}

int ArchivoArtistas::BuscarOCrear(string nombreArtista) {
    string nombreLimpio = Texto::trim(nombreArtista);
    if (nombreLimpio.empty()) return 0;

    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) return idExistente;

    Artista nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdArtista(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    if (Guardar(nuevo)) {
        cout << "   [INFO] Artista nuevo creado: " << nombreLimpio
             << " (ID: " << nuevoId << ")" << endl;
        return nuevoId;
    }
    return -1;
}
