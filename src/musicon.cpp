// musicon.cpp

#include "musicon.h"


#include <iostream>
using namespace std;


// Constructor y Destructor

musicon::musicon()
{
    //ctor
}

musicon::~musicon()
{
    //dtor
}


// --- DEFINICIONES DE FUNCIONES DE REPORTES ---


void musicon::mostrarMenuReportes() {
    cout << "--- SISTEMA DE INFORMES MUSICON (Modo Clase) ---" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. Reproducciones anuales" << endl;
    cout << "2. Reproducciones por suscriptor" << endl;
    cout << "3. Cantidad de reproducciones por genero" << endl;
    cout << "4. Reproducciones por cancion" << endl;
    cout << "5. Listar canciones de un genero" << endl;
    cout << "6. Cantidad de canciones por artista" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "0. Salir" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Ingrese su opcion: ";
}

// Por ahora, todas las funciones solo avisan que no están hechas.

void musicon::reporteReproduccionesAnuales() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 1: REPRODUCCIONES ANUALES" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

void musicon::reporteReproduccionesPorSuscriptor() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 2: REPRODUCCIONES POR SUSCRIPTOR" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

void musicon::reporteReproduccionesPorGenero() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 3: REPRODUCCIONES POR GENERO" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

void musicon::reporteReproduccionesPorCancion() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 4: REPRODUCCIONES POR CANCION" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

void musicon::reporteListarCancionesPorGenero() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 5: LISTAR CANCIONES DE UN GENERO" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

void musicon::reporteCantidadCancionesPorArtista() {
    cout << endl;
    cout << "***********************************" << endl;
    cout << "INFORME 6: CANTIDAD DE CANCIONES POR ARTISTA" << endl;
    cout << "[!] Funcion no implementada." << endl;
    cout << "***********************************" << endl;
}

