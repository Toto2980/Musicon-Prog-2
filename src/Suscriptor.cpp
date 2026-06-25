/**
 * Este archivo implementa la clase Suscriptor, que representa a un usuario del sistema.
 * Un suscriptor puede ser de tipo GRATIS (1) o PAGO (2).
 * La diferencia de plan impacta en cuantas playlists puede crear (ver PlaylistManager).
 *
 * Hereda de EntidadPadre para obtener el campo _id y los metodos getId/setId.
 * Los campos adicionales (DNI, apellido, email, etc.) son propios de Suscriptor.
 */

#include "../include/Suscriptor.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor: inicializa todos los campos con valores neutros.
 * - _tipoSuscriptor = 1 (GRATIS) por defecto.
 * - _nombre empieza vacio, los demas con valores placeholder "S/N" o "0".
 */
Suscriptor::Suscriptor() {
    setId(0);
    _nombre[0] = '\0';
    _estado = false;

    strcpy(_dni, "0");
    strcpy(_apellido, "S/N");
    strcpy(_email, "S/N");

    _tipoSuscriptor = 1; // Plan GRATIS por defecto
}

/** Destructor: no hay recursos dinamicos que liberar. */
Suscriptor::~Suscriptor() { }

/** Asigna el ID del suscriptor usando el setter de EntidadPadre. */
void Suscriptor::setIdSuscriptor(int id) {
    setId(id);
}

/** Asigna el DNI con copia segura (maximo 14 caracteres + terminador nulo). */
void Suscriptor::setDni(const char* dni) {
    strncpy(_dni, dni, 14);
    _dni[14] = '\0';
}

/** Asigna el apellido con copia segura (maximo 49 caracteres + terminador nulo). */
void Suscriptor::setApellido(const char* apellido) {
    strncpy(_apellido, apellido, 49);
    _apellido[49] = '\0';
}

/** Asigna el email con copia segura (maximo 99 caracteres + terminador nulo). */
void Suscriptor::setEmail(const char* email) {
    strncpy(_email, email, 99);
    _email[99] = '\0';
}

/** Asigna la fecha de nacimiento (objeto Fecha completo). */
void Suscriptor::setFechaNacimiento(Fecha fecha) {
    _fechaNacimiento = fecha;
}

/** Asigna el tipo de suscripcion: 1=GRATIS, 2=PAGO. */
void Suscriptor::setTipoSuscriptor(int tipo) {
    _tipoSuscriptor = tipo;
}

/** Devuelve el ID del suscriptor usando el getter de EntidadPadre. */
int Suscriptor::getIdSuscriptor() {
    return getId();
}

/** Devuelve el DNI del suscriptor. */
const char* Suscriptor::getDni() {
    return _dni;
}

/** Devuelve el apellido del suscriptor. */
const char* Suscriptor::getApellido() {
    return _apellido;
}

/** Devuelve el email del suscriptor. */
const char* Suscriptor::getEmail() {
    return _email;
}

/** Devuelve la fecha de nacimiento del suscriptor. */
Fecha Suscriptor::getFechaNacimiento() {
    return _fechaNacimiento;
}

/** Devuelve el tipo de suscripcion (1=GRATIS, 2=PAGO). */
int Suscriptor::getTipoSuscriptor() {
    return _tipoSuscriptor;
}

/**
 * Solicita al usuario los datos del suscriptor por consola.
 * NO pide el nombre de usuario (ya fue pedido antes en SuscriptorManager::Agregar
 * para poder verificar unicidad antes de llamar a este metodo).
 * Si pide: apellido, DNI, email, tipo de suscripcion y fecha de nacimiento.
 */
void Suscriptor::Cargar() {
    char buffer[100];

    InputHelper::pedirCadena("Apellido: ", buffer, 50);
    setApellido(buffer);

    InputHelper::pedirCadena("DNI: ", buffer, 15);
    setDni(buffer);

    InputHelper::pedirCadena("Email: ", buffer, 100);
    setEmail(buffer);

    cout << endl;
    cout << "TIPO DE SUSCRIPCION" << endl;
    cout << "1 - GRATIS" << endl;
    cout << "2 - PAGO" << endl;

    int tipo = InputHelper::pedirEnteroRango(
                                             "Seleccione una opcion: ",
                                             1,
                                             2
                                             );

    setTipoSuscriptor(tipo);

    cout << endl;
    cout << "Fecha de Nacimiento:" << endl;

    int d = InputHelper::pedirEnteroRango("Dia: ", 1, 31);
    int m = InputHelper::pedirEnteroRango("Mes: ", 1, 12);
    int a = InputHelper::pedirEnteroRango("Anio: ", 1900, 2025);

    _fechaNacimiento = Fecha(d, m, a);

    setEstado(true); // Activo al crearse
}

/**
 * Muestra los datos completos del suscriptor por consola.
 * Incluye nombre, apellido, DNI, email, estado (activo/inactivo),
 * tipo de plan y fecha de nacimiento.
 */
void Suscriptor::Mostrar() {

    cout << "ID: "
        << getId()
        << " | Usuario: "
        << getNombre()
        << " "
        << _apellido
        << endl;

    cout << "DNI: "
        << _dni
        << " | Email: "
        << _email
        << endl;

    cout << "Estado: ";

    if(getEstado()) {
        cout << "ACTIVO";
    }
    else {
        cout << "INACTIVO";
    }

    cout << endl;

    cout << "Plan: ";

    if (_tipoSuscriptor == 1) {
        cout << "GRATIS";
    }
    else {
        cout << "PAGO";
    }

    cout << endl;

    cout << "F. Nac: "
        << _fechaNacimiento.toString()
        << endl;

    cout << "-----------------------------------"
        << endl;
}
