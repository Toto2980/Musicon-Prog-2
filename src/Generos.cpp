/**
 * Este archivo implementa la clase Genero con metodos para gestionar generos musicales.
 * Incluye constructor con parametros, setters/getters, metodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Generos.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor con parametros opcionales: Inicializa ID, nombre y estado.
 * Parametros: id - ID unico, nombre - Nombre del genero, estado - Activo/inactivo.
 */
Genero::Genero(int id, const char* nombre, bool estado) {
    setId(id);
    setNombre(nombre);
    _estado = estado;
}

/**
 * Setters: Establecen los valores de los atributos con validaciones.
 */
void Genero::setIdGeneros(int id) { setId(id); }
void Genero::setNombre(const char* n) { strncpy(_nombre, n, 49); _nombre[49] = '\0'; }
void Genero::setEstado(bool estado) { _estado = estado; }

/**
 * Getters: Devuelven los valores de los atributos.
 */
int Genero::getIdGeneros() const { return getId(); }
const char* Genero::getNombre() { return _nombre; }
bool Genero::getEstado() { return _estado; }

/**
 * Metodo Cargar: Solicita al usuario ID y nombre del genero.
 * Establece estado activo.
 */
void Genero::Cargar() {
    cout << "Nombre del genero: "; cin.getline(_nombre, 50);
    _estado = true;
}

/**
 * Metodo Mostrar: Imprime ID, nombre y estado del genero (const para no modificar).
 */
void Genero::Mostrar() const {
    cout << "ID: " << getIdGeneros() << " | " << _nombre << " (" << (_estado ? "Activo" : "Inactivo") << ")" << endl;
}

