/**
 * Este archivo contiene la implementación de la clase musicon, que actúa como el controlador principal
 * de la aplicación Musicon. Su función principal es manejar la interfaz de usuario a través de menús,
 * delegando toda la lógica de negocio a los managers especializados (CancionManager, PlaylistManager, etc.).
 * No contiene lógica de negocio directa, solo navegación de menús y llamadas a los managers.
 */

#include "musicon.h"
#include "InputHelper.h"
#include "ArchivoCanciones.h"
#include "ArchivoSuscriptores.h"
#include "CancionManager.h"
#include "SuscriptorManager.h"
#include "PlaylistManager.h"
#include "ArtistaManager.h"
#include "GeneroManager.h"
#include "ReporteManager.h"
#include "Canciones.h"
#include "Accesos.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cctype>

using namespace std;

/**
 * Constructor de la clase musicon.
 * Inicializa el ID del usuario logueado a 0 (ningún usuario) y el nombre a "Visitante".
 */
musicon::musicon() {
    _idUsuarioLogueado = 0;
    strcpy(_nombreUsuarioLogueado, "Visitante"); // Parametro por omision a "Visitante"
}

/*

 * Método principal que inicia el sistema.
 * Llama al menú de bienvenida para comenzar la interacción con el usuario.
 */
void musicon::iniciarSistema() {
    menuBienvenida();
}

/*
 * Muestra el menú de bienvenida donde el usuario puede elegir iniciar sesión, registrarse o salir.
 * Este es el punto de entrada para usuarios no autenticados.
 */
void musicon::menuBienvenida() {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla de la consola
        cout << "===========================================" << endl;
        cout << "           M  U  S  I  C  O  N             " << endl;
        cout << "===========================================" << endl;
        cout << "1. INICIAR SESION (Login)" << endl;
        cout << "2. REGISTRARSE (Sign Up)" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "0. SALIR DEL SISTEMA" << endl;
        cout << "===========================================" << endl;

        opcion = InputHelper::pedirEnteroRango("Ingrese opcion: ", 0, 2); // Pide una opción válida entre 0 y 2

        switch (opcion) {
            case 1: login(); break; // Llama al método de login
            case 2: {
                SuscriptorManager manager; // Crea una instancia del manager de suscriptores
                manager.Agregar(); // Llama al método para agregar un nuevo suscriptor (registro)
                break;
            }
            case 0: cout << "Nos vemos!" << endl; break; // Mensaje de despedida
        }
    } while (opcion != 0); // Repite hasta que el usuario elija salir
}

/*
 * Método para manejar el inicio de sesión de un usuario.
 * Pide el nombre de usuario, busca en el archivo de suscriptores y, si existe, establece el usuario como logueado.
 */
void musicon::login() {
    char nombreUser[50]; // Variable para almacenar el nombre del usuario ingresado
    system("cls"); // Limpia la pantalla
    cout << "--- LOGIN ---" << endl;
    InputHelper::pedirCadena("Usuario: ", nombreUser, 50); // Pide el nombre de usuario al usuario

    ArchivoSuscriptores arch; // Instancia del archivo de suscriptores para buscar
    int pos = arch.BuscarPosicionPorNombre(nombreUser); // Busca la posición del suscriptor por nombre
    if (pos != -1) { // Si se encontró el usuario
        Suscriptor sus = arch.Leer(pos); // Lee los datos del suscriptor
        _idUsuarioLogueado = sus.getIdSuscriptor(); // Establece el ID del usuario logueado
        strcpy(_nombreUsuarioLogueado, sus.getNombre()); // Establece el nombre del usuario logueado

        cout << "Bienvenido de nuevo, " << _nombreUsuarioLogueado << "!" << endl;
        InputHelper::pausa(); // Pausa para que el usuario lea el mensaje
        mostrarMenuPrincipal(); // Muestra el menú principal para usuarios logueados

        _idUsuarioLogueado = 0; // Resetea el ID al salir
        strcpy(_nombreUsuarioLogueado, "Visitante"); // Resetea el nombre
    } else {
        cout << "Usuario no encontrado. Registrate primero." << endl; // Mensaje de error
        InputHelper::pausa(); // Pausa
    }
}

