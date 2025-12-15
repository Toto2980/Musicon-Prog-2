#ifndef CANCIONES_H
#define CANCIONES_H

// ENTIDAD PRINCIPAL: CANCION
// La unidad básica del sistema. Se vincula a Album y Genero.
class Canciones {
    private:
        int _idCancion;
        char _nombre[100];
        int _idAlbum;   // FK
        int _idGenero;  // FK
        int _duracionSegundos;
        bool _estado;

    public:
        Canciones();
        virtual ~Canciones();

        // --- SETTERS ---
        void setIdCancion(int id);
        void setNombre(const char* nombre);
        void setIdAlbum(int idAl);
        void setIdGenero(int idGe);
        void setDuracionSegundos(int duracion);
        void setEstado(bool e);

        // --- GETTERS ---
        int getIdCancion();
        const char* getNombre();
        int getIdAlbum();
        int getIdGenero();
        int getDuracionSegundos();
        bool getEstado();

        // --- E/S ---
        void Cargar();
        void Mostrar();
};

#endif // CANCIONES_H
