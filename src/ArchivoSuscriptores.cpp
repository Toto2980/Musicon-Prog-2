/*
 * ArchivoSuscriptores.cpp
 * Persistencia de suscriptores sobre ArchivoBinario<Suscriptor>.
 */

#include "../include/ArchivoSuscriptores.h"
#include "../include/ArchivoBinario.h"
#include "../include/Texto.h"
#include <cstring>
#include <vector>

using namespace std;

ArchivoSuscriptores::ArchivoSuscriptores(string nombreArchivo) : _nombreArchivo(nombreArchivo) {}

bool ArchivoSuscriptores::Guardar(Suscriptor reg) {
    return ArchivoBinario<Suscriptor>(_nombreArchivo).agregar(reg);
}

Suscriptor ArchivoSuscriptores::Leer(int pos) {
    Suscriptor reg;
    reg.setEstado(false);
    ArchivoBinario<Suscriptor>(_nombreArchivo).leer(pos, reg);
    return reg;
}

int ArchivoSuscriptores::ObtenerCantidadRegistros() {
    return ArchivoBinario<Suscriptor>(_nombreArchivo).contar();
}

int ArchivoSuscriptores::GenerarIDNuevo() {
    ArchivoBinario<Suscriptor> af(_nombreArchivo);
    int n = af.contar();
    if (n <= 0) return 1;
    Suscriptor ultimo;
    if (!af.leer(n - 1, ultimo)) return 1;
    return ultimo.getIdSuscriptor() + 1;
}

Suscriptor* ArchivoSuscriptores::LeerTodos(int &cantidad) {
    vector<Suscriptor> regs = ArchivoBinario<Suscriptor>(_nombreArchivo).leerTodos();
    cantidad = static_cast<int>(regs.size());
    if (cantidad <= 0) return nullptr;

    // Se mantiene la firma original (arreglo dinamico); el llamador hace delete[].
    Suscriptor* buffer = new Suscriptor[cantidad];
    for (int i = 0; i < cantidad; ++i) buffer[i] = regs[i];
    return buffer;
}

bool ArchivoSuscriptores::Modificar(int pos, Suscriptor reg) {
    return ArchivoBinario<Suscriptor>(_nombreArchivo).escribir(pos, reg);
}

int ArchivoSuscriptores::BuscarPosicion(int id) {
    vector<Suscriptor> todos = ArchivoBinario<Suscriptor>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getIdSuscriptor() == id && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoSuscriptores::BuscarPosicionPorNombre(const char* nombre) {
    string nombreBuscado = Texto::trim(nombre);
    vector<Suscriptor> todos = ArchivoBinario<Suscriptor>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        string nombreArchivo = Texto::trim(todos[i].getNombre());
        if (Texto::igualesSinMayusculas(nombreArchivo, nombreBuscado) && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoSuscriptores::BuscarPosicionPorDNI(const char* dni) {
    vector<Suscriptor> todos = ArchivoBinario<Suscriptor>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (strcmp(todos[i].getDni(), dni) == 0 && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
