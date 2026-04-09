/**
 * Este archivo implementa la clase Suscriptor con métodos para gestionar datos de suscriptores.
 * Maneja inicialización, validaciones y uso de InputHelper para entradas seguras.
 */

#include "Suscriptor.h"
#include "InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor por defecto: Inicializa nombre vacío, estado inactivo, ID en 0,
 * DNI en "0", apellido y email en "S/N".
 */
Suscriptor::Suscriptor() {
    _nombre[0] = '\0';
    _estado = false;
    _idSuscriptor = 0;
    strcpy(_dni, "0");
    strcpy(_apellido, "S/N");
    strcpy(_email, "S/N");
}

/**
 * Destructor: No hay recursos din�micos que liberar.
 */
Suscriptor::~Suscriptor() { }

/**
 * Setters: Establecen los valores de los atributos con copias seguras.
 */
void Suscriptor::setIdSuscriptor(int id) { _idSuscriptor = id; }
void Suscriptor::setDni(const char* dni) { strncpy(_dni, dni, 14); _dni[14] = '\0'; }
void Suscriptor::setApellido(const char* apellido) { strncpy(_apellido, apellido, 49); _apellido[49] = '\0'; }
void Suscriptor::setEmail(const char* email) { strncpy(_email, email, 99); _email[99] = '\0'; }
void Suscriptor::setFechaNacimiento(Fecha fecha) { _fechaNacimiento = fecha; }

/**
 * Getters: Devuelven los valores de los atributos.
 */
int Suscriptor::getIdSuscriptor() { return _idSuscriptor; }
const char* Suscriptor::getDni() { return _dni; }
const char* Suscriptor::getApellido() { return _apellido; }
const char* Suscriptor::getEmail() { return _email; }
Fecha Suscriptor::getFechaNacimiento() { return _fechaNacimiento; }

/**
 * M�todo Cargar: Solicita apellido, DNI, email y fecha de nacimiento al usuario.
 * El nombre se maneja fuera (en l�gica de negocio), establece estado activo.
 * Usa InputHelper para validaciones de rango en fecha.
 */
void Suscriptor::Cargar() {
    char buffer[100];

    // El nombre normalmente se asigna desde la lógica de negocio antes de guardar el suscriptor.

    InputHelper::pedirCadena("Apellido: ", buffer, 50);
    setApellido(buffer);

    InputHelper::pedirCadena("DNI: ", buffer, 15);
    setDni(buffer);

    InputHelper::pedirCadena("Email: ", buffer, 100);
    setEmail(buffer);

    cout << "Fecha de Nacimiento:" << endl;
    int d = InputHelper::pedirEnteroRango("Dia: ", 1, 31);
    int m = InputHelper::pedirEnteroRango("Mes: ", 1, 12);
    int a = InputHelper::pedirEnteroRango("Anio: ", 1900, 2025);
    _fechaNacimiento = Fecha(d, m, a);

    setEstado(true); // M�todo heredado
}

/**
 * M�todo Mostrar: Imprime ID, nombre completo, DNI, email y fecha de nacimiento si activo.
 * Formato legible con separadores.
 */
void Suscriptor::Mostrar() {
    if (getEstado()) { // M�todo heredado
        cout << "ID: " << _idSuscriptor << " | Usuario: " << getNombre() << " " << _apellido << endl;
        cout << "DNI: " << _dni << " | Email: " << _email << endl;
        cout << "F. Nac: " << _fechaNacimiento.toString() << endl;
        cout << "-----------------------------------" << endl;
    }
}
