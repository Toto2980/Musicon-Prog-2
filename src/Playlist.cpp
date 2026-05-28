#include "Playlist.h"
#include "InputHelper.h" // Usamos tu helper para inputs seguros
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

/**
 * Este archivo implementa la clase Playlist, con métodos para crear, guardar y buscar playlists.
 * Maneja la persistencia de datos en archivos y la interacción con el usuario.
 */

/**
 * Prepara una nueva lista de canciones vacía con valores iniciales.
 */
Playlist::Playlist() {
    setId(0);
    _nombre[0] = '\0';
    _idSuscriptorCreador = 0;
    // La fecha se inicializa por defecto en su propio constructor (0/0/0)
    _estado = true;
}

/**

 * Asigna el número único que identifica esta lista.
 * Parámetros: id - El número identificador.
 */
void Playlist::setIdPlaylist(int id) { setId(id); }

/**
 * Asigna el título que el usuario le dio a la lista.
 * Parámetros: n - El nombre de la playlist.
 */
void Playlist::setNombre(const char* n) {
    strcpy(_nombre, n);
}

/**
 * Asigna quién es el usuario que creó esta lista.
 * Parámetros: id - El ID del creador.
 */
void Playlist::setIdSuscriptorCreador(int id) { _idSuscriptorCreador = id; }

/**
 * Asigna cuándo se hizo esta lista por primera vez.
 * Parámetros: f - La fecha de creación.
 */
void Playlist::setFechaCreacion(Fecha f) { _fechaCreacion = f; } // <--- NUEVO

/**
 * Marca si esta lista sigue disponible o fue eliminada.
 * Parámetros: estado - Estado activo/inactivo.
 */
void Playlist::setEstado(bool estado) { _estado = estado; }

/**
 * Dice cuál es el número de esta lista.
 * Retorna: El ID único.
 */
int Playlist::getIdPlaylist() { return getId(); }

/**
 * Dice cuál es el título de esta lista.
 * Retorna: El nombre de la playlist.
 */
const char* Playlist::getNombre() { return _nombre; }

/**
 * Dice quién es el dueño de esta lista.
 * Retorna: El ID del creador.
 */
int Playlist::getIdSuscriptorCreador() { return _idSuscriptorCreador; }

/**
 * Dice cuándo se creó esta lista.
 * Retorna: La fecha de creación.
 */
Fecha Playlist::getFechaCreacion() { return _fechaCreacion; } // <--- NUEVO

/**
 * Dice si esta lista está disponible.
 * Retorna: El estado.
 */
bool Playlist::getEstado() { return _estado; }

/**
 * Pide al usuario que escriba el nombre de la lista.
 */
void Playlist::Cargar() {
    char buffer[50];
    InputHelper::pedirCadena("Nombre de la Playlist: ", buffer, 50);
    setNombre(buffer);

    // La fecha se setea automáticamente desde fuera (musicon.cpp) al crearla,
    // por lo que no la pedimos aquí al usuario.

    _estado = true;
}

void Playlist::Mostrar() {
    if (_estado) {
        cout << "ID Lista: " << getIdPlaylist() << " | Nombre: " << _nombre << endl;
        cout << "Creada por ID Usuario: " << _idSuscriptorCreador << endl;
        cout << "Fecha Creacion: " << _fechaCreacion.toString() << endl; // <--- NUEVO
        cout << "-------------------------" << endl;
    }
}

// --- PERSISTENCIA ---

/**
 * Guarda la lista en un archivo para no perderla.
 * Retorna: Verdadero si se guardó sin problemas.
 */
bool Playlist::Guardar() {
    FILE *p = fopen("playlists.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Carga una lista desde el archivo en una posición específica.
 * Parámetros: pos - La posición en la lista de listas guardadas.
 * Retorna: Verdadero si se cargó correctamente.
 */
bool Playlist::Leer(int pos) {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Playlist), SEEK_SET);
    bool ok = fread(this, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Actualiza la información de la lista en el archivo.
 * Parámetros: pos - La posición a cambiar.
 * Retorna: Verdadero si se actualizó bien.
 */
bool Playlist::Modificar(int pos) {
    FILE *p = fopen("playlists.dat", "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Playlist), SEEK_SET);
    bool ok = fwrite(this, sizeof(Playlist), 1, p);
    fclose(p);
    return ok;
}

/**
 * Cuenta cuántas listas hay guardadas en total.
 * Retorna: El número total de listas.
 */
int Playlist::ObtenerCantidadRegistros() {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Playlist);
    fclose(p);
    return cant;
}

/**
 * Crea un nuevo número único para una lista.
 * Retorna: El siguiente número disponible.
 */
int Playlist::GenerarIDNuevo() {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return 1;
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size < static_cast<long>(sizeof(Playlist))) {
        fclose(p);
        return 1;
    }
    fseek(p, -static_cast<long>(sizeof(Playlist)), SEEK_END);
    Playlist ultimo;
    fread(&ultimo, sizeof(Playlist), 1, p);
    fclose(p);
    return ultimo.getIdPlaylist() + 1;
}

/**
 * Busca una lista por su número identificador.
 * Parámetros: id - El ID a buscar.
 * Retorna: La posición si la encontró, o -1 si no existe.
 */
int Playlist::BuscarPorID(int id) {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return -1;
    Playlist aux;
    int i = 0;
    while(fread(&aux, sizeof(Playlist), 1, p)) {
        if(aux.getIdPlaylist() == id && aux.getEstado()) {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca una lista por su nombre.
 * Parámetros: nombre - Nombre a buscar.
 * Retorna: Posición si encontrada, -1 si no.
 */
int Playlist::BuscarPorNombre(const char* nombre) {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return -1;
    Playlist aux;
    int i = 0;
    while(fread(&aux, sizeof(Playlist), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getNombre(), nombre) && aux.getEstado()) {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