/*
 * Muestra el menú principal para usuarios logueados.
 * Ofrece opciones para gestionar cargas, usuarios, informes y configuración.
 */
void musicon::mostrarMenuPrincipal() {
    int opcion = -1;
    do {
        system("cls"); // Limpia la pantalla
        cout << "MUSICON | User: " << _nombreUsuarioLogueado << " (ID: " << _idUsuarioLogueado << ")" << endl; // Muestra el usuario actual
        cout << "1. GESTION DE CARGAS (Canciones/Listas)" << endl;
        cout << "2. GESTION DE USUARIOS (Admin)" << endl;
        cout << "3. INFORMES Y ESTADISTICAS" << endl;
        cout << "4. CONFIGURACION (Artistas/Generos/Backup)" << endl;
        cout << "0. CERRAR SESION" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4); // Pide opción entre 0 y 4

        switch (opcion) {
            case 1: menuCargas(); break; // Menú de cargas
            case 2: menuSuscriptores(); break; // Menú de suscriptores
            case 3: mostrarMenuReportes(); break; // Menú de reportes
            case 4: menuConfiguracion(); break; // Menú de configuración
            case 0: cout << "Cerrando sesion..." << endl; break; // Mensaje de cierre
        }
    } while (opcion != 0); // Repite hasta cerrar sesión
}

void musicon::menuCargas() {
    int opcion;
    do {
        system("cls");
        cout << "--- CARGAS ---" << endl;
        cout << "1. Menu CANCIONES" << endl;
        cout << "2. Menu PLAYLISTS" << endl;
        cout << "3. Escuchar Cancion (Registrar Acceso)" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 3);

        switch (opcion) {
            case 1: menuCanciones(); break;
            case 2: menuPlaylists(); break;
            case 3: registrarAcceso(); break;
            case 0: break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

void musicon::menuCanciones() {
    CancionManager manager;
    int opcion;
    do {
        system("cls");
        cout << "--- GESTION DE CANCIONES ---" << endl;
        cout << "1. Listar Todas (Detallado)" << endl;
        cout << "2. Agregar Nueva Cancion" << endl;
        cout << "3. Eliminar Cancion" << endl;
        cout << "4. Modificar Cancion" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: manager.ListarDetallado(); break;
            case 2: manager.Agregar(); break;
            case 3: manager.Eliminar(); break;
            case 4: manager.Modificar(); break;
        }
    } while (opcion != 0);
}

void musicon::menuPlaylists() {
    PlaylistManager manager;
    int opcion;
    do {
        system("cls");
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
            case 2: manager.CrearPlaylist(_idUsuarioLogueado); break;
            case 3: manager.ModificarPlaylist(_idUsuarioLogueado); break;
            case 4: manager.EliminarPlaylist(_idUsuarioLogueado); break;
            case 5: manager.AgregarCancionAPlaylist(); break;
        }
        if (opcion != 0) InputHelper::pausa();
    } while (opcion != 0);
}

/*
 * Muestra el menú de gestión de suscriptores, delegando a SuscriptorManager.
 */
void musicon::menuSuscriptores() {
    SuscriptorManager manager; // Instancia del manager de suscriptores
    int opcion;
    do {
        system("cls"); // Limpia la pantalla
        cout << "--- GESTION DE SUSCRIPTORES ---" << endl;
        cout << "1. Registrar Nuevo Usuario" << endl;
        cout << "2. Modificar Usuario" << endl;
        cout << "3. Eliminar Usuario" << endl;
        cout << "4. Listar Todos" << endl;
        cout << "0. Volver" << endl;

        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4); // Pide opción entre 0 y 4

        switch(opcion) {
            case 1: manager.Agregar(); break; // Agregar suscriptor
            case 2: manager.Modificar(); break; // Modificar suscriptor
            case 3: manager.Eliminar(); break; // Eliminar suscriptor
            case 4: manager.Listar(); break; // Listar suscriptores
        }
        if (opcion != 0) InputHelper::pausa(); // Pausa si no es volver
    } while(opcion != 0); // Repite hasta volver
}

