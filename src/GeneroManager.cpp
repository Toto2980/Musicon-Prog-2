/**
 * Este archivo implementa la clase GeneroManager. Maneja el CRUD básico para géneros musicales,
 * incluyendo agregar, modificar, eliminar y listar géneros del sistema.
 */

#include "../include/GeneroManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

void GeneroManager::Agregar() {
    Genero g;
    int id = _archivoGeneros.GenerarIDNuevo();
    g.setIdGeneros(id);

    char buffer[50];
    InputHelper::pedirCadena("Nombre del genero: ", buffer, 50);
    g.setNombre(buffer);
    g.setEstado(true);

    if (_archivoGeneros.Guardar(g)) {
        cout << "Genero guardado." << endl;
    } else {
        cout << "Error al guardar el genero." << endl;
    }
}

void GeneroManager::Modificar() {
    char nombre[50];
    InputHelper::pedirCadena("Ingrese nombre del genero a modificar: ", nombre, 50);

    int id = _archivoGeneros.BuscarIDPorNombre(nombre);
    if (id == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    int pos = _archivoGeneros.BuscarPosicion(id);
    Genero reg = _archivoGeneros.Leer(pos);
    cout << "--- GENERO ENCONTRADO ---" << endl;
    reg.Mostrar();

    char buffer[50];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", buffer, 50);
    if (strlen(buffer) > 0) reg.setNombre(buffer);

    if (_archivoGeneros.Modificar(pos, reg)) {
        cout << "Genero modificado exitosamente." << endl;
    } else {
        cout << "Error al modificar." << endl;
    }
}

void GeneroManager::Eliminar() {
    char nombre[50];
    InputHelper::pedirCadena("Ingrese nombre del genero a eliminar: ", nombre, 50);

    int id = _archivoGeneros.BuscarIDPorNombre(nombre);
    if (id == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    int pos = _archivoGeneros.BuscarPosicion(id);
    Genero reg = _archivoGeneros.Leer(pos);
    reg.Mostrar();

    char op;
    cout << "Seguro desea eliminarlo? (s/n): ";
    cin >> op;
    cin.ignore(10000, '\n');

    if (op == 's' || op == 'S') {
        reg.setEstado(false);
        if (_archivoGeneros.Modificar(pos, reg)) cout << "Genero eliminado." << endl;
        else cout << "Error al eliminar." << endl;
    }
}

void GeneroManager::Listar() {
    int total = _archivoGeneros.ObtenerCantidadRegistros();
    cout << "--- LISTADO DE GENEROS ---" << endl;
    for (int i = 0; i < total; i++) {
        Genero g = _archivoGeneros.Leer(i);
        if (g.getEstado()) g.Mostrar();
    }
}
