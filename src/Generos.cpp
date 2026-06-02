/**
 * Este archivo implementa la clase Genero con métodos para gestionar géneros musicales.
 * Incluye constructor con parámetros, setters/getters, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Generos.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>

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
    FILE *p = fopen("generos.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/**
 * Leer: Lee un género desde la posición especificada en el archivo.
 * Parámetros: pos - Posición (basado en 0).
 * Retorno: true si se leyó correctamente.
 */
bool Genero::Leer(int pos) {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Genero), SEEK_SET);
    bool ok = fread(this, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/**
 * Modificar: Sobrescribe el género en la posición especificada.
 * Parámetros: pos - Posición a modificar.
 * Retorno: true si se modificó correctamente.
 */
bool Genero::Modificar(int pos) {
    FILE *p = fopen("generos.dat", "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Genero), SEEK_SET);
    bool ok = fwrite(this, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/*
 * ObtenerCantidadRegistros: Calcula el número de géneros en el archivo.
 * Retorno: Cantidad de registros.
 */
int Genero::ObtenerCantidadRegistros() {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Genero);
    fclose(p);
    return cant;
}

/*
 * BuscarIDPorNombre: Busca el ID de un género por nombre (insensible a mayúsculas).
 * Parámetros: nombre - Nombre a buscar.
 * Retorno: ID si encontrado y activo, -1 si no.
 */
int Genero::BuscarIDPorNombre(const char* nombre) {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return -1;
    Genero aux;
    while(fread(&aux, sizeof(Genero), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return aux.getIdGeneros();
        }
    }
    fclose(p);
    return -1;
}

/*
 * BuscarPosicionPorID: Busca la posición de un género por su ID.
 * Parámetros: id - ID a buscar.
 * Retorno: Posición si encontrado y activo, -1 si no.
 */
int Genero::BuscarPosicionPorID(int id) {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return -1;
    Genero aux;
    int pos = 0;
    while(fread(&aux, sizeof(Genero), 1, p)) {
        if(aux.getIdGeneros() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
