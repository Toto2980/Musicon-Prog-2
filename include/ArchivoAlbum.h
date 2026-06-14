#ifndef ARCHIVOALBUM_H
#define ARCHIVOALBUM_H

#include "Album.h"
#include <string>

/** Clase para manejar la persistencia de álbumes en archivo binario. */
class ArchivoAlbum {
    private:
        std::string _nombreArchivo;

    public:
        /** Constructor de ArchivoAlbum. Parámetros: nombreArchivo - Nombre del archivo binario, por defecto "albumes.dat". */
        ArchivoAlbum(std::string nombreArchivo = "albumes.dat");

        /** Guarda un registro de álbum en el archivo. Parámetros: reg - El álbum a guardar. Retorna: true si se guardó, false en caso de error. */
        bool Guardar(Album reg);
        /** Lee un álbum desde el archivo en la posición especificada. Parámetros: pos - Posición en el archivo. Retorna: El álbum leído. */
        Album Leer(int pos);
        /** Busca la posición de un álbum por su ID. Parámetros: id - ID del álbum. Retorna: Posición en el archivo, -1 si no encontrado. */
        int BuscarPosicion(int id);
        /** Busca el ID de un álbum por su título. Parámetros: titulo - Título del álbum. Retorna: ID del álbum, -1 si no encontrado. */
        int BuscarIDPorTitulo(const char* titulo);
        /** Genera un nuevo ID único para un álbum. Retorna: Nuevo ID. */
        int GenerarIDNuevo();
        /** Obtiene la cantidad de registros en el archivo. Retorna: Cantidad de álbumes. */
        int ObtenerCantidadRegistros();
        /** Busca un álbum por su ID. Parámetros: id - ID del álbum. Retorna: El álbum encontrado. */
        Album BuscarPorID(int id);

        // NUEVO: Busca por Titulo Y Artista (para evitar homónimos)
        /** Busca un álbum por título y artista, o lo crea si no existe. Parámetros: tituloAlbum - Título del álbum, idArtista - ID del artista. Retorna: ID del álbum. */
        int BuscarOCrear(std::string tituloAlbum, int idArtista);
};

#endif // ARCHIVOALBUM_H
