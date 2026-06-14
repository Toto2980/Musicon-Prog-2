/*
 * Texto.cpp
 * Implementacion de las utilidades de cadenas declaradas en Texto.h.
 */

#include "../include/Texto.h"
#include <cctype>

namespace Texto {

bool igualesSinMayusculas(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) return a == b;
    while (*a && *b) {
        if (std::tolower(static_cast<unsigned char>(*a)) !=
            std::tolower(static_cast<unsigned char>(*b))) {
            return false;
        }
        ++a;
        ++b;
    }
    return *a == *b;
}

bool igualesSinMayusculas(const std::string& a, const std::string& b) {
    return igualesSinMayusculas(a.c_str(), b.c_str());
}

bool contiene(const char* texto, const char* busqueda) {
    if (texto == nullptr || busqueda == nullptr) return false;
    std::string t = aMinusculas(texto);
    std::string b = aMinusculas(busqueda);
    return t.find(b) != std::string::npos;
}

std::string trim(const std::string& str) {
    std::size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return std::string();
    std::size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::string aMinusculas(std::string str) {
    for (char& c : str) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

} // namespace Texto
