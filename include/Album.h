#ifndef ALBUM_H
#define ALBUM_H

// ENTIDAD: ALBUM
class Album {
    private:
        int _idAlbum;
        char _titulo[100];
        int _idArtista;     // FK a Artista
        int _anioPublicacion;
        bool _estado;

    public:
        Album();
        virtual ~Album();

        // --- SETTERS ---
        void setIdAlbum(int id);
        void setTitulo(const char* titulo);
        void setIdArtista(int idAr);
        void setAnioPublicacion(int anio);
        void setEstado(bool e);

        // --- GETTERS ---
        int getIdAlbum();
        const char* getTitulo();
        int getIdArtista();
        int getAnioPublicacion();
        bool getEstado();

        // --- E/S ---
        void Cargar();
        void Mostrar();
};

#endif // ALBUM_H
