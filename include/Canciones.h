#ifndef CANCIONES_H
#define CANCIONES_H

class Canciones {
private:

    int _idCancion;
    char _nombre[100];
    int _idAlbum;
    int _idGenero;
    int _duracionSegundos;
    bool _estado;

public:
    // Constructor
    Canciones();
    // Destructor
    virtual ~Canciones();


    // Setters
    void setIdCancion(int id);
    void setNombre(const char* nombre);
    void setIdAlbum(int idAl);
    void setIdGenero(int idGe);
    void setDuracionSegundos(int duracion);
    void setEstado(bool e);

    // Getters
    int getIdCancion();
    const char* getNombre();
    int getIdAlbum();
    int getIdGenero();
    int getDuracionSegundos();
    bool getEstado();

    void Cargar();
    void Mostrar();
};

#endif // CANCIONES_H
