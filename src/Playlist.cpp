#include "../include/Playlist.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Este archivo implementa la clase Playlist, con metodos para crear, guardar y buscar playlists.
 * Maneja la persistencia de datos en archivos y la interaccion con el usuario.
 */

/**
 * Prepara una nueva lista de canciones vacia con valores iniciales.
 */
Playlist::Playlist() {
    setId(0);
    _nombre[0] = '\0';
    _idSuscriptorCreador = 0;
    // La fecha se inicializa por defecto en su propio constructor (0/0/0)
    _estado = true;
}

/**

 * Asigna el numero unico que identifica esta lista.
 * Parametros: id - El numero identificador.
 */
void Playlist::setIdPlaylist(int id) { setId(id); }

/**
 * Asigna el titulo que el usuario le dio a la lista.
 * Parametros: n - El nombre de la playlist.
 */
void Playlist::setNombre(const char* n) {
    strcpy(_nombre, n);
}

/**
 * Asigna quien es el usuario que creo esta lista.
 * Parametros: id - El ID del creador.
 */
void Playlist::setIdSuscriptorCreador(int id) { _idSuscriptorCreador = id; }

/**
 * Asigna cuando se hizo esta lista por primera vez.
 * Parametros: f - La fecha de creacion.
 */
void Playlist::setFechaCreacion(Fecha f) { _fechaCreacion = f; } // <--- NUEVO

/**
 * Marca si esta lista sigue disponible o fue eliminada.
 * Parametros: estado - Estado activo/inactivo.
 */
void Playlist::setEstado(bool estado) { _estado = estado; }

/**
 * Dice cual es el numero de esta lista.
 * Retorna: El ID unico.
 */
int Playlist::getIdPlaylist() { return getId(); }

/**
 * Dice cual es el titulo de esta lista.
 * Retorna: El nombre de la playlist.
 */
const char* Playlist::getNombre() { return _nombre; }

/**
 * Dice quien es el dueno de esta lista.
 * Retorna: El ID del creador.
 */
int Playlist::getIdSuscriptorCreador() { return _idSuscriptorCreador; }

/**
 * Dice cuando se creo esta lista.
 * Retorna: La fecha de creacion.
 */
Fecha Playlist::getFechaCreacion() { return _fechaCreacion; } // <--- NUEVO

/**
 * Dice si esta lista esta disponible.
 * Retorna: El estado.
 */
bool Playlist::getEstado() { return _estado; }

/**
 * Pide al usuario que escriba el nombre de la lista.
 */
void Playlist::Cargar() {
    char buffer[50];
    InputHelper::pedirCadena("Nombre de la Playlist: ", buffer, 50);
    setNombre(buffer);

    // La fecha se setea automaticamente desde fuera (musicon.cpp) al crearla,
    // por lo que no la pedimos aqui al usuario.

    _estado = true;
}

void Playlist::Mostrar() {
    if (_estado) {
        cout << "ID Lista: " << getIdPlaylist() << " | Nombre: " << _nombre << endl;
        cout << "Creada por ID Usuario: " << _idSuscriptorCreador << endl;
        cout << "Fecha Creacion: " << _fechaCreacion.toString() << endl; // <--- NUEVO
        cout << "-------------------------" << endl;
    }
}

