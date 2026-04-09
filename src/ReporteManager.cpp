/**
 * Este archivo implementa la clase ReporteManager. Genera diversos reportes y estadísticas
 * del sistema Musicon, incluyendo reproducciones, rankings y b�squedas inteligentes.
 * Utiliza mapas desordenados para optimizar el procesamiento de datos y evitar algoritmos O(N�).
 */

#include "../include/ReporteManager.h"
#include "InputHelper.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

/**
 * Función helper para verificar si un texto contiene una subcadena, ignorando mayúsculas/minúsculas.
 * Parámetros: texto - Texto donde buscar, busqueda - Subcadena a buscar.
 * Retorna: true si encuentra la subcadena.
 */
bool ReporteManager::contieneSubcadenaLocal(const char* texto, const char* busqueda) {
    string t = texto;
    string b = busqueda;
    for (auto& c : t) c = tolower(c); // Convierte a min�sculas
    for (auto& c : b) c = tolower(c);
    return t.find(b) != string::npos; // Busca la subcadena
}

/*
 * Muestra el men� principal de reportes y maneja la navegaci�n entre diferentes tipos de informes.
 * Incluye reportes de reproducciones, rankings, b�squedas y estad�sticas.
 */
void ReporteManager::MostrarMenuReportes() {
    int op;
    do {
        system("cls");
        cout << "--- MENU INFORMES ---" << endl;
        cout << "1. Reproducciones Anuales" << endl;
        cout << "2. Reproducciones por Suscriptor" << endl;
        cout << "3. Reproducciones por Genero" << endl;
        cout << "4. Reproducciones por Cancion" << endl;
        cout << "5. Listar Canciones de un Genero" << endl;
        cout << "6. Cantidad Canciones por Artista" << endl;
        cout << "7. Total Canciones de Usuario en Playlists" << endl;
        cout << "8. BUSCAR CANCION en Playlists (Smart Search)" << endl;
        cout << "9. Ranking de Canciones" << endl;
        cout << "0. Volver" << endl;

        op = InputHelper::pedirEnteroRango("Ingrese opcion: ", 0, 9);

        switch(op) {
            case 1: reporteReproduccionesAnuales(); break;
            case 2: reporteReproduccionesPorSuscriptor(); break;
            case 3: reporteReproduccionesPorGenero(); break;
            case 4: reporteReproduccionesPorCancion(); break;
            case 5: reporteListarCancionesPorGenero(); break;
            case 6: reporteCantidadCancionesPorArtista(); break;
            case 7: reporteCancionesPorUsuarioEnListas(); break;
            case 8: reporteBuscarCancionEnListasSmart(); break;
            case 9: reporteRankingCanciones(); break;
        }
        if(op != 0) InputHelper::pausa();
    } while(op != 0);
}

/*
 * Genera un reporte de reproducciones mensuales para un a�o espec�fico.
 * Cuenta las reproducciones por mes utilizando un arreglo de contadores.
 * Par�metros: Solicita el a�o al usuario.
 */
void ReporteManager::reporteReproduccionesAnuales() {
    int anio = InputHelper::pedirEntero("Anio: ");
    int cont[12] = {0}; // Contador para cada mes

    Accesos a;
    int total = a.ObtenerCantidadRegistros();
    for (int i = 0; i < total; i++) { // Itera sobre todos los accesos
        a.Leer(i);
        if (a.getFechaHora().getAnio() == anio) { // Filtra por a�o
            int m = a.getFechaHora().getMes();
            if (m >= 1 && m <= 12) cont[m - 1]++; // Incrementa contador del mes
        }
    }

    cout << "Repros " << anio << ":" << endl;
    for (int i = 0; i < 12; i++) cout << "Mes " << i + 1 << ": " << cont[i] << endl; // Muestra resultados
}

/*
 * Genera un reporte de reproducciones por suscriptor para un a�o espec�fico.
 * Utiliza un mapa desordenado para indexar suscriptores y contar reproducciones eficientemente.
 * Par�metros: Solicita el a�o (0 para el a�o actual).
 */
