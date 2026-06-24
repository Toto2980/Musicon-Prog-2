/**
* Este archivo contiene la implementaci�n de la clase musicon, que act�a como el controlador principal
* de la aplicaci�n Musicon. Su funci�n principal es manejar la interfaz de usuario a trav�s de men�s,
* delegando toda la l�gica de negocio a los managers especializados (CancionManager, PlaylistManager, etc.).
* No contiene l�gica de negocio directa, solo navegaci�n de men�s y llamadas a los managers.
*/

#include "../include/musicon.h"
#include "../include/InputHelper.h"
#include "../include/ArchivoCanciones.h"
#include "../include/ArchivoSuscriptores.h"
#include "../include/CancionManager.h"
#include "../include/SuscriptorManager.h"
#include "../include/PlaylistManager.h"
#include "../include/ArtistaManager.h"
#include "../include/GeneroManager.h"
#include "../include/ReporteManager.h"
#include "../include/Canciones.h"
#include "../include/Accesos.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cctype>

using namespace std;

/**
* Constructor de la clase musicon.
* Inicializa el ID del usuario logueado a 0 (ning�n usuario) y el nombre a "Visitante".
*/
musicon::musicon() {
	_idUsuarioLogueado = 0;
	strcpy(_nombreUsuarioLogueado, "Visitante"); // Parametro por omision a "Visitante"
}

/*

* M�todo principal que inicia el sistema.
* Llama al men� de bienvenida para comenzar la interacci�n con el usuario.
*/
void musicon::iniciarSistema() {
	menuBienvenida();
}

/*
* Muestra el men� de bienvenida donde el usuario puede elegir iniciar sesi�n, registrarse o salir.
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
		
		opcion = InputHelper::pedirEnteroRango("Ingrese opcion: ", 0, 2); // Pide una opci�n v�lida entre 0 y 2
		
		switch (opcion) {
		case 1: login(); break; // Llama al m�todo de login
		case 2: {
			SuscriptorManager manager; // Crea una instancia del manager de suscriptores
			manager.Agregar(); // Llama al m�todo para agregar un nuevo suscriptor (registro)
			break;
		}
		case 0: cout << "Nos vemos!" << endl; break; // Mensaje de despedida
		}
	} while (opcion != 0); // Repite hasta que el usuario elija salir
}

/*
* M�todo para manejar el inicio de sesi�n de un usuario.
* Pide el nombre de usuario, busca en el archivo de suscriptores y, si existe, establece el usuario como logueado.
*/
void musicon::login() {
	char nombreUser[50];
	
	system("cls");
	cout << "--- LOGIN ---" << endl;
	
	InputHelper::pedirCadena(
							 "Usuario: ",
							 nombreUser,
							 50
							 );
	
	std::string nombreBuscado =
		InputHelper::trim(nombreUser);
	
	// ==========================
	// ADMIN FIJO
	// ==========================
	
	if(nombreBuscado == "admin"){
		
		_idUsuarioLogueado = -1;
		
		strcpy(
			   _nombreUsuarioLogueado,
			   "ADMIN"
			   );
		
		cout << endl;
		cout << "Bienvenido Administrador."
			<< endl;
		
		InputHelper::pausa();
		
		mostrarMenuPrincipal();
		
		_idUsuarioLogueado = 0;
		
		strcpy(
			   _nombreUsuarioLogueado,
			   "Visitante"
			   );
		
		return;
	}
	
	ArchivoSuscriptores arch;
	
	int pos =
		arch.BuscarPosicionPorNombre(
									 nombreBuscado.c_str()
									 );
	
	if (pos != -1) {
		
		Suscriptor sus =
			arch.Leer(pos);
		
		_idUsuarioLogueado =
			sus.getIdSuscriptor();
		
		strcpy(
			   _nombreUsuarioLogueado,
			   sus.getNombre()
			   );
		
		cout
			<< "Bienvenido de nuevo, "
			<< _nombreUsuarioLogueado
			<< "!"
			<< endl;
		
		InputHelper::pausa();
		
		mostrarMenuPrincipal();
		
		_idUsuarioLogueado = 0;
		
		strcpy(
			   _nombreUsuarioLogueado,
			   "Visitante"
			   );
	}
	else {
		
		cout
			<< "Usuario no encontrado. Registrate primero."
			<< endl;
		
		InputHelper::pausa();
	}
}

