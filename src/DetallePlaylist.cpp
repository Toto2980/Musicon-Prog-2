#include "DetallePlaylist.h"

DetallePlaylist::DetallePlaylist() {
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
