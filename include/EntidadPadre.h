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
	
	EntidadPadre();
	~EntidadPadre();
	
	void setId(int id);
	int getId() const;
};

#endif // ENTIDADPADRE_H
