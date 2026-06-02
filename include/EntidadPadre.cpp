#include "EntidadPadre.h"

EntidadPadre::EntidadPadre() : _id(0) {}

EntidadPadre::~EntidadPadre() = default;

void EntidadPadre::setId(int id) {
	_id = id;
}

int EntidadPadre::getId() const {
	return _id;
}
