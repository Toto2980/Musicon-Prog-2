/*
 * musicon.cpp
 * Implementacion del controlador de menus. No contiene logica de negocio:
 * solo navegacion y delegacion a los managers.
 */

#include "../include/musicon.h"
#include "../include/Constantes.h"
#include "../include/Consola.h"
#include "../include/InputHelper.h"
#include "../include/Texto.h"
#include "../include/ArchivoSuscriptores.h"
#include "../include/Suscriptor.h"
#include "../include/CancionManager.h"
#include "../include/SuscriptorManager.h"
#include "../include/PlaylistManager.h"
#include "../include/ArtistaManager.h"
#include "../include/GeneroManager.h"
#include "../include/ReporteManager.h"

#include <iostream>
#include <cstring>

using namespace std;

musicon::musicon() {
    _idUsuarioLogueado = cfg::ID_VISITANTE;
    strcpy(_nombreUsuarioLogueado, "Visitante");
}

void musicon::iniciarSistema() {
    Consola::iniciar();
    menuBienvenida();
}

/* ============================ SESION ============================ */

void musicon::menuBienvenida() {
    int opcion;
    do {
        Consola::limpiar();
        cout << "===========================================" << endl;
        cout << "           M  U  S  I  C  O  N             " << endl;
        cout << "===========================================" << endl;
        cout << "1. INICIAR SESION (Login)" << endl;
        cout << "2. REGISTRARSE (Sign Up)" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "0. SALIR DEL SISTEMA" << endl;
        cout << "===========================================" << endl;

        opcion = InputHelper::pedirEnteroRango("Ingrese opcion: ", 0, 2);

        switch (opcion) {
            case 1:
                login();
                break;
            case 2: {
                SuscriptorManager manager;
                manager.Agregar();
                break;
            }
            case 0:
                cout << "Nos vemos!" << endl;
                break;
        }
    } while (opcion != 0);
}

void musicon::login() {
    char nombreUser[50];

    Consola::limpiar();
    cout << "--- LOGIN ---" << endl;

    InputHelper::pedirCadena("Usuario: ", nombreUser, 50);
    string nombreBuscado = Texto::trim(nombreUser);

    // Administrador con credencial fija.
    if (nombreBuscado == "admin") {
        _idUsuarioLogueado = cfg::ID_ADMIN;
        strcpy(_nombreUsuarioLogueado, "ADMIN");

        cout << "\nBienvenido Administrador." << endl;
        InputHelper::pausa();

        menuPrincipalAdmin();

        _idUsuarioLogueado = cfg::ID_VISITANTE;
        strcpy(_nombreUsuarioLogueado, "Visitante");
        return;
    }

    // Usuario normal: se busca en el archivo de suscriptores.
    ArchivoSuscriptores arch;
    int pos = arch.BuscarPosicionPorNombre(nombreBuscado.c_str());

    if (pos != -1) {
        Suscriptor sus = arch.Leer(pos);
        _idUsuarioLogueado = sus.getIdSuscriptor();
        strcpy(_nombreUsuarioLogueado, sus.getNombre());

        cout << "Bienvenido de nuevo, " << _nombreUsuarioLogueado << "!" << endl;
        InputHelper::pausa();

        menuPrincipalUsuario();

        _idUsuarioLogueado = cfg::ID_VISITANTE;
        strcpy(_nombreUsuarioLogueado, "Visitante");
    } else {
        cout << "Usuario no encontrado. Registrate primero." << endl;
        InputHelper::pausa();
    }
}

/* ====================== MENUS PRINCIPALES ====================== */

void musicon::menuPrincipalAdmin() {
    int opcion;
    do {
        Consola::limpiar();
        cout << "MUSICON | ADMIN" << endl;
        cout << "1. GESTION DE CARGAS" << endl;
        cout << "2. GESTION DE USUARIOS" << endl;
        cout << "3. INFORMES" << endl;
        cout << "4. CONFIGURACION" << endl;
        cout << "0. CERRAR SESION" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: menuCargas();        break;
            case 2: menuSuscriptores();  break;
            case 3: menuReportes();      break;
            case 4: menuConfiguracion(); break;
        }
    } while (opcion != 0);
}

void musicon::menuPrincipalUsuario() {
    int opcion;
    do {
        Consola::limpiar();
        cout << "MUSICON | " << _nombreUsuarioLogueado << endl;
        cout << "1. CANCIONES" << endl;
        cout << "2. PLAYLISTS" << endl;
        cout << "3. ESCUCHAR CANCION" << endl;
        cout << "0. CERRAR SESION" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 3);

        switch (opcion) {
            case 1: menuCanciones();   break;
            case 2: menuPlaylists();   break;
            case 3: registrarAcceso(); break;
        }
    } while (opcion != 0);
}

/* ========================== SUBMENUS ========================== */

