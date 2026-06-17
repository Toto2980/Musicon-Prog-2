/**
 * PATRÓN: Manager de Reportes (capa de análisis de datos)
 * Esta clase lee múltiples repositorios y cruza información para generar estadísticas.
 * No modifica nada — es de solo lectura.
 *
 * Técnica clave: pre-indexación con unordered_map para evitar O(N²).
 *
 *   SIN pre-indexación (lento, O(N²)):
 *     for cada acceso:           // N iteraciones
 *       for cada suscriptor:     // N búsqueda lineal por cada acceso
 *         if acceso.id == suscriptor.id → contador++
 *
 *   CON pre-indexación (rápido, O(N)):
 *     Fase 1 — construir índice:
 *       unordered_map<int,int> indice;  // ID suscriptor → posición en vector
 *       for cada suscriptor: indice[id] = posicion   // O(1) inserción
 *
 *     Fase 2 — contar:
 *       for cada acceso:
 *         int pos = indice[acceso.idSuscriptor];  // O(1) lookup en vez de O(N)
 *         contador[pos]++
 *
 * Con millones de accesos: la diferencia es HORAS (O(N²)) vs SEGUNDOS (O(N)).
 */

#include "../include/ReporteManager.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

/*
 * Muestra el menú principal de reportes y maneja la navegación entre diferentes tipos de informes.
 * Incluye reportes de reproducciones, rankings, búsquedas y estadísticas.
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
 * Genera un reporte de reproducciones mensuales para un año específico.
 * Cuenta las reproducciones por mes utilizando un arreglo de contadores.
 * Parámetros: Solicita el año al usuario.
 */
void ReporteManager::reporteReproduccionesAnuales() {
    int anio = InputHelper::pedirEntero("Anio: ");
    int cont[12] = {0}; // Contador para cada mes

    Accesos a;
    int total = a.ObtenerCantidadRegistros();
    for (int i = 0; i < total; i++) { // Itera sobre todos los accesos
        a.Leer(i);
        if (a.getFechaHora().getAnio() == anio) { // Filtra por año
            int m = a.getFechaHora().getMes();
            if (m >= 1 && m <= 12) cont[m - 1]++; // Incrementa contador del mes
        }
    }

    cout << "Repros " << anio << ":" << endl;
    for (int i = 0; i < 12; i++) cout << "Mes " << i + 1 << ": " << cont[i] << endl; // Muestra resultados
}

/*
 * Genera un reporte de reproducciones por suscriptor para un año específico.
 * Utiliza un mapa desordenado para indexar suscriptores y contar reproducciones eficientemente.
 * Parámetros: Solicita el año (0 para el año actual).
 */
void ReporteManager::reporteReproduccionesPorSuscriptor() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el año actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoSuscriptores archS;
    int totalSus = archS.ObtenerCantidadRegistros();

    vector<string> nombres; // Nombres de suscriptores
    vector<int> ids; // IDs de suscriptores
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorSuscriptor; // Mapa para acceso rápido por ID

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
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por año
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
 * Genera un reporte de reproducciones por género para un año específico.
 * Utiliza mapas para indexar géneros y canciones, evitando búsquedas lineales O(N²).
 * Parámetros: Solicita el año (0 para el año actual).
 */
