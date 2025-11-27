#ifndef ACCESOS_H
#define ACCESOS_H

#include "Fecha.h"

class Accesos {
private:
    int _idSuscriptor;
    int _idCancion;
    Fecha _fechaHora;

public:
    // Constructor
    Accesos();
    virtual ~Accesos();

    // Setters
    void setIdSuscriptor(int id);
    void setIdCancion(int id);
    void setFechaHora(Fecha fecha); // Recibe un objeto Fecha (que ya trae hora)

    // Getters
    int getIdSuscriptor();
    int getIdCancion();
    Fecha getFechaHora(); // Devuelve un objeto Fecha

    void Cargar();
    void Mostrar();
};

#endif // ACCESOS_H
