/**
 * Este archivo implementa la clase GeneroManager. Maneja el CRUD básico para géneros musicales,
 * incluyendo agregar, modificar, eliminar y listar géneros del sistema.
 */

#include "../include/GeneroManager.h"
#include "../include/ArchivoGeneros.h"
#include "InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Agrega un nuevo género musical al sistema. Genera ID único y solicita el nombre.
 */
void GeneroManager::Agregar() {
    Genero g;
    ArchivoGeneros arch;
    int id = arch.GenerarIDNuevo(); // Genera ID único
    g.setIdGeneros(id);

    char buffer[50];
    InputHelper::pedirCadena("Nombre del genero: ", buffer, 50); // Solicita nombre
    g.setNombre(buffer);
    g.setEstado(true);

    if (g.Guardar()) { // Guarda el género
        cout << "Genero guardado." << endl;
    } else {
        cout << "Error al guardar el genero." << endl;
    }
}

/*
 * Modifica un género existente. Busca por nombre y permite cambiar el nombre.
 */
void GeneroManager::Modificar() {
    char nombre[50];
    InputHelper::pedirCadena("Ingrese nombre del genero a modificar: ", nombre, 50); // Solicita nombre a buscar

    Genero reg;
    int id = reg.BuscarIDPorNombre(nombre); // Busca el ID por nombre
    if (id == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    int pos = reg.BuscarPosicionPorID(id); // Busca la posición
    reg.Leer(pos); // Lee el registro
    cout << "--- GENERO ENCONTRADO ---" << endl;
    reg.Mostrar(); // Muestra datos actuales

    char buffer[50];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", buffer, 50); // Nuevo nombre
    if (strlen(buffer) > 0) reg.setNombre(buffer);

    if (reg.Modificar(pos)) { // Modifica el registro
        cout << "Genero modificado exitosamente." << endl;
    } else {
        cout << "Error al modificar." << endl;
    }
}

void GeneroManager::Eliminar() {
    char nombre[50];
    InputHelper::pedirCadena("Ingrese nombre del genero a eliminar: ", nombre, 50);

    Genero reg;
    int id = reg.BuscarIDPorNombre(nombre);
    if (id == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    int pos = reg.BuscarPosicionPorID(id);
    reg.Leer(pos);
    reg.Mostrar();

    char op;
    cout << "Seguro desea eliminarlo? (s/n): ";
    cin >> op;
    cin.ignore(10000, '\n');

    if (op == 's' || op == 'S') {
        reg.setEstado(false);
        if (reg.Modificar(pos)) cout << "Genero eliminado." << endl;
        else cout << "Error al eliminar." << endl;
    }
}

void GeneroManager::Listar() {
    Genero g;
    int total = g.ObtenerCantidadRegistros();
    cout << "--- LISTADO DE GENEROS ---" << endl;
    for (int i = 0; i < total; i++) {
        g.Leer(i);
        if (g.getEstado()) g.Mostrar();
    }
}
