/*
 * InputHelper.h
 * Métodos estáticos para leer datos del usuario de forma robusta.
 * Las utilidades de cadena (comparar, trim, contiene) se delegan en Texto.
 */

#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>

/** Helpers de entrada por consola. */
class InputHelper {
public:
    /** Pide un entero. Si 'reintentar' es false, devuelve -1 ante una entrada inválida. */
    static int pedirEntero(std::string mensaje, bool reintentar = true);
    /** Pide un entero dentro de [min, max]. */
    static int pedirEnteroRango(std::string mensaje, int min, int max);
    /** Pide una opción de una lista de 1..cantidadOpciones. */
    static int pedirOpcionDeLista(int cantidadOpciones);
    /** Pide una cadena y la guarda en 'buffer' (hasta 'tamano' caracteres). */
    static void pedirCadena(std::string mensaje, char* buffer, int tamano);
    /** Pausa la ejecución hasta que el usuario presiona ENTER. */
    static void pausa();

    /** Compara dos cadenas sin distinguir mayúsculas/minúsculas. */
    static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2);
    static bool sonIgualesSinMayusculas(const std::string& texto1, const std::string& texto2);

    /** Quita espacios al principio y al final de una cadena. */
    static std::string trim(const std::string& str);

    /** Indica si 'texto' contiene 'busqueda' ignorando mayúsculas/minúsculas. */
    static bool contieneSubcadena(const std::string& texto, const std::string& busqueda);
};

#endif // INPUTHELPER_H
