#include "../include/Suscriptor.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <cstring>

using namespace std;

Suscriptor::Suscriptor() {
	_nombre[0] = '\0';
	_estado = false;
	_idSuscriptor = 0;
	
	strcpy(_dni, "0");
	strcpy(_apellido, "S/N");
	strcpy(_email, "S/N");
	
	_tipoSuscriptor = 1;
}

Suscriptor::~Suscriptor() { }

void Suscriptor::setIdSuscriptor(int id) {
	_idSuscriptor = id;
}

void Suscriptor::setDni(const char* dni) {
	strncpy(_dni, dni, 14);
	_dni[14] = '\0';
}

void Suscriptor::setApellido(const char* apellido) {
	strncpy(_apellido, apellido, 49);
	_apellido[49] = '\0';
}

void Suscriptor::setEmail(const char* email) {
	strncpy(_email, email, 99);
	_email[99] = '\0';
}

void Suscriptor::setFechaNacimiento(Fecha fecha) {
	_fechaNacimiento = fecha;
}

void Suscriptor::setTipoSuscriptor(int tipo) {
	_tipoSuscriptor = tipo;
}

int Suscriptor::getIdSuscriptor() {
	return _idSuscriptor;
}

const char* Suscriptor::getDni() {
	return _dni;
}

const char* Suscriptor::getApellido() {
	return _apellido;
}

const char* Suscriptor::getEmail() {
	return _email;
}

Fecha Suscriptor::getFechaNacimiento() {
	return _fechaNacimiento;
}

int Suscriptor::getTipoSuscriptor() {
	return _tipoSuscriptor;
}

void Suscriptor::Cargar() {
	char buffer[100];
	
	InputHelper::pedirCadena("Apellido: ", buffer, 50);
	setApellido(buffer);
	
	InputHelper::pedirCadena("DNI: ", buffer, 15);
	setDni(buffer);
	
	InputHelper::pedirCadena("Email: ", buffer, 100);
	setEmail(buffer);
	
	cout << endl;
	cout << "TIPO DE SUSCRIPCION" << endl;
	cout << "1 - GRATIS" << endl;
	cout << "2 - PAGO" << endl;
	
	int tipo = InputHelper::pedirEnteroRango(
											 "Seleccione una opcion: ",
											 1,
											 2
											 );
	
	setTipoSuscriptor(tipo);
	
	cout << endl;
	cout << "Fecha de Nacimiento:" << endl;
	
	int d = InputHelper::pedirEnteroRango("Dia: ", 1, 31);
	int m = InputHelper::pedirEnteroRango("Mes: ", 1, 12);
	int a = InputHelper::pedirEnteroRango("Anio: ", 1900, 2025);
	
	_fechaNacimiento = Fecha(d, m, a);
	
	setEstado(true);
}

void Suscriptor::Mostrar() {
	
	cout << "ID: "
		<< _idSuscriptor
		<< " | Usuario: "
		<< getNombre()
		<< " "
		<< _apellido
		<< endl;
	
	cout << "DNI: "
		<< _dni
		<< " | Email: "
		<< _email
		<< endl;
	
	cout << "Estado: ";
	
	if(getEstado()) {
		cout << "ACTIVO";
	}
	else {
		cout << "INACTIVO";
	}
	
	cout << endl;
	
	cout << "Plan: ";
	
	if (_tipoSuscriptor == 1) {
		cout << "GRATIS";
	}
	else {
		cout << "PAGO";
	}
	
	cout << endl;
	
	cout << "F. Nac: "
		<< _fechaNacimiento.toString()
		<< endl;
	
	cout << "-----------------------------------"
		<< endl;
}
