/**
 * Este archivo implementa la clase SuscriptorManager. Maneja el CRUD b\u00e1sico para suscriptores (usuarios),
 * incluyendo agregar, modificar, eliminar y listar suscriptores del sistema.
 */

#include "../include/SuscriptorManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

void SuscriptorManager::Agregar() {
    char nombreUser[50];

    cout << "--- ALTA DE USUARIO ---" << endl;
    Suscriptor nuevo;
    while (true) {
        InputHelper::pedirCadena("Usuario deseado: ", nombreUser, 50);
        std::string nombreBuscado = InputHelper::trim(nombreUser);
        strncpy(nombreUser, nombreBuscado.c_str(), sizeof(nombreUser) - 1);
        nombreUser[sizeof(nombreUser) - 1] = '\0';
        if (_archivoSuscriptores.BuscarPosicionPorNombre(nombreUser) != -1) {
            cout << "[!] Ese nombre ya existe." << endl;
        } else { break; }
    }
    int idAuto = _archivoSuscriptores.GenerarIDNuevo();
    nuevo.setIdSuscriptor(idAuto);
    nuevo.setNombre(nombreUser);
    nuevo.Cargar();
    nuevo.setEstado(true);

    if (_archivoSuscriptores.Guardar(nuevo)) cout << endl << "Usuario creado (ID " << idAuto << ")." << endl;
    else cout << "Error al guardar." << endl;
}

void SuscriptorManager::Modificar() {
    char nombreUser[50];
    InputHelper::pedirCadena("Usuario a modificar: ", nombreUser, 50);

    int pos = _archivoSuscriptores.BuscarPosicionPorNombre(nombreUser);
    if(pos == -1) {
        cout << "No existe ese usuario." << endl;
        return;
    }

    Suscriptor s = _archivoSuscriptores.Leer(pos);
    s.Mostrar();

    cout << "--- Modificando ---" << endl;
    char email[100];
    InputHelper::pedirCadena("Nuevo Email (Enter para no cambiar): ", email, 100);
    if(strlen(email) > 0) s.setEmail(email);

    if(_archivoSuscriptores.Modificar(pos, s)) cout << "Usuario actualizado." << endl;
    else cout << "Error al actualizar." << endl;
}

void SuscriptorManager::Eliminar() {
    char nombreUser[50];
    InputHelper::pedirCadena("Usuario a eliminar: ", nombreUser, 50);

    int pos = _archivoSuscriptores.BuscarPosicionPorNombre(nombreUser);
    if(pos == -1) {
        cout << "No existe." << endl;
        return;
    }

    Suscriptor s = _archivoSuscriptores.Leer(pos);
    cout << "Confirma eliminar a " << s.getNombre() << "? (s/n): ";
    char op;
    cin >> op;
    cin.ignore(10000, '\n');

    if(op == 's' || op == 'S') {
        s.setEstado(false);
        if(_archivoSuscriptores.Modificar(pos, s)) cout << "Usuario eliminado." << endl;
        else cout << "Error." << endl;
    }
}

void SuscriptorManager::Listar() {
    int total = _archivoSuscriptores.ObtenerCantidadRegistros();
    cout << "--- LISTADO DE USUARIOS ---" << endl;
    if (total == 0) {
        cout << "No hay usuarios para mostrar." << endl;
        return;
    }

    Suscriptor *lista = _archivoSuscriptores.LeerTodos(total);
    if (lista == nullptr) {
        cout << "Error al leer los registros." << endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        if (lista[i].getEstado()) {
            lista[i].Mostrar();
        }
    }

    delete [] lista;
}
