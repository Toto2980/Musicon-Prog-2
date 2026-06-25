/**
 * Este archivo implementa la clase Artista con metodos de inicializacion, setters/getters,
 * carga y muestra de datos del artista.
 */

#include "../include/Artista.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor por defecto: Inicializa nombre vacio, estado inactivo, ID en 0 y nacionalidad vacia.
 */
Artista::Artista() {
    setId(0);
    _nombre[0] = '\0';
    _estado = false;
    strcpy(_nacionalidad, "");
}

/**
 * Destructor: No hay recursos dinamicos, pero se define para consistencia.
 */
Artista::~Artista() {}

/**
 * Setter para el ID del artista.
 * Parametros: id - ID unico a asignar.
 */
void Artista::setIdArtista(int id) { setId(id); }

/**
 * Setter para la nacionalidad.
 * Parametros: nacionalidad - Cadena con la nacionalidad (copia segura con limite).
 */
void Artista::setNacionalidad(const char* nacionalidad) { strncpy(_nacionalidad, nacionalidad, 49); _nacionalidad[49] = '\0'; }

/**
 * Getter para el ID del artista.
 * Retorno: ID unico.
 */
int Artista::getIdArtista() { return getId(); }

/**
 * Getter para la nacionalidad.
 * Retorno: Puntero constante a la cadena de nacionalidad.
 */
const char* Artista::getNacionalidad() { return _nacionalidad; }

/**
 * Metodo Cargar: Solicita nombre y nacionalidad al usuario y activa el registro.
 * No pide ID porque se genera automaticamente.
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
 * Metodo Mostrar: Imprime ID, nombre y nacionalidad si el artista esta activo.
 * Formato compacto para listados.
 */
void Artista::Mostrar() {
    if (getEstado()) {
        cout << "ID: " << getIdArtista() << " | " << getNombre() << " (" << _nacionalidad << ")" << endl;
    }
}
