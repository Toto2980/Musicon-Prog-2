#include "InputHelper.h"
#include <iostream>
#include <limits>
#include <cstdio>
#include <algorithm>

using namespace std;

// ... (Funciones anteriores se mantienen igual) ...
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
    int numero;
    while (true) {
        numero = pedirEntero(mensaje);
        if (numero >= min && numero <= max) return numero;
        cout << "[ERROR] El valor debe estar entre " << min << " y " << max << "." << endl;
    }
}

int InputHelper::pedirOpcionDeLista(int cantidadOpciones) {
    if (cantidadOpciones == 0) return 0;
    return pedirEnteroRango("Seleccione una opcion: ", 0, cantidadOpciones);
}

void InputHelper::pedirCadena(string mensaje, char* buffer, int tamano) {
    cout << mensaje;
    cin.getline(buffer, tamano);
}

void InputHelper::pausa() {
    cout << endl;
    system("pause");
}

// --- IMPLEMENTACI�N DE TRIM ---
string InputHelper::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
