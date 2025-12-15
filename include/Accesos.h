#ifndef ACCESOS_H
#define ACCESOS_H

#include "Fecha.h"

// REGISTRO DE REPRODUCCIONES
class Accesos {
    private:
        int _idSuscriptor;
        int _idCancion;
        Fecha _fechaHora;

    public:
        Accesos();
        virtual ~Accesos();

        // --- SETTERS ---
        void setIdSuscriptor(int id);
        void setIdCancion(int id);
        void setFechaHora(Fecha fecha);

        // --- GETTERS ---
        int getIdSuscriptor();
        int getIdCancion();
        Fecha getFechaHora();

        // --- METODOS DE ARCHIVO ---
        void Cargar();
        void Mostrar();
};

#endif // ACCESOS_H
