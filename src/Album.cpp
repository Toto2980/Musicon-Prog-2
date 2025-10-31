#include "Album.h"
#include <cstring>

// --- Definición del Constructor ---
Album::Album() {
    _idAlbum = 0;
    strcpy(_titulo, "");
    _idArtista = 0;
    _anioPublicacion = 0;
    _estado = false;
}

// --- Definiciones de los Setters ---

void Album::setIdAlbum(int id) {
    _idAlbum = id;
}

void Album::setTitulo(const char* titulo) {
    strncpy(_titulo, titulo, 99);
    _titulo[99] = '\0'; // Para asegurar de que no termine nulo
}

void Album::setIdArtista(int idAr) {
    _idArtista = idAr;
}

void Album::setAnioPublicacion(int anio) {

    if (anio > 0) {
        // Si el año es positivo, lo guardamos
        _anioPublicacion = anio;
    }
    else {
        // Si es cero o negativo, guardamos 0
        // para saber que es un error o no está cargado.
        _anioPublicacion = 0;
    }
}

void Album::setEstado(bool e) {
    _estado = e;
}

// --- Definiciones de los Getters ---

int Album::getIdAlbum() {
    return _idAlbum;
}

const char* Album::getTitulo() {
    return _titulo;
}

int Album::getIdArtista() {
    return _idArtista;
}

int Album::getAnioPublicacion() {
    return _anioPublicacion;
}

bool Album::getEstado() {
    return _estado;
}

Album::~Album()
{
    // dtor (Destructor)
    // Tiene que estar definido, aunque esté vacío.
}
