#ifndef ARTISTA_H
#define ARTISTA_H

// ENTIDAD: ARTISTA
// Creador de los álbumes.
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

        // --- SETTERS ---
        void setIdArtista(int id);
        void setNombre(const char* nombre);
        void setNacionalidad(const char* nacionalidad);
        void setEstado(bool estado);

        // --- GETTERS ---
        int getIdArtista();
        const char* getNombre();
        const char* getNacionalidad();
        bool getEstado();

        // --- E/S ---
        void Cargar();
        void Mostrar();
};

#endif // ARTISTA_H
