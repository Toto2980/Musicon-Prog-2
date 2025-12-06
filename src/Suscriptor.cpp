#include "Suscriptor.h"
#include <iostream>
#include <cstring>
#include <cstdio>

Suscriptor::Suscriptor() {
    _estado = false;
    _idSuscriptor = 0;
    strcpy(_nombre, "S/N");
    strcpy(_apellido, "S/N");
    strcpy(_email, "S/N");
    strcpy(_dni, "0");
}

Suscriptor::~Suscriptor() {
    //dtor
}

// SETTERS
void Suscriptor::setIdSuscriptor(int id) { _idSuscriptor = id; }
void Suscriptor::setDni(const char* dni) { strcpy(_dni, dni); }
void Suscriptor::setNombre(const char* nombre) { strcpy(_nombre, nombre); }
void Suscriptor::setApellido(const char* apellido) { strcpy(_apellido, apellido); }
void Suscriptor::setEmail(const char* email) { strcpy(_email, email); }
void Suscriptor::setFechaNacimiento(Fecha fecha) { _fechaNacimiento = fecha; }
void Suscriptor::setEstado(bool estado) { _estado = estado; }

// GETTERS
int Suscriptor::getIdSuscriptor() { return _idSuscriptor; }
const char* Suscriptor::getDni() { return _dni; }
const char* Suscriptor::getNombre() { return _nombre; }
const char* Suscriptor::getApellido() { return _apellido; }
const char* Suscriptor::getEmail() { return _email; }
Fecha Suscriptor::getFechaNacimiento() { return _fechaNacimiento; }
bool Suscriptor::getEstado() { return _estado; }

void Suscriptor::Cargar() {
    // ID y Nombre se piden afuera (en registrarse) o son automáticos
    std::cout << "Nombre de Usuario: ";
    std::cin.ignore();
    std::cin.getline(_nombre, 50);

    std::cout << "Apellido: ";
    std::cin.getline(_apellido, 50);

    std::cout << "DNI: ";
    std::cin >> _dni;

    std::cout << "Email: ";
    std::cin.ignore();
    std::cin.getline(_email, 100);

    int dia, mes, anio;
    std::cout << "Fecha de Nacimiento (D M A): ";
    std::cin >> dia >> mes >> anio;
    _fechaNacimiento = Fecha(dia, mes, anio);

    // ELIMINADO: Pedido de Tipo de Suscripcion
    _estado = true;
}

void Suscriptor::Mostrar() {
    if (_estado) {
        std::cout << "ID: " << _idSuscriptor << " | Usuario: " << _nombre << " " << _apellido << std::endl;
        std::cout << "DNI: " << _dni << " | Email: " << _email << std::endl;
        std::cout << "F. Nac: " << _fechaNacimiento.toString() << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
}
