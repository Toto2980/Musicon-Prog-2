/**
 * Este archivo define la clase HoraYMinutos, una utilidad para manejar horas y minutos.
 * Se utiliza como componente de la clase Fecha para representar la parte temporal.
 */

#ifndef HORAYMINUTOS_H
#define HORAYMINUTOS_H
#include <string>

/** Clase utilitaria para manejar hora y minutos, componente de la clase Fecha. */
class HoraYMinutos
{
   private:
        int _hora;
        int _minutos;

    public:
        /** Constructor por defecto (hora=0, minutos=0). */
        HoraYMinutos();
        /** Constructor con hora y minutos especificados. Parámetros: hora - Hora (0-23), minutos - Minutos (0-59). */
        HoraYMinutos(int hora, int minutos);

        /** Obtiene la hora. Retorna: Hora (0-23). */
        int getHora();
        /** Obtiene los minutos. Retorna: Minutos (0-59). */
        int getMinutos();

        // --- SETTERS ---
        /** Establece la hora. Parámetros: hora - Hora (0-23). */
        void setHora(int hora);
        /** Establece los minutos. Parámetros: minutos - Minutos (0-59). */
        void setMinutos(int minutos);

        /** Convierte a string en formato HH:MM. Retorna: String en formato HH:MM. */
        std::string toString(); // Formato HH:MM
};

#endif // HORAYMINUTOS_H
