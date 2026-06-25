#ifndef ARCHIVOARTISTAS_H
#define ARCHIVOARTISTAS_H

/*
 * PATRON: Repository
 * Esta clase encapsula TODO el acceso al archivo binario "artistas.dat".
 * La capa Manager no sabe si los datos estan en un .dat, una BD o la nube.
 * Solo llama a Guardar/Leer/Modificar/Buscar. Eso es separacion de capas.
 *
 * POR QUE _nombreArchivo es std::string y no char[]:
 *   std::string es para uso en memoria (no se serializa a disco).
 *   Los char[] fijos son para campos dentro de Artista (que SI van a fwrite).
 *   Aqui _nombreArchivo solo vive en RAM como dato interno de la clase.
 */

#include "Artista.h"
#include <string>

class ArchivoArtistas {
    private:
        std::string _nombreArchivo; // Nombre del .dat (ej: "artistas.dat")

    public:
        // Default: "artistas.dat". Se puede cambiar para testing o backup.
        ArchivoArtistas(std::string nombreArchivo = "artistas.dat");

        // --- CRUD BINARIO ---
        // Modo "ab": append binary -- agrega al final, crea el archivo si no existe.
        bool Guardar(Artista reg);

        // Modo "rb": lee por posicion. pos=2 -> salta 2*sizeof(Artista) bytes.
        Artista Leer(int pos);

        // Modo "rb+": lectura+escritura SIN truncar. Sobreescribe un registro existente.
        // Este es el modo clave para la eliminacion logica (estado=false).
        bool Modificar(int pos, Artista reg);

        // ID autoincremental: lee el ultimo registro y retorna su ID + 1.
        int GenerarIDNuevo();

        // Formula: ftell(SEEK_END) / sizeof(Artista) = cantidad de registros.
        int ObtenerCantidadRegistros();

        // --- BUSQUEDAS (todas O(N) -- busqueda lineal sin indice) ---
        int BuscarPosicion(int id);
        int BuscarPosicionPorNombre(const char* nombre); // case-insensitive
        int BuscarIDPorNombre(const char* nombre);       // devuelve el ID, no la posicion

        // Util para reportes: dado un ID, devuelve el objeto Artista completo.
        Artista BuscarPorID(int id);

        // --- PATRON "BUSCAR O CREAR" (usado en importacion CSV) ---
        // Busca el artista por nombre. Si no existe, lo crea automaticamente.
        // Siempre devuelve un ID valido. Evita duplicados en la importacion.
        int BuscarOCrear(std::string nombreArtista);
};

#endif // ARCHIVOARTISTAS_H
