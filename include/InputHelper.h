#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>

/** Clase con métodos estáticos para ayudar con la entrada de datos del usuario. */
class InputHelper {
public:
    /** Pide un entero al usuario. Parámetros: mensaje - Mensaje a mostrar, reintentar - Si reintentar en caso de error. Retorna: El entero ingresado. */
    static int pedirEntero(std::string mensaje, bool reintentar = true);
    /** Pide un entero en un rango. Parámetros: mensaje - Mensaje a mostrar, min - Valor mínimo, max - Valor máximo. Retorna: El entero en rango. */
    static int pedirEnteroRango(std::string mensaje, int min, int max);
    /** Pide una opción de una lista. Parámetros: cantidadOpciones - Cantidad de opciones. Retorna: La opción elegida. */
    static int pedirOpcionDeLista(int cantidadOpciones);
    /** Pide una cadena al usuario. Parámetros: mensaje - Mensaje a mostrar, buffer - Buffer para almacenar la cadena, tamano - Tamaño del buffer. */
    static void pedirCadena(std::string mensaje, char* buffer, int tamano);
    /** Pausa la ejecución esperando entrada del usuario. */
    static void pausa();

    /** Compara dos cadenas sin distinguir mayúsculas/minúsculas. */
    static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2);
    static bool sonIgualesSinMayusculas(const std::string& texto1, const std::string& texto2);

    // --- NUEVAS UTILIDADES PARA IMPORTACIÓN ---
    // Quita espacios al principio y final
    /** Quita espacios al principio y final de una cadena. Parámetros: str - La cadena original. Retorna: La cadena sin espacios. */
    static std::string trim(const std::string& str);
	
	// --- NUEVA HERRAMIENTA CENTRALIZADA ---
	/** Verifica si una cadena contiene una subcadena ignorando may�sculas/min�sculas */
	static bool contieneSubcadena(const std::string& texto, const std::string& busqueda);
};

#endif // INPUTHELPER_H
