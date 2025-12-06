#include "Accesos.h"
#include <iostream>

using namespace std;

Accesos::Accesos() {
    _idSuscriptor = 0;
    _idCancion = 0;
}

Accesos::~Accesos() {
    //dtor
}

// SETTERS
void Accesos::setIdSuscriptor(int id) { _idSuscriptor = id; }
void Accesos::setIdCancion(int id) { _idCancion = id; }
void Accesos::setFechaHora(Fecha fecha) { _fechaHora = fecha; }

// GETTERS
int Accesos::getIdSuscriptor() { return _idSuscriptor; }
int Accesos::getIdCancion() { return _idCancion; }
Fecha Accesos::getFechaHora() { return _fechaHora; }

// METODOS
void Accesos::Cargar() {
    // Como el acceso es automático, no cargamos nada manual ni usamos estado
}

void Accesos::Mostrar() {
    // Mostramos siempre (los logs no se dan de baja)
    cout << "Usuario ID: " << _idSuscriptor << " | Cancion ID: " << _idCancion << endl;
    cout << "Fecha: " << _fechaHora.toString() << endl;
    cout << "-------------------------" << endl;
}
