/**
 * Este archivo implementa la clase Fecha, que maneja fechas y horas completas para el sistema Musicon.
 * Combina día, mes, año con un objeto HoraYMinutos para registrar momentos exactos.
 */

#include "../include/Fecha.h"
#include "InputHelper.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Fecha::Fecha() {
    _dia = 0;
    _mes = 0;
    _anio = 0;
    _objetoHora = HoraYMinutos();
}

Fecha::Fecha(int minutos, int hora, int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
    _objetoHora = HoraYMinutos(hora, minutos);
}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
    _objetoHora = HoraYMinutos();
}

int Fecha::getDia() { return _dia; }
int Fecha::getMes() { return _mes; }
int Fecha::getAnio() { return _anio; }
HoraYMinutos Fecha::getHorario() { return _objetoHora; }

void Fecha::setDia(int dia) { _dia = dia; }
void Fecha::setMes(int mes) { _mes = mes; }
void Fecha::setAnio(int anio) { _anio = anio; }
void Fecha::setHorario(HoraYMinutos horario) { _objetoHora = horario; }

void Fecha::Cargar() {
    _dia = InputHelper::pedirEnteroRango("Dia: ", 1, 31);
    _mes = InputHelper::pedirEnteroRango("Mes: ", 1, 12);
    _anio = InputHelper::pedirEnteroRango("Anio: ", 1900, 2100);

    int hora = InputHelper::pedirEnteroRango("Hora: ", 0, 23);
    int minutos = InputHelper::pedirEnteroRango("Minutos: ", 0, 59);
    _objetoHora = HoraYMinutos(hora, minutos);
}

void Fecha::Mostrar() {
    cout << toString();
}

std::string Fecha::toString() {
    ostringstream salida;
    salida << setfill('0') << setw(2) << _dia << "/"
           << setw(2) << _mes << "/"
           << _anio << " "
           << setw(2) << _objetoHora.getHora() << ":"
           << setw(2) << _objetoHora.getMinutos();
    return salida.str();
}
