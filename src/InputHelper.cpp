/**
 * Esta clase centraliza todas las funciones de entrada del usuario y utilidades de texto.
 * Al concentrar las validaciones aqui, el resto del codigo queda mas limpio
 * y los errores de entrada se manejan en un solo lugar.
 *
 * FUNCIONES DISPONIBLES:
 *   - pedirEntero: lee un entero, reintenta si el usuario escribe texto.
 *   - pedirEnteroRango: igual que pedirEntero pero fuerza un rango [min, max].
 *   - pedirCadena: lee una linea completa con getline (soporta espacios).
 *   - pausa: espera que el usuario presione Enter antes de continuar.
 *   - sonIgualesSinMayusculas: compara strings ignorando mayusculas/minusculas.
 *   - trim: elimina espacios al inicio y al final de un string.
 *   - contieneSubcadena: verifica si un texto contiene una subcadena (case-insensitive).
 */

#include "../include/InputHelper.h"
#include <iostream>
#include <limits>
#include <cstdio>
#include <algorithm>
#include <cctype>

using namespace std;

/**
 * Lee un entero del teclado. Si el usuario escribe texto no numerico,
 * limpia el buffer de cin y vuelve a pedir (si reintentar=true).
 * Si reintentar=false, devuelve -1 ante un error de entrada.
 */
int InputHelper::pedirEntero(string mensaje, bool reintentar) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            // Descarta el salto de linea que queda en el buffer despues de cin >>
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        } else {
            // cin fallo (entrada invalida): limpia el estado de error y el buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (reintentar) cout << "[ERROR] Ingrese un numero valido." << endl;
            else return -1;
        }
    }
}

/**
 * Lee un entero y repite hasta que el valor este dentro de [min, max].
 * Util para menus: el usuario no puede escribir una opcion invalida.
 */
int InputHelper::pedirEnteroRango(string mensaje, int min, int max) {
    int numero;
    while (true) {
        numero = pedirEntero(mensaje);
        if (numero >= min && numero <= max) return numero;
        cout << "[ERROR] El valor debe estar entre " << min << " y " << max << "." << endl;
    }
}

/**
 * Muestra opciones numeradas del 1 al cantidadOpciones y pide que el usuario elija una.
 * Retorna 0 si cantidadOpciones es 0 o negativo.
 */
int InputHelper::pedirOpcionDeLista(int cantidadOpciones) {
    if (cantidadOpciones <= 0) return 0;
    // Las opciones visibles empiezan en 1, el rango es [1, cantidadOpciones]
    return pedirEnteroRango("Seleccione una opcion: ", 1, cantidadOpciones);
}

/**
 * Lee una linea completa del teclado con espacios usando cin.getline.
 * A diferencia de cin >>, getline puede leer nombres como "Foo Fighters".
 * 'tamano' indica el tamano maximo del buffer incluyendo el terminador '\0'.
 */
void InputHelper::pedirCadena(string mensaje, char* buffer, int tamano) {
    cout << mensaje;
    cin.getline(buffer, tamano);
}

/**
 * Pausa la ejecucion hasta que el usuario presione Enter.
 * Limpia cualquier contenido residual en el buffer antes de esperar.
 */
void InputHelper::pausa() {
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Compara dos cadenas de C ignorando diferencias de mayusculas/minusculas.
 * Usa tolower() en cada caracter para normalizar antes de comparar.
 * El cast a unsigned char es obligatorio: tolower espera un valor positivo.
 * Retorna true solo si las cadenas son identicas (misma longitud y mismos caracteres).
 */
bool InputHelper::sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false; // Caracteres diferentes: no son iguales
        }
        ++texto1;
        ++texto2;
    }

    // Verifica que ambas cadenas hayan terminado al mismo tiempo (misma longitud)
    return *texto1 == *texto2;
}

/** Sobrecarga para strings de C++ — convierte a char* y reutiliza la logica anterior. */
bool InputHelper::sonIgualesSinMayusculas(const string& texto1, const string& texto2) {
    return sonIgualesSinMayusculas(texto1.c_str(), texto2.c_str());
}

/**
 * Elimina los espacios al inicio y al final de un string (trim).
 * Util para limpiar entradas del usuario donde puede haber espacios accidentales.
 * Ejemplo: "  Rock " → "Rock".
 */
string InputHelper::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return string(); // Solo espacios → devuelve vacio
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/**
 * Verifica si 'texto' contiene 'busqueda' ignorando mayusculas/minusculas.
 * Convierte ambos strings a minusculas y usa string::find para la busqueda.
 * Se usa en los buscadores de playlists y canciones (busqueda parcial por nombre).
 */
bool InputHelper::contieneSubcadena(const string& texto, const string& busqueda) {
    string t = texto;
    string b = busqueda;
    // Convierte a minusculas para comparacion case-insensitive
    for (auto& c : t) c = tolower(static_cast<unsigned char>(c));
    for (auto& c : b) c = tolower(static_cast<unsigned char>(c));
    return t.find(b) != string::npos;
}