void ReporteManager::reporteReproduccionesPorGenero() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el año actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoGeneros archG;
    int totalGen = archG.ObtenerCantidadRegistros();
    vector<int> ids; // IDs de géneros
    vector<string> nombres; // Nombres de géneros
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorGenero; // Mapa para acceso rápido

    for (int i = 0; i < totalGen; i++) { // Carga géneros activos
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
    unordered_map<int,int> generoPorCancion; // Mapa canción -> género
    for (int i = 0; i < totalCan; i++) { // Mapea canciones a géneros
        Canciones c = archC.Leer(i);
        if (c.getEstado()) generoPorCancion[c.getIdCancion()] = c.getIdGenero();
    }

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) { // Cuenta reproducciones por género
        a.Leer(i);
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por año
        auto it = generoPorCancion.find(a.getIdCancion()); // Busca género de la canción
        if (it != generoPorCancion.end()) {
            auto idx = indicePorGenero.find(it->second); // Busca índice del género
            if (idx != indicePorGenero.end()) contador[idx->second]++; // Incrementa
        }
    }

    for (size_t i = 0; i < ids.size(); i++) { // Muestra resultados
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

/*
 * Genera un reporte de reproducciones por canción para un año específico.
 * Usa el mismo patrón de unordered_map que el reporte por suscriptor:
 *   1. Carga todas las canciones activas en un mapa (ID → índice en el vector contador).
 *   2. Recorre todos los accesos del año y busca el ID de canción en el mapa en O(1).
 *   3. Muestra solo las canciones con al menos una reproducción.
 * Parámetros: Solicita el año al usuario.
 */
void ReporteManager::reporteReproduccionesPorCancion() {
    int anio = InputHelper::pedirEntero("Anio: ");

    ArchivoCanciones archC;
    int totalCan = archC.ObtenerCantidadRegistros();
    vector<int> ids;
    vector<string> nombres;
    vector<int> contador;
    unordered_map<int,int> indicePorCancion; // Mapa ID canción → índice en el vector contador

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
        auto it = indicePorCancion.find(a.getIdCancion()); // Búsqueda O(1) en el mapa
        if (it != indicePorCancion.end()) contador[it->second]++;
    }

    for (size_t i = 0; i < ids.size(); i++) {
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

/*
 * Lista todas las canciones activas de un género dado.
 * Busca el ID del género por nombre y luego filtra las canciones por idGenero.
 * Es una búsqueda simple sin mapas porque solo se usa para mostrar, no para contar.
 */
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

/*
 * Cuenta cuántas canciones tiene cada artista.
 * La cadena Artista → Album → Canción requiere dos mapas:
 *   - artistaPorAlbum: mapa de idAlbum → idArtista (construido una sola vez).
 *   - indicePorArtista: mapa de idArtista → índice en el vector contador.
 * Al recorrer las canciones, resolvemos el artista en dos pasos O(1):
 *   canción.idAlbum → artistaPorAlbum[idAlbum] = idArtista → indicePorArtista[idArtista].
 * Esto evita el O(N²) de buscar el álbum en el archivo por cada canción.
 */
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

/*
 * Cuenta cuántas canciones tiene un usuario en total a través de todas sus playlists.
 * Pasos:
 *   1. Verifica que el usuario exista.
 *   2. Carga todas las playlists en un mapa (idPlaylist → idCreador).
 *   3. Recorre el archivo DetallePlaylist (relación playlist-canción).
 *   4. Por cada detalle activo, busca en el mapa si la playlist pertenece al usuario.
 * Parámetros: Solicita el ID del usuario al usuario por consola.
 */
void ReporteManager::reporteCancionesPorUsuarioEnListas() {
    int idUser = InputHelper::pedirEntero("ID Usuario a consultar: ");

    ArchivoSuscriptores archSus;
    if (archSus.BuscarPosicion(idUser) == -1) {
        cout << "Usuario inexistente." << endl;
        return;
    }

    ArchivoPlaylist archP;
    int totalP = archP.ObtenerCantidadRegistros();
    unordered_map<int,int> creadorPorPlaylist;
    for (int i = 0; i < totalP; i++) {
        Playlist p = archP.Leer(i);
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

/*
 * Búsqueda inteligente de una canción en todas las playlists del sistema.
 * Permite búsqueda PARCIAL por nombre (ej: "love" encuentra "Love Story" y "I Love Rock").
 * Pasos:
 *   1. Busca todas las canciones que contengan la subcadena buscada.
 *   2. Carga todas las playlists en mapas (nombre y creador, indexados por ID).
 *   3. Recorre DetallePlaylist para saber en qué playlists aparece cada canción coincidente.
 *   4. Muestra para cada canción encontrada: en qué playlists está y quién las creó.
 *
 * Se usan unordered_map para evitar buscar en el archivo por cada detalle (O(1) vs O(N)).
 */
void ReporteManager::reporteBuscarCancionEnListasSmart() {
    char busqueda[100];
    InputHelper::pedirCadena("Ingrese nombre (o parte) de la cancion: ", busqueda, 100);

    ArchivoCanciones archC;
    int totalC = archC.ObtenerCantidadRegistros();
    vector<int> idsCoincidentes;
    unordered_map<int,string> nombrePorCancion;

    for (int i = 0; i < totalC; i++) {
        Canciones c = archC.Leer(i);
        if (c.getEstado() && InputHelper::contieneSubcadena(c.getNombre(), busqueda)) {
            idsCoincidentes.push_back(c.getIdCancion());
            nombrePorCancion[c.getIdCancion()] = c.getNombre();
        }
    }

    if (idsCoincidentes.empty()) {
        cout << "No se encontraron canciones con ese texto." << endl;
        return;
    }

    ArchivoPlaylist archP;
    int totalP = archP.ObtenerCantidadRegistros();
    unordered_map<int,string> nombrePorPlaylist;
    unordered_map<int,int> creadorPorPlaylist;
    for (int i = 0; i < totalP; i++) {
        Playlist p = archP.Leer(i);
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

/*
 * Genera el TOP 5 de canciones más escuchadas de todos los tiempos.
 * Usa std::sort con una lambda que compara por cantidad de reproducciones (mayor a menor).
 * La lambda [&] captura los vectores por referencia para poder compararlos.
 *
 * Algoritmo:
 *   1. Carga todas las canciones en vectores de ids, nombres y contadores.
 *   2. Recorre todos los accesos (sin filtro de año) e incrementa el contador.
 *   3. Crea un vector de índices y lo ordena según los contadores.
 *   4. Muestra los primeros 5 (o menos si hay menos de 5 canciones).
 */
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
