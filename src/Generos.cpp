#include "Generos.h"
#include <iostream>
#include <fstream>

using namespace std;


Generos::Generos() {
    _idGeneros = 0;
    _setNombre(_nombre; "");
    _estado = false;
}


void Generos::setIdGeneros(int id) {
     _idGeneros = id; 
     }
void Generos::setNombre(const char* n) {
     strncpy(_nombre, nombre, 49); _nombre[49] = '\0'; 
     }
void Generos::setEstado(bool estado) { 
    _estado = estado;
    }

int Generos::getIdGeneros() { 
    return _idGeneros;
    }
const char* Generos::getNombre() {
    return _nombre; 
    }
bool Generos::getEstado() { 
    return _estado; 
    }


void Generos::cargar() {
        cout << "ID de genero: ";
        cin >> _idGeneros;
        cin.ignore();
        cout << "Nombre del genero: ";
        cin.getline(_nombre, 50);
        _estado = true;
    }


void Generos::mostrar() {
       std::cout << "ID de Genero: " << _idGeneros << std::endl; 
       std::cout << " | Nombre: " << _nombre << std::endl;
       std::cout << "Estado: " << _estado << std::endl;
    }