/*
 * Muestra el menú de configuración, donde se gestionan artistas, géneros, backups y exportaciones.
 */
void musicon::menuConfiguracion() {
    int op = -1;
    do {
        system("cls"); // Limpia la pantalla
        cout << "--- CONFIGURACION ---" << endl;
        cout << "1. Gestionar ARTISTAS" << endl;
        cout << "2. Gestionar GENEROS" << endl;
        cout << "3. Backup de Canciones (.bak)" << endl;
        cout << "4. Exportar Canciones a Excel (.csv)" << endl;
        cout << "5. IMPORTAR CANCIONES DESDE CSV" << endl;
        cout << "0. Volver" << endl;

        op = InputHelper::pedirEnteroRango("Opcion: ", 0, 5); // Pide opción entre 0 y 5

        switch(op) {
            case 1: menuArtistas(); break; // Menú de artistas
            case 2: menuGeneros(); break; // Menú de géneros
            case 3: {
                cout << "Haciendo backup..." << endl; // Mensaje de proceso
                CancionManager manager; // Instancia del manager
                manager.HacerBackup(); // Llama al método de backup
                break;
            }
            case 4: {
                CancionManager manager; // Instancia del manager
                manager.ExportarACSV(); // Llama al método de exportación
                break;
            }
            case 5: {
                CancionManager manager; // Instancia del manager
                manager.ImportarDesdeCSV(); // Llama al método de importación
                break;
            }
        }
    } while (op != 0); // Repite hasta volver
}

void musicon::menuArtistas() {
    ArtistaManager manager;
    int op;
    do {
        system("cls");
        cout << "--- ARTISTAS ---" << endl;
        cout << "1. Cargar Nuevo" << endl;
        cout << "2. Listar Todos" << endl;
        cout << "3. Modificar Artista" << endl;
        cout << "4. Eliminar Artista" << endl;
        cout << "0. Volver" << endl;

        op = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch(op) {
            case 1: manager.Agregar(); break;
            case 2: manager.Listar(); break;
            case 3: manager.Modificar(); break;
            case 4: manager.Eliminar(); break;
        }
        if(op!=0) InputHelper::pausa();
    } while(op!=0);
}

void musicon::menuGeneros() {
    GeneroManager manager;
    int op;
    do {
        system("cls");
        cout << "--- GENEROS ---" << endl;
        cout << "1. Cargar Nuevo" << endl;
        cout << "2. Listar Todos" << endl;
        cout << "3. Modificar Genero" << endl;
        cout << "4. Eliminar Genero" << endl;
        cout << "0. Volver" << endl;

        op = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);

        switch(op) {
            case 1: manager.Agregar(); break;
            case 2: manager.Listar(); break;
            case 3: manager.Modificar(); break;
            case 4: manager.Eliminar(); break;
        }
        if(op!=0) InputHelper::pausa();
    } while(op!=0);
}

void musicon::mostrarMenuReportes() {
    ReporteManager manager;
    manager.MostrarMenuReportes();
}

void musicon::registrarAcceso() {
    char nomC[100];
    InputHelper::pedirCadena("Cancion a escuchar: ", nomC, 100);

    ArchivoCanciones arch;
    int total = arch.ObtenerCantidadRegistros();
    int idC = -1;
    for (int i = 0; i < total; i++) {
        Canciones c = arch.Leer(i);
        if (InputHelper::sonIgualesSinMayusculas(c.getNombre(), nomC) && c.getEstado()) {
            idC = c.getIdCancion();
            break;
        }
    }

    if (idC == -1) {
        cout << "No existe." << endl;
        return;
    }

    Accesos a;
    a.setIdSuscriptor(_idUsuarioLogueado);
    a.setIdCancion(idC);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    a.setFechaHora(Fecha(ltm->tm_min, ltm->tm_hour, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year));
    a.Guardar();
    cout << "Reproduciendo..." << endl;
}
