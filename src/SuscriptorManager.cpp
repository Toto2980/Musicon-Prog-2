/**
 * PATRÓN: Manager (capa de lógica de negocio)
 * Esta clase orquesta el CRUD de suscriptores (usuarios del sistema).
 * No accede directamente al archivo — delega en _archivoSuscriptores (Repository).
 *
 * RESPONSABILIDADES:
 *   - Agregar: verifica unicidad del nombre antes de crear.
 *   - Modificar: solo permite cambiar el email (el nombre de usuario es inmutable).
 *   - Eliminar: hace eliminación LÓGICA (estado=false), nunca borra del archivo.
 *   - Listar: ofrece tres vistas: activos, dados de baja, o todos.
 */

#include "../include/SuscriptorManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Da de alta a un nuevo suscriptor.
 * Primero pide el nombre de usuario y verifica que no esté tomado (unicidad).
 * Si el nombre ya existe, lo rechaza y vuelve a pedir uno nuevo.
 * Luego genera un ID automático y llama a nuevo.Cargar() para el resto de los datos.
 */
void SuscriptorManager::Agregar() {
    char nombreUser[50];

    cout << "--- ALTA DE USUARIO ---" << endl;

    Suscriptor nuevo;

    // Bucle hasta conseguir un nombre de usuario único
    while (true) {

        InputHelper::pedirCadena(
                                 "Usuario deseado: ",
                                 nombreUser,
                                 50
                                 );

        // Limpia espacios al inicio/fin antes de buscar
        std::string nombreBuscado =
            InputHelper::trim(nombreUser);

        strncpy(
                nombreUser,
                nombreBuscado.c_str(),
                sizeof(nombreUser) - 1
                );

        nombreUser[sizeof(nombreUser) - 1] = '\0';

        if (_archivoSuscriptores.BuscarPosicionPorNombre(nombreUser) != -1) {
            // El nombre ya existe: rechazamos y pedimos otro
            cout << "[!] Ese nombre ya existe." << endl;

        }
        else {
            break; // Nombre libre: salimos del bucle
        }
    }

    // Genera ID único y asigna el nombre ya validado
    int idAuto =
           _archivoSuscriptores.GenerarIDNuevo();

    nuevo.setIdSuscriptor(idAuto);

    nuevo.setNombre(nombreUser);

    // Pide el resto de los datos al usuario (apellido, DNI, email, plan, fecha de nacimiento)
    nuevo.Cargar();

    nuevo.setEstado(true);

    if (_archivoSuscriptores.Guardar(nuevo)) {

        cout << endl;
        cout << "Usuario creado (ID "
            << idAuto
            << ")."
            << endl;

    }
    else {

        cout << "Error al guardar." << endl;

    }
}

/**
 * Modifica los datos de un suscriptor existente.
 * Busca por nombre de usuario. Si no existe, informa y termina.
 * Por ahora solo permite cambiar el email (dejar vacío para no modificar).
 */
void SuscriptorManager::Modificar() {

    char nombreUser[50];

    InputHelper::pedirCadena(
                             "Usuario a modificar: ",
                             nombreUser,
                             50
                             );

    int pos =
        _archivoSuscriptores.BuscarPosicionPorNombre(
                                                     nombreUser
                                                     );

    if(pos == -1) {

        cout
            << "No existe ese usuario."
            << endl;

        return;
    }

    // Lee el registro actual y lo muestra antes de modificar
    Suscriptor s =
       _archivoSuscriptores.Leer(pos);

    s.Mostrar();

    cout << "--- Modificando ---" << endl;

    char email[100];

    InputHelper::pedirCadena(
                             "Nuevo Email (Enter para no cambiar): ",
                             email,
                             100
                             );

    // Solo cambia si el usuario escribió algo
    if(strlen(email) > 0)
        s.setEmail(email);

    if(_archivoSuscriptores.Modificar(pos, s))
        cout << "Usuario actualizado." << endl;
    else
        cout << "Error al actualizar." << endl;
}

