#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

// ENTIDAD: GENERO MUSICAL
class Genero {
    private:
        int _idGeneros;
        char _nombre[50];
        bool _estado;

    public:
        // Constructor con valores por defecto para instanciación rápida
        Genero(int id = 0, const char* nombre = "", bool estado = true);

        // --- SETTERS ---
        void setIdGeneros(int id);
        void setNombre(const char* nombre);
        void setEstado(bool estado);

        // --- GETTERS ---
        int getIdGeneros();
        const char* getNombre();
        bool getEstado();

        // --- E/S ---
        void Cargar();
        void Mostrar() const;
};

#endif // GENEROS_H_INCLUDED
