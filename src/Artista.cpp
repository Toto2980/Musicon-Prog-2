#include "Artista.h"
#include <iostream>
#include <cstring>

Artista::Artista(){
    //ctor
    _idArtista = 0;
    strcpy(_nombre, "");
    strcpy(_nacionalidad, "");
    _estado = false;
}

void Artista::setIdArtista(int id) {
    _idArtista = id;
}

void Artista::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 99);
    _nombre[99] = '\0';
}

void Artista::setNacionalidad(const char* nacionalidad) {
    strncpy(_nacionalidad, nacionalidad, 49);
    _nacionalidad[49] = '\0';
}

void Artista::setEstado(bool estado) {
    _estado = estado;
}

int Artista::getIdArtista() {
    return _idArtista;
}

const char* Artista::getNombre() {
    return _nombre;
}

const char* Artista::getNacionalidad() {
    return _nacionalidad;
}

bool Artista::getEstado() {
    return _estado;
}

void Artista::Cargar() {
    std::cout << "ID Artista: ";
    std::cin >> _idArtista;
    std::cout << "Nombre: ";
    std::cin.ignore();
    std::cin.getline(_nombre, 100);
    std::cout << "Nacionalidad: ";
    std::cin.getline(_nacionalidad, 50);
    _estado = true;
}

void Artista::Mostrar() {
    if (_estado == true) {
        std::cout << "------------------------------" << std::endl;
        std::cout << "ID Artista    : " << _idArtista << std::endl;
        std::cout << "Nombre        : " << _nombre << std::endl;
        std::cout << "Nacionalidad  : " << _nacionalidad << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
}

Artista::~Artista()
{
    //dtor
}
