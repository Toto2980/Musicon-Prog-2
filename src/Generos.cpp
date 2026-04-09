/**
 * Este archivo implementa la clase Genero con métodos para gestionar géneros musicales.
 * Incluye constructor con parámetros, setters/getters, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "Generos.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

/**
 * Compara dos textos sin distinguir mayúsculas y minúsculas.
 */
static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false;
        }
        ++texto1;
        ++texto2;
    }

    return *texto1 == *texto2;
}

/**
 * Constructor con par�metros opcionales: Inicializa ID, nombre y estado.
 * Par�metros: id - ID �nico, nombre - Nombre del g�nero, estado - Activo/inactivo.
 */
Genero::Genero(int id, const char* nombre, bool estado) {
    _idGeneros = id;
    setNombre(nombre);
    _estado = estado;
}

/**
 * Setters: Establecen los valores de los atributos con validaciones.
 */
void Genero::setIdGeneros(int id) { _idGeneros = id; }
void Genero::setNombre(const char* n) { strncpy(_nombre, n, 49); _nombre[49] = '\0'; }
void Genero::setEstado(bool estado) { _estado = estado; }

/**
 * Getters: Devuelven los valores de los atributos.
 */
int Genero::getIdGeneros() { return _idGeneros; }
const char* Genero::getNombre() { return _nombre; }
bool Genero::getEstado() { return _estado; }

/**
 * M�todo Cargar: Solicita al usuario ID y nombre del g�nero.
 * Establece estado activo.
 */
void Genero::Cargar() {
    cout << "ID de genero: "; cin >> _idGeneros;
    cin.ignore();
    cout << "Nombre del genero: "; cin.getline(_nombre, 50);
    _estado = true;
}

/**
 * M�todo Mostrar: Imprime ID, nombre y estado del g�nero (const para no modificar).
 */
void Genero::Mostrar() const {
    cout << "ID: " << _idGeneros << " | " << _nombre << " (" << (_estado ? "Activo" : "Inactivo") << ")" << endl;
}

// --- PERSISTENCIA ---

/**
 * Guardar: Agrega el g�nero al final del archivo binario "generos.dat".
 * Retorno: true si se escribi� correctamente, false si error.
 */
bool Genero::Guardar() {
    FILE *p = fopen("generos.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Genero), 1, p);
    fclose(p);
    return ok;
}

/**
 * Leer: Lee un g�nero desde la posici�n especificada en el archivo.
 * Par�metros: pos - Posici�n (basado en 0).
 * Retorno: true si se ley� correctamente.
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
 * Modificar: Sobrescribe el g�nero en la posici�n especificada.
 * Par�metros: pos - Posici�n a modificar.
 * Retorno: true si se modific� correctamente.
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
 * ObtenerCantidadRegistros: Calcula el n�mero de g�neros en el archivo.
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
 * BuscarIDPorNombre: Busca el ID de un g�nero por nombre (insensible a may�sculas).
 * Par�metros: nombre - Nombre a buscar.
 * Retorno: ID si encontrado y activo, -1 si no.
 */
int Genero::BuscarIDPorNombre(const char* nombre) {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return -1;
    Genero aux;
    while(fread(&aux, sizeof(Genero), 1, p)) {
        if(sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return aux.getIdGeneros();
        }
    }
    fclose(p);
    return -1;
}

/*
 * BuscarPosicionPorID: Busca la posici�n de un g�nero por su ID.
 * Par�metros: id - ID a buscar.
 * Retorno: Posici�n si encontrado y activo, -1 si no.
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
