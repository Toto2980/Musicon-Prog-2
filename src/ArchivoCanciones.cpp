/*
 * ArchivoCanciones.cpp
 * Persistencia de canciones. Delega la E/S binaria de bajo nivel en
 * ArchivoBinario<Canciones> y solo aporta la logica especifica del dominio
 * (busquedas por id/nombre, generacion de id).
 */

#include "../include/ArchivoCanciones.h"
#include "../include/ArchivoBinario.h"
#include "../include/Texto.h"
#include <vector>

using namespace std;

ArchivoCanciones::ArchivoCanciones(string nombreArchivo) : _nombreArchivo(nombreArchivo) {}

bool ArchivoCanciones::Guardar(Canciones reg) {
    return ArchivoBinario<Canciones>(_nombreArchivo).agregar(reg);
}

Canciones ArchivoCanciones::Leer(int pos) {
    Canciones reg;
    reg.setEstado(false); // estado por defecto si la lectura falla
    ArchivoBinario<Canciones>(_nombreArchivo).leer(pos, reg);
    return reg;
}

int ArchivoCanciones::ObtenerCantidadRegistros() {
    return ArchivoBinario<Canciones>(_nombreArchivo).contar();
}

int ArchivoCanciones::GenerarIDNuevo() {
    ArchivoBinario<Canciones> af(_nombreArchivo);
    int n = af.contar();
    if (n <= 0) return 1;
    Canciones ultimo;
    if (!af.leer(n - 1, ultimo)) return 1;
    return ultimo.getIdCancion() + 1;
}

int ArchivoCanciones::BuscarPosicion(int id) {
    vector<Canciones> todos = ArchivoBinario<Canciones>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getIdCancion() == id && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool ArchivoCanciones::Modificar(int pos, Canciones reg) {
    return ArchivoBinario<Canciones>(_nombreArchivo).escribir(pos, reg);
}

Canciones ArchivoCanciones::BuscarPorID(int id) {
    int pos = BuscarPosicion(id);
    if (pos != -1) return Leer(pos);
    Canciones reg;
    reg.setEstado(false);
    return reg;
}

int ArchivoCanciones::BuscarPosicionPorNombreYAlbum(const char* nombre, int idAlbum) {
    vector<Canciones> todos = ArchivoBinario<Canciones>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getEstado() &&
            todos[i].getIdAlbum() == idAlbum &&
            Texto::igualesSinMayusculas(todos[i].getNombre(), nombre)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
