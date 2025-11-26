#include "Accesos.h"

#include <iostream>
using namespace std;

// --- Definición del Constructor ---
Accesos::Accesos() {
    _idSuscriptor = 0;
    _idCancion = 0;

}

// --- Definición del Destructor ---
Accesos::~Accesos()
{
    // dtor
}

// --- Definiciones de los Setters ---

void Accesos::setIdSuscriptor(int id) {
    if (id >= 0) {
        _idSuscriptor = id;
    } else {
        _idSuscriptor = 0;
    }
}

void Accesos::setIdCancion(int id) {
    if (id >= 0) {
        _idCancion = id;
    } else {
        _idCancion = 0;
    }
}

void Accesos::setFechaHora(Fecha fecha) {
    _fechaHora = fecha;
}


// --- Definiciones de los Getters ---

int Accesos::getIdSuscriptor() {
    return _idSuscriptor;
}

int Accesos::getIdCancion() {
    return _idCancion;
}

Fecha Accesos::getFechaHora() {
    return _fechaHora;
}

void Accesos::Cargar() {
    cout << "Ingrese ID del Suscriptor: ";
    cin >> _idSuscriptor;
    cout << "Ingrese ID de la Cancion: ";
    cin >> _idCancion;
    cout << "Ingrese Fecha del acceso:" << endl;
    _fechaHora.Cargar();
}

void Accesos::Mostrar() {
    cout << "ID Suscriptor: " << _idSuscriptor << endl;
    cout << "ID Cancion   : " << _idCancion << endl;
    cout << "Fecha/Hora   : ";
    _fechaHora.Mostrar();
    cout << endl;
}
