/*
 * Consola.cpp
 * Implementacion de las utilidades de terminal declaradas en Consola.h.
 */

#include "../include/Consola.h"
#include <iostream>
#include <string>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace Consola {

void iniciar() {
#ifdef _WIN32
    // Permite mostrar correctamente acentos y simbolos UTF-8 en la consola.
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void limpiar() {
#ifdef _WIN32
    // Limpieza nativa con la API de Windows (sin lanzar el comando "cls").
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;

    DWORD celdas = static_cast<DWORD>(csbi.dwSize.X) * csbi.dwSize.Y;
    COORD inicio = {0, 0};
    DWORD escritas;

    FillConsoleOutputCharacter(hOut, ' ', celdas, inicio, &escritas);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, celdas, inicio, &escritas);
    SetConsoleCursorPosition(hOut, inicio);
#else
    // Secuencia ANSI estandar para terminales tipo Unix.
    std::cout << "\033[2J\033[H";
#endif
}

void pausa() {
    std::cout << "\nPresione ENTER para continuar...";
    // Limpia cualquier resto en el buffer y espera una linea completa.
    if (std::cin.rdbuf()->in_avail() == 0) {
        std::string descarte;
        std::getline(std::cin, descarte);
    } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

} // namespace Consola
