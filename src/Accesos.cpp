#include "../include/Accesos.h"
#include <iostream>
#include <cstdio>

using namespace std;

/**
 * Este archivo implementa la clase Accesos, que registra cuando un usuario reproduce una cancion.
 * Guarda y carga datos de accesos desde archivos para llevar un historial.
 */

/**
 * Prepara un nuevo registro de acceso vacio.
 * Inicializa el ID del usuario y de la cancion a cero, y la fecha a valores predeterminados.
 */
Accesos::Accesos() {
    _idSuscriptor = 0;
    _idCancion = 0;
}

/**
 * Limpia cualquier recurso usado por el registro de acceso.
 * Actualmente no hay recursos especiales que liberar.
 */

// CAMBIAR VALORES

/**
 * Asigna el ID del usuario que accedio a la cancion.
 * Parametros: id - El numero unico del usuario.
 */
void Accesos::setIdSuscriptor(int id) { _idSuscriptor = id; }

/**
 * Asigna el ID de la cancion que fue reproducida.
 * Parametros: id - El numero unico de la cancion.
 */
void Accesos::setIdCancion(int id) { _idCancion = id; }

/**
 * Asigna la fecha y hora exacta cuando ocurrio el acceso.
 * Parametros: fecha - La fecha y hora del evento.
 */
void Accesos::setFechaHora(Fecha fecha) { _fechaHora = fecha; }

// OBTENER VALORES

/**
 * Dice cual usuario accedio.
 * Retorna: El ID del usuario.
 */
int Accesos::getIdSuscriptor() { return _idSuscriptor; }

/**
 * Dice cual cancion fue reproducida.
 * Retorna: El ID de la cancion.
 */
int Accesos::getIdCancion() { return _idCancion; }

/**
 * Dice cuando ocurrio el acceso.
 * Retorna: La fecha y hora del evento.
 */
Fecha Accesos::getFechaHora() { return _fechaHora; }

// GUARDAR Y CARGAR DATOS

/**
 * Guarda este registro de acceso en un archivo para recordar lo que paso.
 * Retorna: Verdadero si se guardo correctamente, falso si hubo un problema.
 */
bool Accesos::Guardar() {
    FILE *p = fopen("accesos.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Accesos), 1, p);
    fclose(p);
    return ok;
}

/**
 * Carga un registro de acceso desde el archivo en una posicion especifica.
 * Parametros: pos - La posicion en la lista de registros.
 * Retorna: Verdadero si se cargo correctamente.
 */
bool Accesos::Leer(int pos) {
    FILE *p = fopen("accesos.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Accesos), SEEK_SET);
    bool ok = fread(this, sizeof(Accesos), 1, p);
    fclose(p);
    return ok;
}

/**
 * Cuenta cuantos registros de acceso hay guardados en total.
 * Retorna: El numero total de accesos registrados.
 */
int Accesos::ObtenerCantidadRegistros() {
    FILE *p = fopen("accesos.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Accesos);
    fclose(p);
    return cant;
}
