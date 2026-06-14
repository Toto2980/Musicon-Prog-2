/*
 * InputHelper.cpp
 * Entrada de datos robusta desde la consola. Las utilidades de cadena se
 * delegan en Texto y la pausa en Consola, para no duplicar logica.
 */

#include "../include/InputHelper.h"
#include "../include/Texto.h"
#include "../include/Consola.h"
#include <iostream>
#include <limits>

using namespace std;

int InputHelper::pedirEntero(string mensaje, bool reintentar) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (reintentar) cout << "[ERROR] Ingrese un numero valido." << endl;
            else return -1;
        }
    }
}

int InputHelper::pedirEnteroRango(string mensaje, int min, int max) {
    while (true) {
        int numero = pedirEntero(mensaje);
        if (numero >= min && numero <= max) return numero;
        cout << "[ERROR] El valor debe estar entre " << min << " y " << max << "." << endl;
    }
}

int InputHelper::pedirOpcionDeLista(int cantidadOpciones) {
    if (cantidadOpciones <= 0) return 0;
    // Las opciones mostradas al usuario empiezan en 1, no en 0.
    return pedirEnteroRango("Seleccione una opcion: ", 1, cantidadOpciones);
}

void InputHelper::pedirCadena(string mensaje, char* buffer, int tamano) {
    cout << mensaje;
    cin.getline(buffer, tamano);
}

void InputHelper::pausa() {
    Consola::pausa();
}

bool InputHelper::sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    return Texto::igualesSinMayusculas(texto1, texto2);
}

bool InputHelper::sonIgualesSinMayusculas(const string& texto1, const string& texto2) {
    return Texto::igualesSinMayusculas(texto1, texto2);
}

string InputHelper::trim(const string& str) {
    return Texto::trim(str);
}

bool InputHelper::contieneSubcadena(const string& texto, const string& busqueda) {
    return Texto::contiene(texto.c_str(), busqueda.c_str());
}
