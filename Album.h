#ifndef ALBUM_H
#define ALBUM_H

class Album {
private:

    int _idAlbum;
    char _titulo[100];
    int _idArtista;
    int _anioPublicacion;
    bool _estado;

public:
    // Constructor
    Album();
    virtual ~Album();

    // Setters
    void setIdAlbum(int id);
    void setTitulo(const char* titulo);
    void setIdArtista(int idAr);
    void setAnioPublicacion(int anio);
    void setEstado(bool e);

    // Getters
    int getIdAlbum();
    const char* getTitulo();
    int getIdArtista();
    int getAnioPublicacion();
    bool getEstado();

    // Falta Cargar() y Mostrar()
    void Cargar();
    void Mostrar();
};

#endif // ALBUM_H
