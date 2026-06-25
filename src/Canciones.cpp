/**
 * Este archivo implementa la clase Canciones con metodos para gestionar datos de canciones.
 * Incluye validaciones basicas y uso de InputHelper para entradas de usuario seguras.
 */

#include "../include/Canciones.h"
#include <iostream>
#include <cstring>
#include "../include/InputHelper.h" // Aprovechamos tu InputHelper

using namespace std;

/**
 * Inicializa todos los atributos con valores neutros.
 * El ID se deja en 0 (se asignara automaticamente), nombre vacio, IDs de album/genero en 0,
 * duracion en 0 y estado inactivo.
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
 * No hay recursos dinamicos que liberar.
 */

/**
 * Asigna el ID unico de la cancion.
 * Parametros: id - El ID unico a asignar.
 */
void Canciones::setIdCancion(int id) { setId(id); }

/**
 * Asigna el nombre de la cancion con limite de 99 caracteres.
 * Usa strncpy para evitar desbordamientos y asegura terminacion nula.
 * Parametros: nombre - Cadena con el nombre.
 */
void Canciones::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 99);
    _nombre[99] = '\0';
}

/**
 * Asigna el ID del album al que pertenece la cancion.
 * Parametros: idAl - ID del album.
 */
void Canciones::setIdAlbum(int idAl) { _idAlbum = idAl; }

/**
 * Asigna el ID del genero musical.
 * Parametros: idGe - ID del genero.
 */
void Canciones::setIdGenero(int idGe) { _idGenero = idGe; }

/**
 * Asigna la duracion en segundos (solo acepta valores >= 0).
 * Si es negativa, se establece en 0.
 * Parametros: duracion - Duracion en segundos.
 */
void Canciones::setDuracionSegundos(int duracion) {
    if (duracion >= 0) _duracionSegundos = duracion;
    else _duracionSegundos = 0;
}

/**
 * Asigna el estado activo o inactivo.
 * Parametros: e - true para activo, false para inactivo (eliminacion logica).
 */
void Canciones::setEstado(bool e) { _estado = e; }

/**
 * Dice el ID unico de la cancion.
 * Retorna: El ID unico asignado.
 */
int Canciones::getIdCancion() { return getId(); }

/**
 * Dice el nombre de la cancion.
 * Retorna: Puntero constante a la cadena del nombre.
 */
const char* Canciones::getNombre() { return _nombre; }

/**
 * Dice el ID del album.
 * Retorna: ID del album.
 */
int Canciones::getIdAlbum() { return _idAlbum; }

/**
 * Dice el ID del genero.
 * Retorna: ID del genero.
 */
int Canciones::getIdGenero() { return _idGenero; }

/**
 * Dice la duracion en segundos.
 * Retorna: Duracion en segundos.
 */
int Canciones::getDuracionSegundos() { return _duracionSegundos; }

/**
 * Dice el estado activo o inactivo.
 * Retorna: true si activo, false si inactivo.
 */
bool Canciones::getEstado() { return _estado; }

/**
 * Solicita al usuario los datos de la cancion.
 * No pide ID (se genera automaticamente fuera de esta clase).
 * Usa InputHelper para entradas seguras y establece el estado como activo.
 */
void Canciones::Cargar() {
    // Ya no pedimos el ID aque, el ID se gestiona fuera automaticamente
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
 * Imprime los datos de la cancion en la consola si esta activa.
 * Formatea la duracion en minutos y segundos para mejor legibilidad.
 */
void Canciones::Mostrar() {
    // Solo mostramos si esta activo
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
