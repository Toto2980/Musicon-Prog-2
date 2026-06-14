#include <iostream>
#include "../include/DetallePlaylist.h"
#include "../include/ArchivoBinario.h"
#include "../include/Constantes.h"

using namespace std;

/**
 * Este archivo implementa la clase DetallePlaylist, que conecta canciones con playlists.
 * Maneja la relación entre una playlist y las canciones que contiene, con fechas de agregado.
 */

/**
 * Crea un nuevo detalle de playlist vacío.
 * Prepara un espacio para conectar una canción con una playlist, con estado activo por defecto.
 */
DetallePlaylist::DetallePlaylist() {
    _idPlaylist = 0;
    _idCancion = 0;
    _estado = true;
}

/**
 * Asigna el ID de la playlist a la que pertenece esta conexión.
 * Parámetros: id - El número único de la playlist.
 */
void DetallePlaylist::setIdPlaylist(int id) { _idPlaylist = id; }

/**
 * Asigna el ID de la canción que se agrega a la playlist.
 * Parámetros: id - El número único de la canción.
 */
void DetallePlaylist::setIdCancion(int id) { _idCancion = id; }

/**
 * Asigna la fecha en que se agregó la canción a la playlist.
 * Parámetros: f - La fecha y hora del momento de agregar.
 */
void DetallePlaylist::setFechaAgregado(Fecha f) { _fechaAgregado = f; }

/**
 * Marca si esta conexión está activa o no.
 * Parámetros: e - Verdadero si la canción sigue en la playlist, falso si fue removida.
 */
void DetallePlaylist::setEstado(bool e) { _estado = e; }

/**
 * Dice a cuál playlist pertenece.
 * Retorna: El ID de la playlist.
 */
int DetallePlaylist::getIdPlaylist() { return _idPlaylist; }

/**
 * Dice cuál canción está conectada.
 * Retorna: El ID de la canción.
 */
int DetallePlaylist::getIdCancion() { return _idCancion; }

/**
 * Dice cuándo se agregó la canción.
 * Retorna: La fecha y hora de agregado.
 */
Fecha DetallePlaylist::getFechaAgregado() { return _fechaAgregado; }

/**
 * Dice si la conexión sigue activa.
 * Retorna: Verdadero si la canción está en la playlist.
 */
bool DetallePlaylist::getEstado() { return _estado; }

/**
 * Pide al usuario que ingrese los datos para conectar una canción con una playlist.
 * Solicita IDs y fecha desde el teclado.
 */
void DetallePlaylist::Cargar() {
    cout << "Ingrese ID de la Playlist: ";
    cin >> _idPlaylist;
    cout << "Ingrese ID de la Cancion a agregar: ";
    cin >> _idCancion;
    cout << "--- Fecha de Agregado ---" << endl;
    _fechaAgregado.Cargar();
    _estado = true;
}

/**
 * Muestra en pantalla la información de esta conexión, si está activa.
 * Imprime IDs y fecha de agregado.
 */
void DetallePlaylist::Mostrar() {
    if (_estado == true) {
        cout << "ID Playlist : " << _idPlaylist << endl;
        cout << "ID Cancion  : " << _idCancion << endl;
        cout << "Agregada el : ";
        _fechaAgregado.Mostrar();
        cout << endl;
    }
}

// GUARDAR Y CARGAR DATOS

/**
 * Guarda esta conexión en un archivo para recordarla.
 * Retorna: Verdadero si se guardó sin problemas.
 */
bool DetallePlaylist::Guardar() {
    return ArchivoBinario<DetallePlaylist>(cfg::archivos::DETALLE_PL).agregar(*this);
}

/**
 * Carga una conexión desde el archivo en una posición específica.
 * Parámetros: pos - La posición en la lista.
 * Retorna: Verdadero si se cargó correctamente.
 */
bool DetallePlaylist::Leer(int pos) {
    return ArchivoBinario<DetallePlaylist>(cfg::archivos::DETALLE_PL).leer(pos, *this);
}

/**
 * Cuenta cuántas conexiones hay guardadas en total.
 * Retorna: El número total de conexiones.
 */
int DetallePlaylist::ObtenerCantidadRegistros() {
    return ArchivoBinario<DetallePlaylist>(cfg::archivos::DETALLE_PL).contar();
}

// ACCIONES ESPECIALES

/**
 * Verifica si una canción específica ya está en una playlist dada.
 * Parámetros: idPlaylist - El ID de la playlist a revisar, idCancion - El ID de la canción a buscar.
 * Retorna: La posición si existe, o -1 si no está.
 */
int DetallePlaylist::BuscarCancionEnPlaylist(int idPlaylist, int idCancion) {
    std::vector<DetallePlaylist> todos =
        ArchivoBinario<DetallePlaylist>(cfg::archivos::DETALLE_PL).leerTodos();
    for (size_t pos = 0; pos < todos.size(); ++pos) {
        if (todos[pos].getIdPlaylist() == idPlaylist &&
            todos[pos].getIdCancion() == idCancion &&
            todos[pos].getEstado()) {
            return static_cast<int>(pos);
        }
    }
    return -1;
}
