#ifndef HORAYMINUTOS_H
#define HORAYMINUTOS_H
#include <string>

// CLASE UTILITARIA DE TIEMPO (Componente de Fecha)
class HoraYMinutos
{
   private:
        int _hora;
        int _minutos;

    public:
        HoraYMinutos();
        HoraYMinutos(int hora, int minutos);

        // --- GETTERS ---
        int getHora();
        int getMinutos();

        // --- SETTERS ---
        void setHora(int hora);
        void setMinutos(int minutos);

        std::string toString(); // Formato HH:MM
};

#endif // HORAYMINUTOS_H
