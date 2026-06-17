/**
 * Este archivo implementa la clase Album con métodos para gestionar datos de álbumes.
 * Incluye inicialización, validaciones, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Album.h"
#include "../include/InputHelper.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cctype>

using namespace std;

/**
 * Inicializa todos los atributos con valores neutros.
 */
Album::Album() {
    setId(0);
    strcpy(_titulo, "");
    _idArtista = 0;
    _anioPublicacion = 0;
    _estado = false;
}

/**
 * Establece los valores de los atributos con validaciones básicas.
 */
void Album::setIdAlbum(int id) { setId(id); }
void Album::setTitulo(const char* titulo) { strncpy(_titulo, titulo, 99); _titulo[99] = '\0'; }
void Album::setIdArtista(int idAr) { _idArtista = idAr; }
void Album::setAnioPublicacion(int anio) {
    if (anio > 0) _anioPublicacion = anio;
    else _anioPublicacion = 0;
}
void Album::setEstado(bool e) { _estado = e; }

/**
 * Devuelven los valores de los atributos.
 */
int Album::getIdAlbum() { return getId(); }
const char* Album::getTitulo() { return _titulo; }
int Album::getIdArtista() { return _idArtista; }
int Album::getAnioPublicacion() { return _anioPublicacion; }
bool Album::getEstado() { return _estado; }

/**
 * Método Cargar: Solicita al usuario los datos del álbum.
 * Pide ID, artista, título y año; establece estado activo.
 */
void Album::Cargar() {
    cout << "Ingrese ID del Artista: "; cin >> _idArtista;
    cin.ignore();
    cout << "Ingrese Titulo del Album: "; cin.getline(_titulo, 99);
    cout << "Ingrese Anio de Publicacion: "; cin >> _anioPublicacion;
    _estado = true;
}

/**
 * Método Mostrar: Imprime los datos del álbum si está activo.
 */
void Album::Mostrar() {
    if (_estado == true) {
        cout << "ID: " << getIdAlbum() << " | Titulo: " << _titulo << " | ArtistaID: " << _idArtista << endl;
    }
}


// --- PERSISTENCIA ---

/**
 * Guardar: Agrega el álbum al final del archivo binario "albumes.dat".
 * Retorno: true si se escribió correctamente, false si error al abrir o escribir.
 */
bool Album::Guardar() {
    FILE *p = fopen("albumes.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

/**
 * Leer: Lee un álbum desde la posición especificada en el archivo.
 * Parámetros: pos - Posición (basado en 0, multiplica por sizeof(Album)).
 * Retorno: true si se leyó correctamente.
 */
bool Album::Leer(int pos) {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Album), SEEK_SET);
    bool ok = fread(this, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

/**
 * Modificar: Sobrescribe el álbum en la posición especificada.
 * Parámetros: pos - Posición a modificar.
 * Retorno: true si se modificó correctamente.
 */
bool Album::Modificar(int pos) {
    FILE *p = fopen("albumes.dat", "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Album), SEEK_SET);
    bool ok = fwrite(this, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

/**
 * ObtenerCantidadRegistros: Calcula el número de álbumes en el archivo.
 * Usa fseek a SEEK_END y divide por el tamaño del registro.
 * Retorno: Cantidad de registros.
 */
int Album::ObtenerCantidadRegistros() {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Album);
    fclose(p);
    return cant;
}

/**
 * BuscarIDPorTitulo: Busca el ID de un álbum por título (insensible a mayúsculas).
 * Parámetros: titulo - Título a buscar.
 * Retorno: ID si encontrado y activo, -1 si no.
 */
int Album::BuscarIDPorTitulo(const char* titulo) {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return -1;
    Album aux;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(InputHelper::sonIgualesSinMayusculas(aux.getTitulo(), titulo) && aux.getEstado()) {
            fclose(p);
            return aux.getIdAlbum();
        }
    }
    fclose(p);
    return -1;
}

/**
 * BuscarPosicionPorID: Busca la posición de un álbum por su ID.
 * Parámetros: id - ID a buscar.
 * Retorno: Posición si encontrado y activo, -1 si no.
 */
int Album::BuscarPosicionPorID(int id) {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return -1;
    Album aux;
    int pos = 0;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(aux.getIdAlbum() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