void ReporteManager::reporteReproduccionesPorSuscriptor() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el a�o actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoSuscriptores archS;
    int totalSus = archS.ObtenerCantidadRegistros();

    vector<string> nombres; // Nombres de suscriptores
    vector<int> ids; // IDs de suscriptores
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorSuscriptor; // Mapa para acceso r�pido por ID

    for (int i = 0; i < totalSus; i++) { // Carga suscriptores activos
        Suscriptor s = archS.Leer(i);
        if (s.getEstado()) {
            ids.push_back(s.getIdSuscriptor());
            nombres.push_back(s.getNombre());
            contador.push_back(0);
            indicePorSuscriptor[s.getIdSuscriptor()] = static_cast<int>(contador.size()) - 1; // Indexa
        }
    }

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) { // Cuenta reproducciones por suscriptor
        a.Leer(i);
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por a�o
        auto it = indicePorSuscriptor.find(a.getIdSuscriptor()); // Busca en mapa
        if (it != indicePorSuscriptor.end()) {
            contador[it->second]++; // Incrementa contador
        }
    }

    for (size_t i = 0; i < ids.size(); i++) { // Muestra resultados
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

/*
 * Genera un reporte de reproducciones por g�nero para un a�o espec�fico.
 * Utiliza mapas para indexar g�neros y canciones, evitando b�squedas lineales O(N�).
 * Par�metros: Solicita el a�o (0 para el a�o actual).
 */
void ReporteManager::reporteReproduccionesPorGenero() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el a�o actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoGeneros archG;
    int totalGen = archG.ObtenerCantidadRegistros();
    vector<int> ids; // IDs de g�neros
    vector<string> nombres; // Nombres de g�neros
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorGenero; // Mapa para acceso r�pido

    for (int i = 0; i < totalGen; i++) { // Carga g�neros activos
        Genero g = archG.Leer(i);
        if (g.getEstado()) {
            ids.push_back(g.getIdGeneros());
            nombres.push_back(g.getNombre());
            contador.push_back(0);
            indicePorGenero[g.getIdGeneros()] = static_cast<int>(contador.size()) - 1; // Indexa
        }
    }

    ArchivoCanciones archC;
    int totalCan = archC.ObtenerCantidadRegistros();
    unordered_map<int,int> generoPorCancion; // Mapa canci�n -> g�nero
    for (int i = 0; i < totalCan; i++) { // Mapea canciones a g�neros
        Canciones c = archC.Leer(i);
        if (c.getEstado()) generoPorCancion[c.getIdCancion()] = c.getIdGenero();
    }

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) { // Cuenta reproducciones por g�nero
        a.Leer(i);
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por a�o
        auto it = generoPorCancion.find(a.getIdCancion()); // Busca g�nero de la canci�n
        if (it != generoPorCancion.end()) {
            auto idx = indicePorGenero.find(it->second); // Busca �ndice del g�nero
            if (idx != indicePorGenero.end()) contador[idx->second]++; // Incrementa
        }
    }

    for (size_t i = 0; i < ids.size(); i++) { // Muestra resultados
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

void ReporteManager::reporteReproduccionesPorCancion() {
    int anio = InputHelper::pedirEntero("Anio: ");

    ArchivoCanciones archC;
    int totalCan = archC.ObtenerCantidadRegistros();
    vector<int> ids;
    vector<string> nombres;
    vector<int> contador;
    unordered_map<int,int> indicePorCancion;

    for (int i = 0; i < totalCan; i++) {
        Canciones c = archC.Leer(i);
        if (c.getEstado()) {
            ids.push_back(c.getIdCancion());
            nombres.push_back(c.getNombre());
            contador.push_back(0);
            indicePorCancion[c.getIdCancion()] = static_cast<int>(contador.size()) - 1;
        }
    }

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) {
        a.Leer(i);
        if (a.getFechaHora().getAnio() != anio) continue;
        auto it = indicePorCancion.find(a.getIdCancion());
        if (it != indicePorCancion.end()) contador[it->second]++;
    }

    for (size_t i = 0; i < ids.size(); i++) {
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

void ReporteManager::reporteListarCancionesPorGenero() {
    char nom[50];
    InputHelper::pedirCadena("Genero: ", nom, 50);

    ArchivoGeneros archG;
    int idG = archG.BuscarIDPorNombre(nom);
    if (idG == -1) {
        cout << "No existe." << endl;
        return;
    }

    ArchivoCanciones archC;
    int total = archC.ObtenerCantidadRegistros();
    for (int i = 0; i < total; i++) {
        Canciones c = archC.Leer(i);
        if (c.getEstado() && c.getIdGenero() == idG) cout << "- " << c.getNombre() << endl;
    }
}

void ReporteManager::reporteCantidadCancionesPorArtista() {
    ArchivoArtistas archArt;
    int totalArt = archArt.ObtenerCantidadRegistros();

    vector<int> ids;
    vector<string> nombres;
    vector<int> contador;
    unordered_map<int,int> indicePorArtista;

    for (int i = 0; i < totalArt; i++) {
        Artista art = archArt.Leer(i);
        if (art.getEstado()) {
            ids.push_back(art.getIdArtista());
            nombres.push_back(art.getNombre());
            contador.push_back(0);
            indicePorArtista[art.getIdArtista()] = static_cast<int>(contador.size()) - 1;
        }
    }

    ArchivoAlbum archAlb;
    int totalAlb = archAlb.ObtenerCantidadRegistros();
    unordered_map<int,int> artistaPorAlbum;
    for (int i = 0; i < totalAlb; i++) {
        Album alb = archAlb.Leer(i);
        if (alb.getEstado()) artistaPorAlbum[alb.getIdAlbum()] = alb.getIdArtista();
    }

    ArchivoCanciones archC;
    int totalCan = archC.ObtenerCantidadRegistros();
    for (int i = 0; i < totalCan; i++) {
        Canciones c = archC.Leer(i);
        if (!c.getEstado()) continue;
        auto it = artistaPorAlbum.find(c.getIdAlbum());
        if (it != artistaPorAlbum.end()) {
            auto idx = indicePorArtista.find(it->second);
            if (idx != indicePorArtista.end()) contador[idx->second]++;
        }
    }

    for (size_t i = 0; i < ids.size(); i++) {
        cout << nombres[i] << ": " << contador[i] << endl;
    }
}

void ReporteManager::reporteCancionesPorUsuarioEnListas() {
    int idUser = InputHelper::pedirEntero("ID Usuario a consultar: ");

    ArchivoSuscriptores archSus;
    if (archSus.BuscarPosicion(idUser) == -1) {
        cout << "Usuario inexistente." << endl;
        return;
    }

    Playlist p;
    int totalP = p.ObtenerCantidadRegistros();
    unordered_map<int,int> creadorPorPlaylist;
    for (int i = 0; i < totalP; i++) {
        if (!p.Leer(i)) continue;
        if (p.getEstado()) creadorPorPlaylist[p.getIdPlaylist()] = p.getIdSuscriptorCreador();
    }

    DetallePlaylist dp;
    int totalDP = dp.ObtenerCantidadRegistros();
    int contadorCanciones = 0;
    for (int i = 0; i < totalDP; i++) {
        dp.Leer(i);
        if (!dp.getEstado()) continue;
        auto it = creadorPorPlaylist.find(dp.getIdPlaylist());
        if (it != creadorPorPlaylist.end() && it->second == idUser) contadorCanciones++;
    }

    cout << "El usuario ID " << idUser << " tiene un total de " << contadorCanciones << " canciones en sus listas." << endl;
}

void ReporteManager::reporteBuscarCancionEnListasSmart() {
    char busqueda[100];
    InputHelper::pedirCadena("Ingrese nombre (o parte) de la cancion: ", busqueda, 100);

    ArchivoCanciones archC;
    int totalC = archC.ObtenerCantidadRegistros();
    vector<int> idsCoincidentes;
    unordered_map<int,string> nombrePorCancion;

    for (int i = 0; i < totalC; i++) {
        Canciones c = archC.Leer(i);
        if (c.getEstado() && contieneSubcadenaLocal(c.getNombre(), busqueda)) {
            idsCoincidentes.push_back(c.getIdCancion());
            nombrePorCancion[c.getIdCancion()] = c.getNombre();
        }
    }

    if (idsCoincidentes.empty()) {
        cout << "No se encontraron canciones con ese texto." << endl;
        return;
    }

    Playlist p;
    int totalP = p.ObtenerCantidadRegistros();
    unordered_map<int,string> nombrePorPlaylist;
    unordered_map<int,int> creadorPorPlaylist;
    for (int i = 0; i < totalP; i++) {
        if (!p.Leer(i)) continue;
        if (p.getEstado()) {
            nombrePorPlaylist[p.getIdPlaylist()] = p.getNombre();
            creadorPorPlaylist[p.getIdPlaylist()] = p.getIdSuscriptorCreador();
        }
    }

    unordered_map<int, vector<int>> playlistsPorCancion;
    DetallePlaylist dp;
    int totalDP = dp.ObtenerCantidadRegistros();
    for (int i = 0; i < totalDP; i++) {
        dp.Leer(i);
        if (!dp.getEstado()) continue;
        if (nombrePorCancion.find(dp.getIdCancion()) != nombrePorCancion.end()) {
            playlistsPorCancion[dp.getIdCancion()].push_back(dp.getIdPlaylist());
        }
    }

    for (int idCancion : idsCoincidentes) {
        cout << ">> COINCIDENCIA: " << nombrePorCancion[idCancion] << " (ID " << idCancion << ")" << endl;
        auto& listas = playlistsPorCancion[idCancion];
        if (listas.empty()) {
            cout << "    (No esta en ninguna playlist)" << endl;
        } else {
            for (int idLista : listas) {
                auto it = nombrePorPlaylist.find(idLista);
                if (it != nombrePorPlaylist.end()) {
                    cout << "    -> En Playlist: " << it->second << " (Usuario ID " << creadorPorPlaylist[idLista] << ")" << endl;
                }
            }
        }
        cout << "---------------------------------" << endl;
    }
}

void ReporteManager::reporteRankingCanciones() {
    system("cls");
    cout << "--- RANKING DE CANCIONES MAS ESCUCHADAS ---" << endl;

    ArchivoCanciones archC;
    int totalReg = archC.ObtenerCantidadRegistros();
    vector<int> ids;
    vector<string> nombres;
    unordered_map<int,int> indicePorCancion;
    vector<int> contador;

    for (int i = 0; i < totalReg; i++) {
        Canciones c = archC.Leer(i);
        if (c.getEstado()) {
            ids.push_back(c.getIdCancion());
            nombres.push_back(c.getNombre());
            contador.push_back(0);
            indicePorCancion[c.getIdCancion()] = static_cast<int>(contador.size()) - 1;
        }
    }

    Accesos acc;
    int totalAcc = acc.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) {
        acc.Leer(i);
        auto it = indicePorCancion.find(acc.getIdCancion());
        if (it != indicePorCancion.end()) contador[it->second]++;
    }

    vector<int> orden(ids.size());
    for (size_t i = 0; i < ids.size(); i++) orden[i] = static_cast<int>(i);
    sort(orden.begin(), orden.end(), [&](int a, int b) {
        return contador[a] > contador[b];
    });

    int tope = static_cast<int>(orden.size());
    if (tope > 5) tope = 5;
    cout << endl;
    cout << "PUESTO\tCANTIDAD\tTITULO" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < tope; i++) {
        int idx = orden[i];
        cout << "#" << i + 1 << "\t" << contador[idx] << "\t\t" << nombres[idx] << endl;
    }
}
