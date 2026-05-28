#include "InputHelper.h"
#include <iostream>
#include <limits>
#include <cstdio>
#include <algorithm>
#include <cctype>

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
    int numero;
    while (true) {
        numero = pedirEntero(mensaje);
        if (numero >= min && numero <= max) return numero;
        cout << "[ERROR] El valor debe estar entre " << min << " y " << max << "." << endl;
    }
}

int InputHelper::pedirOpcionDeLista(int cantidadOpciones) {
    if (cantidadOpciones <= 0) return 0;
    // Opciones mostradas al usuario suelen empezar en 1, no en 0
    return pedirEnteroRango("Seleccione una opcion: ", 1, cantidadOpciones);
}

void InputHelper::pedirCadena(string mensaje, char* buffer, int tamano) {
    cout << mensaje;
    // Asegurarse de descartar un posible '\n' pendiente antes de leer la línea
    if (cin.peek() == '\n') cin.get();
    cin.getline(buffer, tamano);
}

void InputHelper::pausa() {
    cout << endl;
    system("pause");
}

// --- IMPLEMENTACIÓN DE TRIM ---
bool InputHelper::sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false;
        }
        ++texto1;
        ++texto2;
    }

    return *texto1 == *texto2;
}

bool InputHelper::sonIgualesSinMayusculas(const string& texto1, const string& texto2) {
    return sonIgualesSinMayusculas(texto1.c_str(), texto2.c_str());
}

string InputHelper::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return string();
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
