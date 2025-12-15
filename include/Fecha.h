#pragma once
#include <string>
#include "HoraYMinutos.h"


class Fecha{
    private:
        int _dia, _mes, _anio;
        HoraYMinutos _objetoHora; // Composición

    public:
        Fecha(); // Constructor por defecto
        Fecha(int minutos, int hora, int dia, int mes, int anio); // Fecha + Hora
        Fecha(int dia, int mes, int anio); // Solo Fecha

        // --- GETTERS ---
        int getDia();
        int getMes();
        int getAnio();
        HoraYMinutos getHorario();

        // --- SETTERS ---
        void setDia(int dia);
        void setMes(int mes);
        void setAnio(int anio);
        void setHorario(HoraYMinutos horario);

        // --- UTILIDADES ---
        void Cargar();
        void Mostrar();
        std::string toString(); // Para concatenaciones fáciles
};
