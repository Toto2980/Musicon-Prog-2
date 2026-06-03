/**
 * Este archivo define la clase Fecha, que combina una fecha (día, mes, año) con una hora.
 * Utiliza la clase HoraYMinutos para representar la parte horaria.
 */

#ifndef FECHA_H
#define FECHA_H

#include <string>
#include "HoraYMinutos.h"

/** Representa una fecha completa con día, mes, año y hora. */
class Fecha {
    private:
        int _dia;
        int _mes;
        int _anio;
        HoraYMinutos _objetoHora;

    public:
        /** Constructor por defecto. */
        Fecha();

        /** Constructor con hora incluida. Parámetros: minutos, hora, dia, mes, anio. */
        Fecha(int minutos, int hora, int dia, int mes, int anio);
        /** Constructor sin hora específica. Parámetros: dia, mes, anio. */
        Fecha(int dia, int mes, int anio);

        /** Obtiene el día. Retorna: Día de la fecha. */
        int getDia();
        /** Obtiene el mes. Retorna: Mes de la fecha. */
        int getMes();
        /** Obtiene el año. Retorna: Año de la fecha. */
        int getAnio();
        /** Obtiene la hora y minutos. Retorna: Objeto HoraYMinutos. */
        HoraYMinutos getHorario();

        /** Establece el día. Parámetros: dia - Nuevo día. */
        void setDia(int dia);
        /** Establece el mes. Parámetros: mes - Nuevo mes. */
        void setMes(int mes);
        /** Establece el año. Parámetros: anio - Nuevo año. */
        void setAnio(int anio);
        /** Establece el horario. Parámetros: horario - Nueva hora y minutos. */
        void setHorario(HoraYMinutos horario);

        /** Carga la fecha y hora desde teclado. */
        void Cargar();
        /** Muestra la fecha y hora por pantalla. */
        void Mostrar();
        /** Convierte la fecha a texto. Retorna: Cadena con la fecha y hora. */
        std::string toString();
};

#endif // FECHA_H
