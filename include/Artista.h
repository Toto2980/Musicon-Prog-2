#ifndef ARTISTA_H
#define ARTISTA_H

class Artista
{
    private:
        int _idArtista;
        char _nombre[100];
        char _nacionalidad[50];
        bool _estado;

    public:
        Artista();
        virtual ~Artista();

        void setIdArtista(int id);
        void setNombre(const char* nombre);
        void setNacionalidad(const char* nacionalidad);
        void setEstado(bool estado);

        int getIdArtista();
        const char* getNombre();
        const char* getNacionalidad();
        bool getEstado();

        void Cargar();
        void Mostrar();
};

#endif // ARTISTA_H
