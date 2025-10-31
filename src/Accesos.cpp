#include "Accesos.h"

// --- Definición del Constructor ---
Accesos::Accesos() {
    _idSuscriptor = 0;
    _idCancion = 0;

    // Inicializo todos los campos de la struct
    _fechaHora.dia = 0;
    _fechaHora.mes = 0;
    _fechaHora.anio = 0;
    _fechaHora.hora = 0;
    _fechaHora.minuto = 0;
    _fechaHora.segundo = 0;
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

void Accesos::setFechaHora(DateTime fecha) {
    _fechaHora = fecha;
}


// --- Definiciones de los Getters ---

int Accesos::getIdSuscriptor() {
    return _idSuscriptor;
}

int Accesos::getIdCancion() {
    return _idCancion;
}

DateTime Accesos::getFechaHora() {
    return _fechaHora;
}
