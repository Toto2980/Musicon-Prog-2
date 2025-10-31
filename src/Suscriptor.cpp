#include <iostream>
#include <cstring>
#include "Suscriptor.h"
using namespace std;

Suscriptor::Suscriptor() {
    _idSuscriptor = 0;
    strcpy(_dni, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_email, "");
    _idSuscripcion = 0;
    _estado = false;
}


void Suscriptor::setIdSuscriptor(int id) {
    _idSuscriptor = id;
}

void Suscriptor::setDni(const char* dni) {
    strncpy(_dni, dni, 10);
    _dni[10] = '\0';
}

void Suscriptor::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 49);
    _nombre[49] = '\0';
}

void Suscriptor::setApellido(const char* apellido) {
    strncpy(_apellido, apellido, 49);
    _apellido[49] = '\0';
}

void Suscriptor::setEmail(const char* email) {
    strncpy(_email, email, 99);
    _email[99] = '\0';
}

void Suscriptor::setFechaNacimiento(Fecha fecha) {
    _fechaNacimiento = fecha;
}

void Suscriptor::setIdSuscripcion(int id) {
    _idSuscripcion = id;
}

void Suscriptor::setEstado(bool estado) {
    _estado = estado;
}

int Suscriptor::getIdSuscriptor() {
    return _idSuscriptor;
}

const char* Suscriptor::getDni() {
    return _dni;
}

const char* Suscriptor::getNombre() {
    return _nombre;
}

const char* Suscriptor::getApellido() {
    return _apellido;
}

const char* Suscriptor::getEmail() {
    return _email;
}

Fecha Suscriptor::getFechaNacimiento() {
    return _fechaNacimiento;
}

int Suscriptor::getIdSuscripcion() {
    return _idSuscripcion;
}

bool Suscriptor::getEstado() {
    return _estado;
}


void Suscriptor::Cargar() {

    std::cout << "ID Suscriptor: ";
    std::cin >> _idSuscriptor;
    std::cout << "DNI: ";
    std::cin >> _dni;
    std::cout << "Nombre: ";
    std::cin.ignore();
    std::cin.getline(_nombre, 50);
    std::cout << "Apellido: ";
    std::cin.getline(_apellido, 50);
    std::cout << "Email: ";
    std::cin.getline(_email, 100);

    int dia, mes, anio;
    std::cout << "Fecha de Nacimiento (DD MM AAAA): " << std::endl;
    std::cout << "Dia: ";
    std::cin >> dia;
    std::cout << "Mes: ";
    std::cin >> mes;
    std::cout << "Anio: ";
    std::cin >> anio;

    _fechaNacimiento = Fecha(dia, mes, anio);

    std::cout << "ID Tipo Suscripcion: ";
    std::cin >> _idSuscripcion;
    _estado = true; // Se activa al cargar

}

void Suscriptor::Mostrar() {
    std::cout << "ID Suscriptor: " << _idSuscriptor << std::endl;
    std::cout << "DNI: " << _dni << std::endl;
    std::cout << "Nombre: " << _nombre << std::endl;
    std::cout << "Apellido: " << _apellido << std::endl;
    std::cout << "Email: " << _email << std::endl;
    // Usamos el m‚todo .toString() de la Fecha
    std::cout << "Fecha Nac: " << _fechaNacimiento.toString() << std::endl;
    std::cout << "ID Suscripcion: " << _idSuscripcion << std::endl;
    std::cout << "Estado: " << (_estado ? "Activo" : "Baja") << std::endl;
}

Suscriptor::~Suscriptor()
{
    // dtor
}
