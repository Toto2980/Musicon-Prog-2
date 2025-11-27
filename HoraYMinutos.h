#ifndef HORAYMINUTOS_H
#define HORAYMINUTOS_H
#include <string>

class HoraYMinutos
{
   private:
        int _hora;
        int _minutos;

    public:
        HoraYMinutos();
        HoraYMinutos(int hora, int minutos);

        int getHora();
        int getMinutos();

        void setHora(int hora);
        void setMinutos(int minutos);

        std::string toString();
};

#endif // HORAYMINUTOS_H
