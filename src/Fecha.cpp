#include "Fecha.h"
#include <string>
#include <iostream>

using namespace std;

Fecha::Fecha(){
    //ctor
    _dia = 0;
    _mes = 0;
    _anio = 0;
}

Fecha::Fecha(int minutos, int hora , int dia, int mes, int anio){
    //ctor con parametros
    _dia = dia;
    _mes = mes;
    _anio = anio;

    _objetoHora.setHora(hora);
    _objetoHora.setMinutos(minutos);
 }

 Fecha::Fecha(int dia, int mes, int anio) {
    //ctor fecha simple
    _dia = dia;
    _mes = mes;
    _anio = anio;


    _objetoHora.setHora(0);
    _objetoHora.setMinutos(0);
}

HoraYMinutos Fecha::getHorario() {
    return _objetoHora;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::setDia(int dia){
    _dia = dia;
}

void Fecha::setMes(int mes){
    _mes = mes;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

void Fecha::setHorario(HoraYMinutos horario){
    _objetoHora = horario;
}


void Fecha::Cargar() {
    cout << "Dia: ";
    cin >> _dia;
    cout << "Mes: ";
    cin >> _mes;
    cout << "Anio: ";
    cin >> _anio;


    _objetoHora.setHora(0);
    _objetoHora.setMinutos(0);
}

void Fecha::Mostrar() {
    cout << _dia << "/" << _mes << "/" << _anio;
}


std::string Fecha::toString(){
    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio) + " " + _objetoHora.toString();
}
