#ifndef DETALLEPLAYLIST_H
#define DETALLEPLAYLIST_H

#include "Fecha.h"

class DetallePlaylist {
private:
    int _idPlaylist;
    int _idCancion;
    Fecha _fechaAgregado;
    bool _estado;

public:
    DetallePlaylist();

    void setIdPlaylist(int id);
    void setIdCancion(int id);
    void setFechaAgregado(Fecha f);
    void setEstado(bool e);

    int getIdPlaylist();
    int getIdCancion();
    Fecha getFechaAgregado();
    bool getEstado();
};

#endif // DETALLEPLAYLIST_H
