#include "Canciones.h"
#include <cstring>
#include <iostream>
using namespace std;

Canciones::Canciones() {
    //ctor
    _idCancion = 0;
    strcpy(_nombre, "");
    _idAlbum = 0;
    _idGenero = 0;
    _duracionSegundos = 0;
    _estado = false;
}

Canciones::~Canciones()
{
    //dtor
}

void Canciones::setIdCancion(int id) {
    _idCancion = id;
}

void Canciones::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 99);
    _nombre[99] = '\0';
}

void Canciones::setIdAlbum(int idAl) {
    _idAlbum = idAl;
}

void Canciones::setIdGenero(int idGe) {
    _idGenero = idGe;
}

void Canciones::setDuracionSegundos(int duracion) {
    if (duracion >= 0) {
        _duracionSegundos = duracion;
    } else {
        _duracionSegundos = 0;
    }
}

void Canciones::setEstado(bool e) {
    _estado = e;
}

int Canciones::getIdCancion() {
    return _idCancion;
}

const char* Canciones::getNombre() {
    return _nombre;
}

int Canciones::getIdAlbum() {
    return _idAlbum;
}

int Canciones::getIdGenero() {
    return _idGenero;
}

int Canciones::getDuracionSegundos() {
    return _duracionSegundos;
}

bool Canciones::getEstado() {
    return _estado;
}

void Canciones::Cargar() {
    cout << "Nombre de la cancion: ";
    cin.ignore();
    cin.getline(_nombre, 100);

    cout << "ID del Album: ";
    cin >> _idAlbum;

    cout << "ID del Genero: ";
    cin >> _idGenero;

    cout << "Duracion (en segundos): ";
    cin >> _duracionSegundos;

    _estado = true;
}

void Canciones::Mostrar() {
    if (_estado == true) {
        cout << "-----------------------------------" << endl;
        cout << "ID Cancion     : " << _idCancion << endl;
        cout << "Nombre         : " << _nombre << endl;
        cout << "ID Album       : " << _idAlbum << endl;
        cout << "ID Genero      : " << _idGenero << endl;

        cout << "Duracion       : " << _duracionSegundos / 60 << "m "
                                    << _duracionSegundos % 60 << "s" << endl;
        cout << "-----------------------------------" << endl;
    }
}
}