/**
 * Da de baja lógicamente a un suscriptor (estado=false).
 * Busca por nombre, muestra los datos y pide confirmación antes de proceder.
 * No borra el registro del archivo — solo cambia su estado a inactivo.
 */
void SuscriptorManager::Eliminar() {

    char nombreUser[50];

    InputHelper::pedirCadena(
                             "Usuario a dar de baja: ",
                             nombreUser,
                             50
                             );

    int pos =
        _archivoSuscriptores.BuscarPosicionPorNombre(
                                                     nombreUser
                                                     );

    if(pos == -1) {

        cout
            << "No existe ese usuario."
            << endl;

        return;
    }

    Suscriptor s =
       _archivoSuscriptores.Leer(pos);

    cout
        << "Confirma dar de baja a "
        << s.getNombre()
        << "? (s/n): ";

    char op;

    cin >> op;
    cin.ignore(10000, '\n');

    if(op == 's' || op == 'S') {

        // Eliminación lógica: marcamos estado=false y sobrescribimos el registro
        s.setEstado(false);

        if(
           _archivoSuscriptores.Modificar(
                                          pos,
                                          s
                                          )
           ) {

            cout
                << "Usuario dado de baja correctamente."
                << endl;

        }
        else {

               cout
                   << "Error al dar de baja el usuario."
                   << endl;

           }
    }
}

/**
 * Listar: alias de ListarActivos para la interfaz del menú principal.
 */
void SuscriptorManager::Listar() {

    ListarActivos();

}

/**
 * Muestra todos los suscriptores con estado=true (activos).
 * Lee todos los registros en memoria y filtra por estado.
 * El arreglo se libera al final con delete[] para evitar fuga de memoria.
 */
void SuscriptorManager::ListarActivos() {

    int total =
        _archivoSuscriptores.ObtenerCantidadRegistros();

    cout << "--- USUARIOS ACTIVOS ---" << endl;

    if(total == 0) {

        cout
            << "No hay usuarios."
            << endl;

        return;
    }

    // Lee todos los registros de una sola vez (más eficiente que un fread por registro)
    Suscriptor *lista =
       _archivoSuscriptores.LeerTodos(total);

    if(lista == nullptr) {

        cout
            << "Error al leer usuarios."
            << endl;

        return;
    }

    for(int i = 0; i < total; i++) {

        if(lista[i].getEstado()) {

            lista[i].Mostrar();

        }
    }

    delete[] lista; // Libera la memoria reservada en LeerTodos
}

/**
 * Muestra todos los suscriptores con estado=false (dados de baja).
 * Mismo mecanismo que ListarActivos pero con la condición invertida.
 */
void SuscriptorManager::ListarInactivos() {

    int total =
        _archivoSuscriptores.ObtenerCantidadRegistros();

    cout << "--- USUARIOS DADOS DE BAJA ---" << endl;

    if(total == 0) {

        cout
            << "No hay usuarios."
            << endl;

        return;
    }

    Suscriptor *lista =
       _archivoSuscriptores.LeerTodos(total);

    if(lista == nullptr) {

        cout
            << "Error al leer usuarios."
            << endl;

        return;
    }

    for(int i = 0; i < total; i++) {

        if(!lista[i].getEstado()) { // Solo los inactivos

            lista[i].Mostrar();

        }
    }

    delete[] lista;
}

/**
 * Muestra todos los suscriptores sin importar su estado (activos e inactivos).
 * Útil para el admin, que necesita ver el historial completo.
 */
void SuscriptorManager::ListarTodos() {

    int total =
        _archivoSuscriptores.ObtenerCantidadRegistros();

    cout << "--- TODOS LOS USUARIOS ---" << endl;

    if(total == 0) {

        cout
            << "No hay usuarios."
            << endl;

        return;
    }

    Suscriptor *lista =
       _archivoSuscriptores.LeerTodos(total);

    if(lista == nullptr) {

        cout
            << "Error al leer usuarios."
            << endl;

        return;
    }

    for(int i = 0; i < total; i++) {

        lista[i].Mostrar(); // Muestra todos sin filtrar por estado

    }

    delete[] lista;
}
