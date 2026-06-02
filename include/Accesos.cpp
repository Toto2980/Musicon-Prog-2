#include "../include/Accesos.h"
#include <iostream>
#include <cstdio>

using namespace std;

/**
 * Este archivo implementa la clase Accesos, que registra cuándo un usuario reproduce una canción.
 * Guarda y carga datos de accesos desde archivos para llevar un historial.
 */

/**
 * Prepara un nuevo registro de acceso vacío.
 * Inicializa el ID del usuario y de la canción a cero, y la fecha a valores predeterminados.
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
 * Asigna el ID del usuario que accedió a la canción.
 * Parámetros: id - El número único del usuario.
 */
void Accesos::setIdSuscriptor(int id) { _idSuscriptor = id; }

/**
 * Asigna el ID de la canción que fue reproducida.
 * Parámetros: id - El número único de la canción.
 */
void Accesos::setIdCancion(int id) { _idCancion = id; }

/**
 * Asigna la fecha y hora exacta cuando ocurrió el acceso.
 * Parámetros: fecha - La fecha y hora del evento.
 */
void Accesos::setFechaHora(Fecha fecha) { _fechaHora = fecha; }

// OBTENER VALORES

/**
 * Dice cuál usuario accedió.
 * Retorna: El ID del usuario.
 */
int Accesos::getIdSuscriptor() { return _idSuscriptor; }

/**
 * Dice cuál canción fue reproducida.
 * Retorna: El ID de la canción.
 */
int Accesos::getIdCancion() { return _idCancion; }

/**
 * Dice cuándo ocurrió el acceso.
 * Retorna: La fecha y hora del evento.
 */
Fecha Accesos::getFechaHora() { return _fechaHora; }

// GUARDAR Y CARGAR DATOS

/**
 * Guarda este registro de acceso en un archivo para recordar lo que pasó.
 * Retorna: Verdadero si se guardó correctamente, falso si hubo un problema.
 */
bool Accesos::Guardar() {
    FILE *p = fopen("accesos.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Accesos), 1, p);
    fclose(p);
    return ok;
}

/**
 * Carga un registro de acceso desde el archivo en una posición específica.
 * Parámetros: pos - La posición en la lista de registros.
 * Retorna: Verdadero si se cargó correctamente.
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
 * Cuenta cuántos registros de acceso hay guardados en total.
 * Retorna: El número total de accesos registrados.
 */
int Accesos::ObtenerCantidadRegistros() {
    FILE *p = fopen("accesos.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Accesos);
    fclose(p);
    return cant;
}
