/**
 * Este archivo implementa la clase Album con métodos para gestionar datos de álbumes.
 * Incluye inicialización, validaciones, métodos de carga/muestra y persistencia en archivo binario.
 */

#include "../include/Album.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cctype>

using namespace std;

/**
 * Compara dos textos sin distinguir mayúsculas y minúsculas.
 */
static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false;
        }
        ++texto1;
        ++texto2;
    }

    return *texto1 == *texto2;
}

/**
 * Inicializa todos los atributos con valores neutros.
 */
Album::Album() {
    _idAlbum = 0;
    strcpy(_titulo, "");
    _idArtista = 0;
    _anioPublicacion = 0;
    _estado = false;
}

/**
 * Establece los valores de los atributos con validaciones básicas.
 */
void Album::setIdAlbum(int id) { _idAlbum = id; }
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
int Album::getIdAlbum() { return _idAlbum; }
const char* Album::getTitulo() { return _titulo; }
int Album::getIdArtista() { return _idArtista; }
int Album::getAnioPublicacion() { return _anioPublicacion; }
bool Album::getEstado() { return _estado; }

/**
 * M�todo Cargar: Solicita al usuario los datos del �lbum.
 * Pide ID, artista, t�tulo y a�o; establece estado activo.
 */
void Album::Cargar() {
    cout << "Ingrese ID de Album: "; cin >> _idAlbum;
    cout << "Ingrese ID del Artista: "; cin >> _idArtista;
    cin.ignore();
    cout << "Ingrese Titulo del Album: "; cin.getline(_titulo, 99);
    cout << "Ingrese Anio de Publicacion: "; cin >> _anioPublicacion;
    _estado = true;
}

/**
 * M�todo Mostrar: Imprime los datos del �lbum si est� activo.
 */
void Album::Mostrar() {
    if (_estado == true) {
        cout << "ID: " << _idAlbum << " | Titulo: " << _titulo << " | ArtistaID: " << _idArtista << endl;
    }
}

/**
 * Destructor: No hay recursos din�micos que liberar.
 */
Album::~Album() {}

// --- PERSISTENCIA ---

/**
 * Guardar: Agrega el �lbum al final del archivo binario "albumes.dat".
 * Retorno: true si se escribi� correctamente, false si error al abrir o escribir.
 */
bool Album::Guardar() {
    FILE *p = fopen("albumes.dat", "ab");
    if (p == NULL) return false;
    bool ok = fwrite(this, sizeof(Album), 1, p);
    fclose(p);
    return ok;
}

/**
 * Leer: Lee un �lbum desde la posici�n especificada en el archivo.
 * Par�metros: pos - Posici�n (basado en 0, multiplica por sizeof(Album)).
 * Retorno: true si se ley� correctamente.
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
 * Modificar: Sobrescribe el �lbum en la posici�n especificada.
 * Par�metros: pos - Posici�n a modificar.
 * Retorno: true si se modific� correctamente.
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
 * ObtenerCantidadRegistros: Calcula el n�mero de �lbumes en el archivo.
 * Usa fseek a SEEK_END y divide por el tama�o del registro.
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
 * BuscarIDPorTitulo: Busca el ID de un �lbum por t�tulo (insensible a may�sculas).
 * Par�metros: titulo - T�tulo a buscar.
 * Retorno: ID si encontrado y activo, -1 si no.
 */
int Album::BuscarIDPorTitulo(const char* titulo) {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return -1;
    Album aux;
    while(fread(&aux, sizeof(Album), 1, p)) {
        if(sonIgualesSinMayusculas(aux.getTitulo(), titulo) && aux.getEstado()) {
            fclose(p);
            return aux.getIdAlbum();
        }
    }
    fclose(p);
    return -1;
}

/**
 * BuscarPosicionPorID: Busca la posici�n de un �lbum por su ID.
 * Par�metros: id - ID a buscar.
 * Retorno: Posici�n si encontrado y activo, -1 si no.
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
