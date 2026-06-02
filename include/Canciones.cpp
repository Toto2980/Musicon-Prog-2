/**
 * Este archivo implementa la clase Canciones con métodos para gestionar datos de canciones.
 * Incluye validaciones básicas y uso de InputHelper para entradas de usuario seguras.
 */

#include "../include/Canciones.h"
#include <iostream>
#include <cstring>
#include "../include/InputHelper.h" // Aprovechamos tu InputHelper

using namespace std;

/**
 * Inicializa todos los atributos con valores neutros.
 * El ID se deja en 0 (se asignará automáticamente), nombre vacío, IDs de album/género en 0,
 * duración en 0 y estado inactivo.
 */
Canciones::Canciones() {
    setId(0);
    strcpy(_nombre, "");
    _idAlbum = 0;
    _idGenero = 0;
    _duracionSegundos = 0;
    _estado = false;
}

/**
 * No hay recursos dinámicos que liberar.
 */

/**
 * Asigna el ID único de la canción.
 * Parámetros: id - El ID único a asignar.
 */
void Canciones::setIdCancion(int id) { setId(id); }

/**
 * Asigna el nombre de la canción con límite de 99 caracteres.
 * Usa strncpy para evitar desbordamientos y asegura terminación nula.
 * Parámetros: nombre - Cadena con el nombre.
 */
void Canciones::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 99);
    _nombre[99] = '\0';
}

/**
 * Asigna el ID del álbum al que pertenece la canción.
 * Parámetros: idAl - ID del álbum.
 */
void Canciones::setIdAlbum(int idAl) { _idAlbum = idAl; }

/**
 * Asigna el ID del género musical.
 * Parámetros: idGe - ID del género.
 */
void Canciones::setIdGenero(int idGe) { _idGenero = idGe; }

/**
 * Asigna la duración en segundos (solo acepta valores >= 0).
 * Si es negativa, se establece en 0.
 * Parámetros: duracion - Duración en segundos.
 */
void Canciones::setDuracionSegundos(int duracion) {
    if (duracion >= 0) _duracionSegundos = duracion;
    else _duracionSegundos = 0;
}

/**
 * Asigna el estado activo o inactivo.
 * Parámetros: e - true para activo, false para inactivo (eliminación lógica).
 */
void Canciones::setEstado(bool e) { _estado = e; }

/**
 * Dice el ID único de la canción.
 * Retorna: El ID único asignado.
 */
int Canciones::getIdCancion() { return getId(); }

/**
 * Dice el nombre de la canción.
 * Retorna: Puntero constante a la cadena del nombre.
 */
const char* Canciones::getNombre() { return _nombre; }

/**
 * Dice el ID del álbum.
 * Retorna: ID del álbum.
 */
int Canciones::getIdAlbum() { return _idAlbum; }

/**
 * Dice el ID del género.
 * Retorna: ID del género.
 */
int Canciones::getIdGenero() { return _idGenero; }

/**
 * Dice la duración en segundos.
 * Retorna: Duración en segundos.
 */
int Canciones::getDuracionSegundos() { return _duracionSegundos; }

/**
 * Dice el estado activo o inactivo.
 * Retorna: true si activo, false si inactivo.
 */
bool Canciones::getEstado() { return _estado; }

/**
 * Solicita al usuario los datos de la canción.
 * No pide ID (se genera automáticamente fuera de esta clase).
 * Usa InputHelper para entradas seguras y establece el estado como activo.
 */
void Canciones::Cargar() {
    // Ya no pedimos el ID aqué, el ID se gestiona fuera automáticamente
    // Usamos InputHelper para inputs seguros
    char buffer[100];
    InputHelper::pedirCadena("Nombre de la cancion: ", buffer, 100);
    setNombre(buffer);

    _idAlbum = InputHelper::pedirEntero("ID del Album: ");
    _idGenero = InputHelper::pedirEntero("ID del Genero: ");
    _duracionSegundos = InputHelper::pedirEntero("Duracion (en segundos): ");

    _estado = true;
}

/**
 * Imprime los datos de la canción en la consola si está activa.
 * Formatea la duración en minutos y segundos para mejor legibilidad.
 */
void Canciones::Mostrar() {
    // Solo mostramos si está activo
    if (_estado) {
        cout << "-----------------------------------" << endl;
        cout << "ID Cancion     : " << getIdCancion() << endl;
        cout << "Nombre         : " << _nombre << endl;
        cout << "ID Album       : " << _idAlbum << endl;
        cout << "ID Genero      : " << _idGenero << endl;
        cout << "Duracion       : " << _duracionSegundos / 60 << "m "
                                    << _duracionSegundos % 60 << "s" << endl;
        cout << "-----------------------------------" << endl;
    }
}
