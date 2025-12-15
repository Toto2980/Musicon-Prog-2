#include <iostream>
#include "DetallePlaylist.h"

using namespace std;

DetallePlaylist::DetallePlaylist() {
    //ctor
    _idPlaylist = 0;
    _idCancion = 0;
    _estado = true;

}

void DetallePlaylist::setIdPlaylist(int id) { _idPlaylist = id; }
void DetallePlaylist::setIdCancion(int id) { _idCancion = id; }
void DetallePlaylist::setFechaAgregado(Fecha f) { _fechaAgregado = f; }
void DetallePlaylist::setEstado(bool e) { _estado = e; }

int DetallePlaylist::getIdPlaylist() { return _idPlaylist; }
int DetallePlaylist::getIdCancion() { return _idCancion; }
Fecha DetallePlaylist::getFechaAgregado() { return _fechaAgregado; }
bool DetallePlaylist::getEstado() { return _estado; }

void DetallePlaylist::Cargar() {
    cout << "Ingrese ID de la Playlist: ";
    cin >> _idPlaylist;

    cout << "Ingrese ID de la Cancion a agregar: ";
    cin >> _idCancion;

    cout << "--- Fecha de Agregado ---" << endl;
    _fechaAgregado.Cargar();

    _estado = true;
}

void DetallePlaylist::Mostrar() {
    if (_estado == true) {
        cout << "ID Playlist : " << _idPlaylist << endl;
        cout << "ID Cancion  : " << _idCancion << endl;
        cout << "Agregada el : ";
        _fechaAgregado.Mostrar();
        cout << endl;
    }
}
