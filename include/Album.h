/** Este archivo implementa la clase Album, que representa un album musical en el sistema Musicon.
 * Contiene atributos como titulo, artista, ano de publicacion y estado. Incluye metodos
 * para persistencia en archivo binario (guardar, leer, modificar) y busquedas. */

#ifndef ALBUM_H
#define ALBUM_H

#include "EntidadPadre.h"

/** Clase que representa un album musical con atributos como ID, titulo, artista, ano de publicacion y estado. Incluye metodos para persistencia en archivo binario. */
class Album : public EntidadPadre {
    private:
        char _titulo[100]; // Titulo del album
        int _idArtista; // ID del artista (clave foranea)
        int _anioPublicacion; // Ano de lanzamiento
        bool _estado; // Estado activo/inactivo

    public:
        /** Constructor por defecto de la clase Album. */
        Album();

        // --- SETTERS ---
        /** Establece el ID del album. Parametros: id - ID unico del album. */
        void setIdAlbum(int id);

        /** Establece el titulo del album. Parametros: titulo - Cadena con el titulo. */
        void setTitulo(const char* titulo);

        /** Establece el ID del artista. Parametros: idAr - ID del artista. */
        void setIdArtista(int idAr);

        /** Establece el ano de publicacion. Parametros: anio - Ano de lanzamiento. */
        void setAnioPublicacion(int anio);

        /** Establece el estado activo/inactivo. Parametros: e - true para activo, false para inactivo. */
        void setEstado(bool e);

        // --- GETTERS ---
        /** Obtiene el ID del album. Retorna: ID unico del album. */
        int getIdAlbum();

        /** Obtiene el titulo del album. Retorna: Puntero a la cadena del titulo. */
        const char* getTitulo();

        /** Obtiene el ID del artista. Retorna: ID del artista. */
        int getIdArtista();

        /** Obtiene el ano de publicacion. Retorna: Ano de lanzamiento. */
        int getAnioPublicacion();

        /** Obtiene el estado activo/inactivo. Retorna: true si activo, false si inactivo. */
        bool getEstado();

        // --- E/S (Interfaz con usuario) ---
        /** Carga los datos del album desde la entrada del usuario. */
        void Cargar();

        /** Muestra los datos del album en la consola. */
        void Mostrar();

        // --- PERSISTENCIA ---
        /** Guarda el album en el archivo binario (agrega al final). Retorna: true si se guardo correctamente, false en caso de error. */
        bool Guardar();

        /** Lee un album desde el archivo binario en la posicion especificada. Parametros: pos - Posicion en el archivo (basado en 0). Retorna: true si se leyo correctamente, false en caso de error. */
        bool Leer(int pos);

        /** Modifica un album en el archivo binario en la posicion especificada. Parametros: pos - Posicion a modificar. Retorna: true si se modifico correctamente, false en caso de error. */
        bool Modificar(int pos);

        /** Obtiene la cantidad total de registros (albumes) en el archivo. Retorna: Numero de albumes guardados. */
        int ObtenerCantidadRegistros();

        /** Busca el ID de un album por su titulo (comparacion insensible a mayusculas). Parametros: titulo - Titulo a buscar. Retorna: ID del album si se encuentra, -1 si no. */
        int BuscarIDPorTitulo(const char* titulo);

        /** Busca la posicion en el archivo de un album por su ID. Parametros: id - ID del album a buscar. Retorna: Posicion en el archivo (basado en 0), -1 si no se encuentra. */
        int BuscarPosicionPorID(int id);
};

#endif // ALBUM_H