/*
* Muestra el men� principal para usuarios logueados.
* Ofrece opciones para gestionar cargas, usuarios, informes y configuraci�n.
*/
void musicon::mostrarMenuPrincipal() {
	
	// ==========================
	// ADMIN
	// ==========================
	
	if(_idUsuarioLogueado == -1){
		
		int opcion;
		
		do{
			
			system("cls");
			
			cout
				<< "MUSICON | ADMIN"
				<< endl;
			
			cout
				<< "1. GESTION DE CARGAS"
				<< endl;
			
			cout
				<< "2. GESTION DE USUARIOS"
				<< endl;
			
			cout
				<< "3. INFORMES"
				<< endl;
			
			cout
				<< "4. CONFIGURACION"
				<< endl;
			
			cout
				<< "0. CERRAR SESION"
				<< endl;
			
			opcion =
				InputHelper::pedirEnteroRango(
											  "Opcion: ",
											  0,
											  4
											  );
			
			switch(opcion){
				
			case 1:
				menuCargas();
				break;
				
			case 2:
				menuSuscriptores();
				break;
				
			case 3:
				mostrarMenuReportes();
				break;
				
			case 4:
				menuConfiguracion();
				break;
			}
			
		}while(opcion != 0);
		
		return;
	}
	
	// ==========================
	// USUARIO GRATIS / PAGO
	// ==========================
	
	int opcion;
	
	do{
		
		system("cls");
		
		cout
			<< "MUSICON | "
			<< _nombreUsuarioLogueado
			<< endl;
		
		cout
			<< "1. CANCIONES"
			<< endl;
		
		cout
			<< "2. PLAYLISTS"
			<< endl;
		
		cout
			<< "3. ESCUCHAR CANCION"
			<< endl;
		
		cout
			<< "0. CERRAR SESION"
			<< endl;
		
		opcion =
			InputHelper::pedirEnteroRango(
										  "Opcion: ",
										  0,
										  3
										  );
		
		switch(opcion){
			
		case 1:
			menuCanciones();
			break;
			
		case 2:
			menuPlaylists();
			break;
			
		case 3:
			registrarAcceso();
			break;
		}
		
	}while(opcion != 0);
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
* Muestra el men� de gesti�n de suscriptores, delegando a SuscriptorManager.
*/
void musicon::menuSuscriptores() {
	
	SuscriptorManager manager;
	
	int opcion;
	
	do {
		
		system("cls");
		
		cout << "--- GESTION DE SUSCRIPTORES ---" << endl;
		
		cout << "1. Registrar Nuevo Usuario" << endl;
		cout << "2. Modificar Usuario" << endl;
		cout << "3. Dar de Baja Usuario" << endl;
		cout << "4. Listar Usuarios Activos" << endl;
		cout << "5. Listar Usuarios Inactivos" << endl;
		cout << "6. Listar Todos" << endl;
		cout << "0. Volver" << endl;
		
		opcion =
			InputHelper::pedirEnteroRango(
										  "Opcion: ",
										  0,
										  6
										  );
		
		switch(opcion) {
			
		case 1:
			manager.Agregar();
			break;
			
		case 2:
			manager.Modificar();
			break;
			
		case 3:
			manager.Eliminar();
			break;
			
		case 4:
			manager.ListarActivos();
			break;
			
		case 5:
			manager.ListarInactivos();
			break;
			
		case 6:
			manager.ListarTodos();
			break;
		}
		
		if(opcion != 0)
			   InputHelper::pausa();
		
	} while(opcion != 0);
}

/*
* Muestra el men� de configuraci�n, donde se gestionan artistas, g�neros, backups y exportaciones.
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
		
		op = InputHelper::pedirEnteroRango("Opcion: ", 0, 5); // Pide opci�n entre 0 y 5
		
		switch(op) {
		case 1: menuArtistas(); break; // Men� de artistas
		case 2: menuGeneros(); break; // Men� de g�neros
		case 3: {
			cout << "Haciendo backup..." << endl; // Mensaje de proceso
			CancionManager manager; // Instancia del manager
			manager.HacerBackup(); // Llama al m�todo de backup
			break;
		}
		case 4: {
			CancionManager manager; // Instancia del manager
			manager.ExportarACSV(); // Llama al m�todo de exportaci�n
			break;
		}
		case 5: {
			CancionManager manager; // Instancia del manager
			manager.ImportarDesdeCSV(); // Llama al m�todo de importaci�n
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

	// Trim del nombre ingresado para tolerar espacios accidentales
	std::string nomBuscado = InputHelper::trim(nomC);

	ArchivoCanciones arch;
	int total = arch.ObtenerCantidadRegistros();
	int idC = -1;
	for (int i = 0; i < total; i++) {
		Canciones c = arch.Leer(i);
		std::string nomGuardado = InputHelper::trim(c.getNombre());
		if (InputHelper::sonIgualesSinMayusculas(nomGuardado.c_str(), nomBuscado.c_str()) && c.getEstado()) {
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
