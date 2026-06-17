/**
* Este archivo implementa la clase SuscriptorManager. Maneja el CRUD básico para suscriptores (usuarios),
* incluyendo agregar, modificar, dar de baja y listar suscriptores del sistema.
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
		
		InputHelper::pedirCadena(
								 "Usuario deseado: ",
								 nombreUser,
								 50
								 );
		
		std::string nombreBuscado =
			InputHelper::trim(nombreUser);
		
		strncpy(
				nombreUser,
				nombreBuscado.c_str(),
				sizeof(nombreUser) - 1
				);
		
		nombreUser[sizeof(nombreUser) - 1] = '\0';
		
		if (_archivoSuscriptores.BuscarPosicionPorNombre(nombreUser) != -1) {
			
			cout << "[!] Ese nombre ya existe." << endl;
			
		}
		else {
			
			break;
			
		}
	}
	
	int idAuto =
		   _archivoSuscriptores.GenerarIDNuevo();
	
	nuevo.setIdSuscriptor(idAuto);
	
	nuevo.setNombre(nombreUser);
	
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
	
	if(strlen(email) > 0)
		s.setEmail(email);
	
	if(_archivoSuscriptores.Modificar(pos, s))
		cout << "Usuario actualizado." << endl;
	else
		cout << "Error al actualizar." << endl;
}

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

void SuscriptorManager::Listar() {
	
	ListarActivos();
	
}

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
	
	delete[] lista;
}

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
		
		if(!lista[i].getEstado()) {
			
			lista[i].Mostrar();
			
		}
	}
	
	delete[] lista;
}

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
		
		lista[i].Mostrar();
		
	}
	
	delete[] lista;
}
