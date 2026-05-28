#ifndef ENTIDADPADRE_H
#define ENTIDADPADRE_H

/**
 * Clase base mínima para entidades que comparten un identificador único.
 * Se usa solo en clases donde el campo ID ya está posicionado al inicio
 * para preservar el layout de datos de las clases persistidas en binario.
 */
class EntidadPadre {
protected:
    int _id;

public:
    EntidadPadre() : _id(0) {}
    ~EntidadPadre() = default;

    void setId(int id) { _id = id; }
    int getId() const { return _id; }
};

#endif // ENTIDADPADRE_H