void musicon::menuCargas() {
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- CARGAS ---" << endl;
        cout << "1. Menu CANCIONES" << endl;
        cout << "2. Menu PLAYLISTS" << endl;
        cout << "3. Escuchar Cancion (Registrar Acceso)" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 3);

        switch (opcion) {
            case 1: menuCanciones();   break;
            case 2: menuPlaylists();   break;
            case 3: registrarAcceso(); break;
        }
    } while (opcion != 0);
}

void musicon::menuCanciones() {
    CancionManager manager;
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- GESTION DE CANCIONES ---" << endl;
        cout << "1. Listar Todas (Detallado)" << endl;
        cout << "2. Agregar Nueva Cancion" << endl;
        cout << "3. Eliminar Cancion" << endl;
        cout << "4. Modificar Cancion" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: manager.ListarDetallado(); break;
            case 2: manager.Agregar();         break;
            case 3: manager.Eliminar();        break;
            case 4: manager.Modificar();       break;
        }
    } while (opcion != 0);
}

void musicon::menuPlaylists() {
    PlaylistManager manager;
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- GESTION DE PLAYLISTS ---" << endl;
        cout << "1. MIS PLAYLISTS" << endl;
        cout << "2. Crear Playlist" << endl;
        cout << "3. Modificar Playlist" << endl;
        cout << "4. Eliminar Playlist" << endl;
        cout << "5. Agregar Cancion a Playlist" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 5);

        switch (opcion) {
            case 1: manager.MostrarMisPlaylists(_idUsuarioLogueado); break;
            case 2: manager.CrearPlaylist(_idUsuarioLogueado);      break;
            case 3: manager.ModificarPlaylist(_idUsuarioLogueado);  break;
            case 4: manager.EliminarPlaylist(_idUsuarioLogueado);   break;
            case 5: manager.AgregarCancionAPlaylist();              break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

void musicon::menuSuscriptores() {
    SuscriptorManager manager;
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- GESTION DE SUSCRIPTORES ---" << endl;
        cout << "1. Registrar Nuevo Usuario" << endl;
        cout << "2. Modificar Usuario" << endl;
        cout << "3. Dar de Baja Usuario" << endl;
        cout << "4. Listar Usuarios Activos" << endl;
        cout << "5. Listar Usuarios Inactivos" << endl;
        cout << "6. Listar Todos" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 6);

        switch (opcion) {
            case 1: manager.Agregar();          break;
            case 2: manager.Modificar();        break;
            case 3: manager.Eliminar();         break;
            case 4: manager.ListarActivos();    break;
            case 5: manager.ListarInactivos();  break;
            case 6: manager.ListarTodos();      break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

void musicon::menuConfiguracion() {
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- CONFIGURACION ---" << endl;
        cout << "1. Gestionar ARTISTAS" << endl;
        cout << "2. Gestionar GENEROS" << endl;
        cout << "3. Backup de Canciones (.bak)" << endl;
        cout << "4. Exportar Canciones a Excel (.csv)" << endl;
        cout << "5. IMPORTAR CANCIONES DESDE CSV" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 5);

        switch (opcion) {
            case 1: menuArtistas(); break;
            case 2: menuGeneros();  break;
            case 3: {
                CancionManager manager;
                manager.HacerBackup();
                break;
            }
            case 4: {
                CancionManager manager;
                manager.ExportarACSV();
                break;
            }
            case 5: {
                CancionManager manager;
                manager.ImportarDesdeCSV();
                break;
            }
        }
    } while (opcion != 0);
}

void musicon::menuArtistas() {
    ArtistaManager manager;
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- ARTISTAS ---" << endl;
        cout << "1. Cargar Nuevo" << endl;
        cout << "2. Listar Todos" << endl;
        cout << "3. Modificar Artista" << endl;
        cout << "4. Eliminar Artista" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: manager.Agregar();   break;
            case 2: manager.Listar();    break;
            case 3: manager.Modificar(); break;
            case 4: manager.Eliminar();  break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

void musicon::menuGeneros() {
    GeneroManager manager;
    int opcion;
    do {
        Consola::limpiar();
        cout << "--- GENEROS ---" << endl;
        cout << "1. Cargar Nuevo" << endl;
        cout << "2. Listar Todos" << endl;
        cout << "3. Modificar Genero" << endl;
        cout << "4. Eliminar Genero" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: manager.Agregar();   break;
            case 2: manager.Listar();    break;
            case 3: manager.Modificar(); break;
            case 4: manager.Eliminar();  break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

void musicon::menuReportes() {
    ReporteManager manager;
    manager.MostrarMenuReportes();
}

/* ========================== ACCIONES ========================== */

void musicon::registrarAcceso() {
    // La logica vive en CancionManager para no duplicarla.
    CancionManager manager;
    manager.RegistrarAcceso(_idUsuarioLogueado);
    InputHelper::pausa();
}
