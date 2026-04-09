/**
 * Este archivo implementa la clase Artista con métodos de inicialización, setters/getters,
 * carga y muestra de datos del artista.
 */

#include "../include/Artista.h"
#include "InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor por defecto: Inicializa nombre vacío, estado inactivo, ID en 0 y nacionalidad vacía.
 */
Artista::Artista() {
    _nombre[0] = '\0';
    _estado = false;
    _idArtista = 0;
    strcpy(_nacionalidad, "");
}

/**
 * Destructor: No hay recursos din�micos, pero se define para consistencia.
 */
Artista::~Artista() {}

/**
 * Setter para el ID del artista.
 * Par�metros: id - ID �nico a asignar.
 */
void Artista::setIdArtista(int id) { _idArtista = id; }

/**
 * Setter para la nacionalidad.
 * Par�metros: nacionalidad - Cadena con la nacionalidad (copia segura con l�mite).
 */
void Artista::setNacionalidad(const char* nacionalidad) { strncpy(_nacionalidad, nacionalidad, 49); _nacionalidad[49] = '\0'; }

/**
 * Getter para el ID del artista.
 * Retorno: ID �nico.
 */
int Artista::getIdArtista() { return _idArtista; }

/**
 * Getter para la nacionalidad.
 * Retorno: Puntero constante a la cadena de nacionalidad.
 */
const char* Artista::getNacionalidad() { return _nacionalidad; }

/**
 * Método Cargar: Solicita nombre y nacionalidad al usuario y activa el registro.
 * No pide ID porque se genera automáticamente.
 */
void Artista::Cargar() {
    char buffer[100];

    InputHelper::pedirCadena("Nombre: ", buffer, 100);
    setNombre(buffer);

    InputHelper::pedirCadena("Nacionalidad: ", buffer, 50);
    setNacionalidad(buffer);

    setEstado(true);
}

/**
 * M�todo Mostrar: Imprime ID, nombre y nacionalidad si el artista est� activo.
 * Formato compacto para listados.
 */
void Artista::Mostrar() {
    if (getEstado()) {
        cout << "ID: " << _idArtista << " | " << getNombre() << " (" << _nacionalidad << ")" << endl;
    }
}
