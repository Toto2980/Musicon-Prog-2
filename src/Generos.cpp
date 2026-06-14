/**
 * Este archivo implementa la clase Genero con métodos para gestionar géneros musicales.
 * Incluye constructor con parámetros, setters/getters, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Generos.h"
#include "../include/ArchivoBinario.h"
#include "../include/Constantes.h"
#include "../include/Texto.h"
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
    cout << "ID de genero: "; cin >> _id;
    cin.ignore();
    cout << "Nombre del genero: "; cin.getline(_nombre, 50);
    _estado = true;
}

/**
 * Método Mostrar: Imprime ID, nombre y estado del género (const para no modificar).
 */
void Genero::Mostrar() const {
    cout << "ID: " << getIdGeneros() << " | " << _nombre << " (" << (_estado ? "Activo" : "Inactivo") << ")" << endl;
}

// --- PERSISTENCIA ---

/**
 * Guardar: Agrega el género al final del archivo binario "generos.dat".
 * Retorno: true si se escribió correctamente, false si error.
 */
bool Genero::Guardar() {
    return ArchivoBinario<Genero>(cfg::archivos::GENEROS).agregar(*this);
}

/**
 * Leer: Lee un género desde la posición especificada en el archivo.
 * Parámetros: pos - Posición (basado en 0).
 * Retorno: true si se leyó correctamente.
 */
bool Genero::Leer(int pos) {
    return ArchivoBinario<Genero>(cfg::archivos::GENEROS).leer(pos, *this);
}

/**
 * Modificar: Sobrescribe el género en la posición especificada.
 * Parámetros: pos - Posición a modificar.
 * Retorno: true si se modificó correctamente.
 */
bool Genero::Modificar(int pos) {
    return ArchivoBinario<Genero>(cfg::archivos::GENEROS).escribir(pos, *this);
}

/*
 * ObtenerCantidadRegistros: Calcula el número de géneros en el archivo.
 * Retorno: Cantidad de registros.
 */
int Genero::ObtenerCantidadRegistros() {
    return ArchivoBinario<Genero>(cfg::archivos::GENEROS).contar();
}

/*
 * BuscarIDPorNombre: Busca el ID de un género por nombre (insensible a mayúsculas).
 * Parámetros: nombre - Nombre a buscar.
 * Retorno: ID si encontrado y activo, -1 si no.
 */
int Genero::BuscarIDPorNombre(const char* nombre) {
    std::vector<Genero> todos = ArchivoBinario<Genero>(cfg::archivos::GENEROS).leerTodos();
    for (size_t i = 0; i < todos.size(); ++i) {
        if (Texto::igualesSinMayusculas(todos[i].getNombre(), nombre) && todos[i].getEstado()) {
            return todos[i].getIdGeneros();
        }
    }
    return -1;
}

/*
 * BuscarPosicionPorID: Busca la posición de un género por su ID.
 * Parámetros: id - ID a buscar.
 * Retorno: Posición si encontrado y activo, -1 si no.
 */
int Genero::BuscarPosicionPorID(int id) {
    std::vector<Genero> todos = ArchivoBinario<Genero>(cfg::archivos::GENEROS).leerTodos();
    for (size_t pos = 0; pos < todos.size(); ++pos) {
        if (todos[pos].getIdGeneros() == id && todos[pos].getEstado()) {
            return static_cast<int>(pos);
        }
    }
    return -1;
}
