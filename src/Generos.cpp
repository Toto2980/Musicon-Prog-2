#include "Generos.h"
#include <iostream>
#include <cstring>

using namespace std;


Genero::Genero(int id, const char* nombre, bool estado) {
    _idGeneros = id;


    setNombre(nombre);

    _estado = estado;
}

void Genero::setIdGeneros(int id) {
    _idGeneros = id;
}

void Genero::setNombre(const char* n) {

    strncpy(_nombre, n, 49);
    _nombre[49] = '\0';
}

void Genero::setEstado(bool estado) {
    _estado = estado;
}

int Genero::getIdGeneros() {
    return _idGeneros;
}

const char* Genero::getNombre() {
    return _nombre;
}

bool Genero::getEstado() {
    return _estado;
}

void Genero::cargar() {
    cout << "ID de genero: ";
    cin >> _idGeneros;


    cin.ignore();

    cout << "Nombre del genero: ";
    cin.getline(_nombre, 50);

    _estado = true;
}

void Genero::mostrar() const {
    cout << "ID de Genero: " << _idGeneros << endl;
    cout << " | Nombre: " << _nombre << endl;
    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}
