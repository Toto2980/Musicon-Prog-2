/*
 * ArchivoGeneros.cpp
 * Persistencia de generos sobre ArchivoBinario<Genero>.
 */

#include "../include/ArchivoGeneros.h"
#include "../include/ArchivoBinario.h"
#include "../include/Texto.h"
#include <iostream>
#include <vector>

using namespace std;

ArchivoGeneros::ArchivoGeneros(string nombreArchivo) : _nombreArchivo(nombreArchivo) {}

bool ArchivoGeneros::Guardar(Genero reg) {
    return ArchivoBinario<Genero>(_nombreArchivo).agregar(reg);
}

Genero ArchivoGeneros::Leer(int pos) {
    Genero reg;
    reg.setEstado(false);
    ArchivoBinario<Genero>(_nombreArchivo).leer(pos, reg);
    return reg;
}

int ArchivoGeneros::ObtenerCantidadRegistros() {
    return ArchivoBinario<Genero>(_nombreArchivo).contar();
}

int ArchivoGeneros::GenerarIDNuevo() {
    ArchivoBinario<Genero> af(_nombreArchivo);
    int n = af.contar();
    if (n <= 0) return 1;
    Genero ultimo;
    if (!af.leer(n - 1, ultimo)) return 1;
    return ultimo.getIdGeneros() + 1;
}

int ArchivoGeneros::BuscarPosicion(int id) {
    vector<Genero> todos = ArchivoBinario<Genero>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getIdGeneros() == id && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoGeneros::BuscarIDPorNombre(const char* nombre) {
    vector<Genero> todos = ArchivoBinario<Genero>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (Texto::igualesSinMayusculas(todos[i].getNombre(), nombre) && todos[i].getEstado()) {
            return todos[i].getIdGeneros();
        }
    }
    return -1;
}

Genero ArchivoGeneros::BuscarPorID(int id) {
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    Genero reg;
    reg.setEstado(false);
    return reg;
}

int ArchivoGeneros::BuscarOCrear(string nombreGenero) {
    string nombreLimpio = Texto::trim(nombreGenero);
    if (nombreLimpio.empty()) return 0;

    int idExistente = BuscarIDPorNombre(nombreLimpio.c_str());
    if (idExistente != -1) return idExistente;

    Genero nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdGeneros(nuevoId);
    nuevo.setNombre(nombreLimpio.c_str());
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Genero creado: " << nombreLimpio
         << " (ID: " << nuevoId << ")" << endl;
    return nuevoId;
}
