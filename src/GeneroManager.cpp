/**
 * PATRÓN: Manager (capa de lógica de negocio)
 * Esta clase orquesta el CRUD de géneros musicales.
 * No accede directamente al archivo — delega en _archivoGeneros (Repository).
 *
 * Los géneros se usan como categoría de las canciones.
 * Al eliminar un género, solo se lo marca como inactivo (eliminación lógica).
 * Las canciones que tenían ese género conservan su idGenero — no se rompen.
 */

#include "../include/GeneroManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Da de alta un nuevo género musical.
 * Genera un ID automático, pide el nombre al usuario y guarda con estado=true.
 */
void GeneroManager::Agregar() {
    Genero g;

    // Genera el siguiente ID disponible
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

/**
 * Modifica el nombre de un género existente.
 * Busca por nombre actual (case-insensitive), muestra los datos actuales
 * y permite ingresar un nuevo nombre (Enter para no cambiar).
 */
void GeneroManager::Modificar() {
    char nombre[50];
    InputHelper::pedirCadena("Ingrese nombre del genero a modificar: ", nombre, 50);

    // Busca el ID por nombre para luego obtener su posición en el archivo
    int id = _archivoGeneros.BuscarIDPorNombre(nombre);
    if (id == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    // Con el ID, busca la posición exacta del registro en el archivo
    int pos = _archivoGeneros.BuscarPosicion(id);
    Genero reg = _archivoGeneros.Leer(pos);

    cout << "--- GENERO ENCONTRADO ---" << endl;
    reg.Mostrar();

    char buffer[50];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", buffer, 50);

    // Solo actualiza si el usuario ingresó algo
    if (strlen(buffer) > 0) reg.setNombre(buffer);

    if (_archivoGeneros.Modificar(pos, reg)) {
        cout << "Genero modificado exitosamente." << endl;
    } else {
        cout << "Error al modificar." << endl;
    }
}

/**
 * Da de baja lógicamente un género (estado=false).
 * Busca por nombre, muestra los datos y pide confirmación.
 * No borra del archivo — solo cambia su estado a inactivo.
 */
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
        // Eliminación lógica: marcamos inactivo y sobrescribimos el registro
        reg.setEstado(false);
        if (_archivoGeneros.Modificar(pos, reg)) cout << "Genero eliminado." << endl;
        else cout << "Error al eliminar." << endl;
    }
}

/**
 * Lista todos los géneros activos (estado=true).
 * Recorre todos los registros y muestra solo los que están activos.
 */
void GeneroManager::Listar() {
    int total = _archivoGeneros.ObtenerCantidadRegistros();
    cout << "--- LISTADO DE GENEROS ---" << endl;
    for (int i = 0; i < total; i++) {
        Genero g = _archivoGeneros.Leer(i);
        if (g.getEstado()) g.Mostrar(); // Solo muestra activos
    }
}
