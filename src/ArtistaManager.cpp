/**
 * Este archivo implementa la clase ArtistaManager. Maneja el CRUD basico para artistas,
 * incluyendo agregar, modificar, eliminar y listar artistas del sistema.
 */

#include "../include/ArtistaManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Agrega un nuevo artista al sistema. Genera ID unico y solicita datos al usuario.
 */
void ArtistaManager::Agregar() {
    Artista nuevo;
    int id = _archivoArtistas.GenerarIDNuevo(); // Genera ID unico
    nuevo.setIdArtista(id);
    nuevo.Cargar(); // Solicita datos al usuario
    nuevo.setEstado(true);

    if (_archivoArtistas.Guardar(nuevo)) { // Guarda el artista
        cout << "Artista guardado. (ID " << id << ")" << endl;
    } else {
        cout << "Error al guardar el artista." << endl;
    }
}

/**
 * Modifica un artista existente. Busca por nombre y permite cambiar nombre y nacionalidad.
 */
void ArtistaManager::Modificar() {
    char nombre[100];
    InputHelper::pedirCadena("Ingrese nombre del artista a modificar: ", nombre, 100);

    int id = _archivoArtistas.BuscarIDPorNombre(nombre);
    if (id == -1) {
        cout << "Artista no encontrado." << endl;
        return;
    }

    int pos = _archivoArtistas.BuscarPosicion(id);
    if (pos == -1) {
        cout << "Error interno: artista no encontrado en el archivo." << endl;
        return;
    }

    Artista reg = _archivoArtistas.Leer(pos);
    cout << "--- ARTISTA ENCONTRADO ---" << endl;
    reg.Mostrar();

    char buffer[100];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", buffer, 100);
    if (strlen(buffer) > 0) reg.setNombre(buffer);

    InputHelper::pedirCadena("Nueva Nacionalidad (Enter para mantener): ", buffer, 100);
    if (strlen(buffer) > 0) reg.setNacionalidad(buffer);

    if (_archivoArtistas.Modificar(pos, reg)) {
        cout << "Artista modificado exitosamente." << endl;
    } else {
        cout << "Error al modificar." << endl;
    }
}

/**
 * Elimina un artista logicamente (marca como inactivo). Busca por nombre y confirma antes de eliminar.
 */
void ArtistaManager::Eliminar() {
    char nombre[100];
    InputHelper::pedirCadena("Ingrese nombre del artista a eliminar: ", nombre, 100); // Solicita nombre

    int id = _archivoArtistas.BuscarIDPorNombre(nombre); // Busca el ID
    if (id == -1) {
        cout << "Artista no encontrado." << endl;
        return;
    }

    int pos = _archivoArtistas.BuscarPosicion(id); // Busca posicion
    Artista reg = _archivoArtistas.Leer(pos); // Lee el registro
    reg.Mostrar(); // Muestra datos

    char op;
    cout << "Seguro desea eliminarlo? (s/n): "; // Confirma eliminacion
    cin >> op;
    cin.ignore(10000, '\n');

    if (op == 's' || op == 'S') { // Si confirma
        reg.setEstado(false); // Marca como inactivo
        if (_archivoArtistas.Modificar(pos, reg)) {
            cout << "Artista eliminado." << endl;
        } else {
            cout << "Error al eliminar." << endl;
        }
    }
}

/**
 * Lista todos los artistas activos del sistema.
 */
void ArtistaManager::Listar() {
    int total = _archivoArtistas.ObtenerCantidadRegistros();
    cout << "--- LISTADO DE ARTISTAS ---" << endl;
    for (int i = 0; i < total; i++) { // Itera sobre todos los artistas
        Artista a = _archivoArtistas.Leer(i);
        if (a.getEstado()) a.Mostrar(); // Muestra solo activos
    }
}
