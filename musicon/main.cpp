// main.cpp

#include <iostream>
#include "musicon.h"

using namespace std;

int main() {
    int opcion;

    // --- Paso 1: Crear un 'objeto' de la clase ---
    musicon sistema;

    do {
        // 2. Mostramos el menú
        sistema.mostrarMenuReportes();

        // 3. Leemos la opción
        cin >> opcion;

        // 4. Decidimos qué hacer
        switch (opcion) {
            case 1:
                sistema.reporteReproduccionesAnuales();
                break;
            case 2:
                sistema.reporteReproduccionesPorSuscriptor();
                break;
            case 3:
                sistema.reporteReproduccionesPorGenero();
                break;
            case 4:
                sistema.reporteReproduccionesPorCancion();
                break;
            case 5:
                sistema.reporteListarCancionesPorGenero();
                break;
            case 6:
                sistema.reporteCantidadCancionesPorArtista();
                break;
            case 0:
                cout << "Saliendo del sistema de informes..." << endl;
                break;
            default:
                cout << "[!] Opcion no valida. Intente de nuevo." << endl;
                break;
        }

        cout << endl;

    } while (opcion != 0);

    return 0;
}

