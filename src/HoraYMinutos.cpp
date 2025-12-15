#include <iostream>
#include "HoraYMinutos.h"
#include <string>

using namespace std;

HoraYMinutos::HoraYMinutos(){
    //ctor
    _hora = 0;
    _minutos = 0;
}

HoraYMinutos::HoraYMinutos(int hora, int minutos)
{
    //ctor parametrizado
    _hora = hora;
    _minutos = minutos;
}


int HoraYMinutos::getHora(){
    return _hora;
}


int HoraYMinutos::getMinutos(){
    return _minutos;
}

void HoraYMinutos::setHora(int hora) {
    _hora = hora;
}

void HoraYMinutos::setMinutos(int minutos) {
    _minutos = minutos;
}

std::string HoraYMinutos::toString() {

    string minStr = std::to_string(_minutos);
    if(_minutos < 10) minStr = "0" + minStr;

    return std::to_string(_hora) + ":" + minStr;
}
