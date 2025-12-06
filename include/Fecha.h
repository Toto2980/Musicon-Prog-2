#pragma once
#include <string>
#include "HoraYMinutos.h"

class Fecha{
    private:
    int _dia, _mes, _anio;
    HoraYMinutos _objetoHora;

    public:
    Fecha();
    Fecha(int minutos, int hora, int dia, int mes, int anio);
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();
    HoraYMinutos getHorario();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void setHorario(HoraYMinutos horario);

    void Cargar();
    void Mostrar();

    std::string toString();
};
