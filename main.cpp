/*
 * Archivo: main.cpp
 * Descripción: Punto de entrada de la aplicación Musicon.
 * Este archivo contiene la función main que inicializa la aplicación
 * y comienza la ejecución del sistema.
 */

#include "include/musicon.h"
#include <iostream>
#include <locale.h>


using namespace std;

int main() {

    setlocale(LC_ALL, "");
    // Crear instancia de la aplicación Musicon
    musicon app;

    // Iniciar el sistema
    app.iniciarSistema();

    return 0;
}
