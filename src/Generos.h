#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

class Generos {
private:
    int _idGeneros;
    char _nombre[50];
    bool _estado;

public:

    Generos(int id = 0, const char* nombre = "", bool estado = true);

    void setIdGeneros(int id);
    void setNombre(const char* nombre);
    void setEstado(bool estado);

    int getIdGeneros();
    const char* getNombre();
    bool getEstado();

    void cargar();
    void mostrar() const;
};


#endif // GENERO_H_INCLUDED
