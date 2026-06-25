#include <iostream>
#include <cstdio>
#include "../include/DetallePlaylist.h"

using namespace std;

/**
 * Este archivo implementa la clase DetallePlaylist, que conecta canciones con playlists.
 * Maneja la relacion entre una playlist y las canciones que contiene, con fechas de agregado.
 */

/**
 * Crea un nuevo detalle de playlist vacio.
 * Prepara un espacio para conectar una cancion con una playlist, con estado activo por defecto.
 */
DetallePlaylist::DetallePlaylist() {
    _idPlaylist = 0;
    _idCancion = 0;
    _estado = true;
}

/**
 * Asigna el ID de la playlist a la que pertenece esta conexion.
 * Parametros: id - El numero unico de la playlist.
 */
void DetallePlaylist::setIdPlaylist(int id) { _idPlaylist = id; }

/**
 * Asigna el ID de la cancion que se agrega a la playlist.
 * Parametros: id - El numero unico de la cancion.
 */
void DetallePlaylist::setIdCancion(int id) { _idCancion = id; }

/**
 * Asigna la fecha en que se agrego la cancion a la playlist.
 * Parametros: f - La fecha y hora del momento de agregar.
 */
void DetallePlaylist::setFechaAgregado(Fecha f) { _fechaAgregado = f; }

/**
 * Marca si esta conexion esta activa o no.
 * Parametros: e - Verdadero si la cancion sigue en la playlist, falso si fue removida.
 */
void DetallePlaylist::setEstado(bool e) { _estado = e; }

/**
 * Dice a cual playlist pertenece.
 * Retorna: El ID de la playlist.
 */
int DetallePlaylist::getIdPlaylist() { return _idPlaylist; }

/**
 * Dice cual cancion esta conectada.
 * Retorna: El ID de la cancion.
 */
int DetallePlaylist::getIdCancion() { return _idCancion; }

/**
 * Dice cuando se agrego la cancion.
 * Retorna: La fecha y hora de agregado.
 */
Fecha DetallePlaylist::getFechaAgregado() { return _fechaAgregado; }

/**
 * Dice si la conexion sigue activa.
 * Retorna: Verdadero si la cancion esta en la playlist.
 */
bool DetallePlaylist::getEstado() { return _estado; }

/**
 * Pide al usuario que ingrese los datos para conectar una cancion con una playlist.
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
 * Muestra en pantalla la informacion de esta conexion, si esta activa.
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
 * Guarda esta conexion en un archivo para recordarla.
 * Retorna: Verdadero si se guardo sin problemas.
 */
bool DetallePlaylist::Guardar() {
    FILE *p = fopen("Listas_Canciones.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(DetallePlaylist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Carga una conexion desde el archivo en una posicion especifica.
 * Parametros: pos - La posicion en la lista.
 * Retorna: Verdadero si se cargo correctamente.
 */
bool DetallePlaylist::Leer(int pos) {
    FILE *p = fopen("Listas_Canciones.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(DetallePlaylist), SEEK_SET);
    bool ok = fread(this, sizeof(DetallePlaylist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Cuenta cuantas conexiones hay guardadas en total.
 * Retorna: El numero total de conexiones.
 */
int DetallePlaylist::ObtenerCantidadRegistros() {
    FILE *p = fopen("Listas_Canciones.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(DetallePlaylist);
    fclose(p);
    return cant;
}

// ACCIONES ESPECIALES

/**
 * Verifica si una cancion especifica ya esta en una playlist dada.
 * Parametros: idPlaylist - El ID de la playlist a revisar, idCancion - El ID de la cancion a buscar.
 * Retorna: La posicion si existe, o -1 si no esta.
 */
int DetallePlaylist::BuscarCancionEnPlaylist(int idPlaylist, int idCancion) {
    FILE *p = fopen("Listas_Canciones.dat", "rb");
    if (p == NULL) return -1;

    DetallePlaylist aux;
    int pos = 0;
    while(fread(&aux, sizeof(DetallePlaylist), 1, p)) {
        if(aux.getIdPlaylist() == idPlaylist &&
           aux.getIdCancion() == idCancion &&
           aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
