#include "Fecha.h"
#include <string>

Fecha::Fecha(){
    _dia = 0;
    _mes = 0;
    _anio = 0;

}

Fecha::Fecha(int minutos, int hora , int dia, int mes, int anio){
    _dia = dia;
    _mes = mes;
    _anio = anio;


    _objetoHora.setHora(hora);
    _objetoHora.setMinutos(minutos);
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

std::string Fecha::toString(){

    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio) + " " + _objetoHora.toString();
}
