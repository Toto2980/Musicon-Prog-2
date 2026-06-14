/*
 * ArchivoAlbum.cpp
 * Persistencia de albumes sobre ArchivoBinario<Album>.
 */

#include "../include/ArchivoAlbum.h"
#include "../include/ArchivoBinario.h"
#include "../include/Texto.h"
#include <iostream>
#include <vector>

using namespace std;

ArchivoAlbum::ArchivoAlbum(string nombreArchivo) : _nombreArchivo(nombreArchivo) {}

bool ArchivoAlbum::Guardar(Album reg) {
    return ArchivoBinario<Album>(_nombreArchivo).agregar(reg);
}

Album ArchivoAlbum::Leer(int pos) {
    Album reg;
    reg.setEstado(false);
    ArchivoBinario<Album>(_nombreArchivo).leer(pos, reg);
    return reg;
}

int ArchivoAlbum::ObtenerCantidadRegistros() {
    return ArchivoBinario<Album>(_nombreArchivo).contar();
}

int ArchivoAlbum::GenerarIDNuevo() {
    ArchivoBinario<Album> af(_nombreArchivo);
    int n = af.contar();
    if (n <= 0) return 1;
    Album ultimo;
    if (!af.leer(n - 1, ultimo)) return 1;
    return ultimo.getIdAlbum() + 1;
}

int ArchivoAlbum::BuscarPosicion(int id) {
    vector<Album> todos = ArchivoBinario<Album>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getIdAlbum() == id && todos[i].getEstado()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int ArchivoAlbum::BuscarIDPorTitulo(const char* titulo) {
    vector<Album> todos = ArchivoBinario<Album>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (Texto::igualesSinMayusculas(todos[i].getTitulo(), titulo) && todos[i].getEstado()) {
            return todos[i].getIdAlbum();
        }
    }
    return -1;
}

Album ArchivoAlbum::BuscarPorID(int id) {
    int pos = BuscarPosicion(id);
    if (pos >= 0) return Leer(pos);
    Album reg;
    reg.setEstado(false);
    return reg;
}

int ArchivoAlbum::BuscarOCrear(string tituloAlbum, int idArtista) {
    string tituloLimpio = Texto::trim(tituloAlbum);
    if (tituloLimpio.empty()) return 0;

    // Buscar coincidencia exacta de titulo Y artista (para evitar homonimos).
    vector<Album> todos = ArchivoBinario<Album>(_nombreArchivo).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (todos[i].getEstado() &&
            todos[i].getIdArtista() == idArtista &&
            Texto::igualesSinMayusculas(todos[i].getTitulo(), tituloLimpio.c_str())) {
            return todos[i].getIdAlbum();
        }
    }

    Album nuevo;
    int nuevoId = GenerarIDNuevo();
    nuevo.setIdAlbum(nuevoId);
    nuevo.setTitulo(tituloLimpio.c_str());
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0);
    nuevo.setEstado(true);

    Guardar(nuevo);
    cout << "   [INFO] Nuevo Album creado: " << tituloLimpio
         << " (ID: " << nuevoId << ")" << endl;
    return nuevoId;
}
