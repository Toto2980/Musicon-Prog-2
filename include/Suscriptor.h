#ifndef SUSCRIPTOR_H
#define SUSCRIPTOR_H

#include "Fecha.h"
class Suscriptor
{
private:
    int _idSuscriptor;
    char _dni[12];
    char _nombre[50];
    char _apellido[50];
    char _email[100];
    Fecha _fechaNacimiento;
    int _idSuscripcion;
    bool _estado;

public:
    Suscriptor();
    virtual ~Suscriptor();

    // Setters
    void setIdSuscriptor(int id);
    void setDni(const char* dni);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setEmail(const char* email);
    void setFechaNacimiento(Fecha fecha);
    void setIdSuscripcion(int id);
    void setEstado(bool estado);

    // Getters
    int getIdSuscriptor();
    const char* getDni();
    const char* getNombre();
    const char* getApellido();
    const char* getEmail();
    Fecha getFechaNacimiento();
    int getIdSuscripcion();
    bool getEstado();


    void Cargar();
    void Mostrar();
};

#endif // SUSCRIPTOR_H
