#ifndef ACCESOS_H
#define ACCESOS_H


#include "musicon.h"

class Accesos {
private:
    int _idSuscriptor;
    int _idCancion;
    DateTime _fechaHora;

public:
    // Constructor
    Accesos();
    virtual ~Accesos();

    // Setters
    void setIdSuscriptor(int id);
    void setIdCancion(int id);
    void setFechaHora(DateTime fecha); // Recibe la struct entera

    // Getters
    int getIdSuscriptor();
    int getIdCancion();
    DateTime getFechaHora(); // Devuelve la struct entera
};

#endif // ACCESOS_H
