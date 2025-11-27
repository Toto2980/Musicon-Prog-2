#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

class Genero { // La clase es Singular
private:
    int _idGeneros;
    char _nombre[50];
    bool _estado;

public:
    // CORRECCIÓN AQUÍ: El constructor debe llamarse Genero (igual que la clase)
    Genero(int id = 0, const char* nombre = "", bool estado = true);

    void setIdGeneros(int id);
    void setNombre(const char* nombre);
    void setEstado(bool estado);

    int getIdGeneros();
    const char* getNombre();
    bool getEstado();

    void Cargar();
    void Mostrar() const;
};

#endif // GENEROS_H_INCLUDED
