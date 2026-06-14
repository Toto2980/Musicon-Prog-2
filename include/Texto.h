/*
 * Texto.h
 * Utilidades de cadenas reutilizables en todo el sistema.
 *
 * Centraliza funciones que antes estaban duplicadas (con implementaciones casi
 * identicas) en InputHelper, CancionManager, PlaylistManager y ReporteManager:
 * comparacion sin distinguir mayusculas, busqueda de subcadenas y trim.
 */

#ifndef TEXTO_H
#define TEXTO_H

#include <string>

namespace Texto {

    /** Compara dos cadenas C ignorando mayusculas/minusculas. */
    bool igualesSinMayusculas(const char* a, const char* b);

    /** Sobrecarga para std::string. */
    bool igualesSinMayusculas(const std::string& a, const std::string& b);

    /** Indica si 'texto' contiene 'busqueda' como subcadena, ignorando mayusculas. */
    bool contiene(const char* texto, const char* busqueda);

    /** Devuelve la cadena sin espacios al inicio ni al final. */
    std::string trim(const std::string& str);

    /** Devuelve una copia en minusculas. */
    std::string aMinusculas(std::string str);

} // namespace Texto

#endif // TEXTO_H
