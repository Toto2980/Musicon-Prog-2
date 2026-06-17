/**
 * Este archivo implementa la clase Genero con métodos para gestionar géneros musicales.
 * Incluye constructor con parámetros, setters/getters, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Generos.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor con parámetros opcionales: Inicializa ID, nombre y estado.
 * Parámetros: id - ID único, nombre - Nombre del género, estado - Activo/inactivo.
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
 * Método Cargar: Solicita al usuario ID y nombre del género.
 * Establece estado activo.
 */
void Genero::Cargar() {
    cout << "Nombre del genero: "; cin.getline(_nombre, 50);
    _estado = true;
}

/**
 * Método Mostrar: Imprime ID, nombre y estado del género (const para no modificar).
 */
void Genero::Mostrar() const {
    cout << "ID: " << getIdGeneros() << " | " << _nombre << " (" << (_estado ? "Activo" : "Inactivo") << ")" << endl;
}

