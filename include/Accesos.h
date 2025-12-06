#ifndef ACCESOS_H
#define ACCESOS_H

#include "Fecha.h"

class Accesos {
private:
    int _idSuscriptor;
    int _idCancion;
    Fecha _fechaHora;
    // Eliminado _estado porque no se usa en logs históricos

public:
    Accesos();
    virtual ~Accesos();

    void setIdSuscriptor(int id);
    void setIdCancion(int id);
    void setFechaHora(Fecha fecha);

    int getIdSuscriptor();
    int getIdCancion();
    Fecha getFechaHora();

    void Cargar();
    void Mostrar();
};

#endif // ACCESOS_H
