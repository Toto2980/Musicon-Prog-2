/**
 * PATRON: Manager de Reportes (capa de analisis de datos)
 * Esta clase lee multiples repositorios y cruza informacion para generar estadisticas.
 * No modifica nada — es de solo lectura.
 *
 * Tecnica clave: pre-indexacion con unordered_map para evitar O(N²).
 *
 *   SIN pre-indexacion (lento, O(N²)):
 *     for cada acceso:           // N iteraciones
 *       for cada suscriptor:     // N busqueda lineal por cada acceso
 *         if acceso.id == suscriptor.id → contador++
 *
 *   CON pre-indexacion (rapido, O(N)):
 *     Fase 1 — construir indice:
 *       unordered_map<int,int> indice;  // ID suscriptor → posicion en vector
 *       for cada suscriptor: indice[id] = posicion   // O(1) insercion
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
#include <fstream>

using namespace std;

/*
 * Muestra el menu principal de reportes y maneja la navegacion entre diferentes tipos de informes.
 * Incluye reportes de reproducciones, rankings, busquedas y estadisticas.
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
        cout << "10. Informe de Suscriptores" << endl;
        cout << "11. Exportar Suscriptores a CSV" << endl;
        cout << "0. Volver" << endl;

        op = InputHelper::pedirEnteroRango("Ingrese opcion: ", 0, 11);

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
            case 10: reporteUsuarios(); break;
            case 11: exportarReporteSuscriptoresCSV(); break;
        }
        if(op != 0) InputHelper::pausa();
    } while(op != 0);
}

/*
 * Genera un reporte de reproducciones mensuales para un ano especifico.
 * Cuenta las reproducciones por mes utilizando un arreglo de contadores.
 * Parametros: Solicita el ano al usuario.
 */
void ReporteManager::reporteReproduccionesAnuales() {
    int anio = InputHelper::pedirEntero("Anio: ");
    int cont[12] = {0}; // Contador para cada mes

    Accesos a;
    int total = a.ObtenerCantidadRegistros();
    for (int i = 0; i < total; i++) { // Itera sobre todos los accesos
        a.Leer(i);
        if (a.getFechaHora().getAnio() == anio) { // Filtra por ano
            int m = a.getFechaHora().getMes();
            if (m >= 1 && m <= 12) cont[m - 1]++; // Incrementa contador del mes
        }
    }

    cout << "Repros " << anio << ":" << endl;
    for (int i = 0; i < 12; i++) cout << "Mes " << i + 1 << ": " << cont[i] << endl; // Muestra resultados
}

/*
 * Genera un reporte de reproducciones por suscriptor para un ano especifico.
 * Utiliza un mapa desordenado para indexar suscriptores y contar reproducciones eficientemente.
 * Parametros: Solicita el ano (0 para el ano actual).
 */
void ReporteManager::reporteReproduccionesPorSuscriptor() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el ano actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoSuscriptores archS;
    int totalSus = archS.ObtenerCantidadRegistros();

    vector<string> nombres; // Nombres de suscriptores
    vector<int> ids; // IDs de suscriptores
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorSuscriptor; // Mapa para acceso rapido por ID

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
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por ano
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
 * Genera un reporte de reproducciones por genero para un ano especifico.
 * Utiliza mapas para indexar generos y canciones, evitando busquedas lineales O(N²).
 * Parametros: Solicita el ano (0 para el ano actual).
 */
void ReporteManager::reporteReproduccionesPorGenero() {
    int anio = InputHelper::pedirEntero("Anio (0=actual): ");
    if (anio == 0) { // Si es 0, usa el ano actual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        anio = tm->tm_year + 1900;
    }

    ArchivoGeneros archG;
    int totalGen = archG.ObtenerCantidadRegistros();
    vector<int> ids; // IDs de generos
    vector<string> nombres; // Nombres de generos
    vector<int> contador; // Contador de reproducciones
    unordered_map<int,int> indicePorGenero; // Mapa para acceso rapido

    for (int i = 0; i < totalGen; i++) { // Carga generos activos
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
    unordered_map<int,int> generoPorCancion; // Mapa cancion -> genero
    for (int i = 0; i < totalCan; i++) { // Mapea canciones a generos
        Canciones c = archC.Leer(i);
        if (c.getEstado()) generoPorCancion[c.getIdCancion()] = c.getIdGenero();
    }

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    for (int i = 0; i < totalAcc; i++) { // Cuenta reproducciones por genero
        a.Leer(i);
        if (a.getFechaHora().getAnio() != anio) continue; // Filtra por ano
        auto it = generoPorCancion.find(a.getIdCancion()); // Busca genero de la cancion
        if (it != generoPorCancion.end()) {
            auto idx = indicePorGenero.find(it->second); // Busca indice del genero
            if (idx != indicePorGenero.end()) contador[idx->second]++; // Incrementa
        }
    }

    for (size_t i = 0; i < ids.size(); i++) { // Muestra resultados
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

/*
 * Genera un reporte de reproducciones por cancion para un ano especifico.
 * Usa el mismo patron de unordered_map que el reporte por suscriptor:
 *   1. Carga todas las canciones activas en un mapa (ID → indice en el vector contador).
 *   2. Recorre todos los accesos del ano y busca el ID de cancion en el mapa en O(1).
 *   3. Muestra solo las canciones con al menos una reproduccion.
 * Parametros: Solicita el ano al usuario.
 */
void ReporteManager::reporteReproduccionesPorCancion() {
    int anio = InputHelper::pedirEntero("Anio: ");

    ArchivoCanciones archC;
    int totalCan = archC.ObtenerCantidadRegistros();
    vector<int> ids;
    vector<string> nombres;
    vector<int> contador;
    unordered_map<int,int> indicePorCancion; // Mapa ID cancion → indice en el vector contador

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
        auto it = indicePorCancion.find(a.getIdCancion()); // Busqueda O(1) en el mapa
        if (it != indicePorCancion.end()) contador[it->second]++;
    }

    for (size_t i = 0; i < ids.size(); i++) {
        if (contador[i] > 0) cout << nombres[i] << ": " << contador[i] << endl;
    }
}

/*
 * Lista todas las canciones activas de un genero dado.
 * Busca el ID del genero por nombre y luego filtra las canciones por idGenero.
 * Es una busqueda simple sin mapas porque solo se usa para mostrar, no para contar.
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
 * Cuenta cuantas canciones tiene cada artista.
 * La cadena Artista → Album → Cancion requiere dos mapas:
 *   - artistaPorAlbum: mapa de idAlbum → idArtista (construido una sola vez).
 *   - indicePorArtista: mapa de idArtista → indice en el vector contador.
 * Al recorrer las canciones, resolvemos el artista en dos pasos O(1):
 *   cancion.idAlbum → artistaPorAlbum[idAlbum] = idArtista → indicePorArtista[idArtista].
 * Esto evita el O(N²) de buscar el album en el archivo por cada cancion.
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
 * Cuenta cuantas canciones tiene un usuario en total a traves de todas sus playlists.
 * Pasos:
 *   1. Verifica que el usuario exista.
 *   2. Carga todas las playlists en un mapa (idPlaylist → idCreador).
 *   3. Recorre el archivo DetallePlaylist (relacion playlist-cancion).
 *   4. Por cada detalle activo, busca en el mapa si la playlist pertenece al usuario.
 * Parametros: Solicita el ID del usuario al usuario por consola.
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
 * Busqueda inteligente de una cancion en todas las playlists del sistema.
 * Permite busqueda PARCIAL por nombre (ej: "love" encuentra "Love Story" y "I Love Rock").
 * Pasos:
 *   1. Busca todas las canciones que contengan la subcadena buscada.
 *   2. Carga todas las playlists en mapas (nombre y creador, indexados por ID).
 *   3. Recorre DetallePlaylist para saber en que playlists aparece cada cancion coincidente.
 *   4. Muestra para cada cancion encontrada: en que playlists esta y quien las creo.
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
 * Genera el TOP 5 de canciones mas escuchadas de todos los tiempos.
 * Usa std::sort con una lambda que compara por cantidad de reproducciones (mayor a menor).
 * La lambda [&] captura los vectores por referencia para poder compararlos.
 *
 * Algoritmo:
 *   1. Carga todas las canciones en vectores de ids, nombres y contadores.
 *   2. Recorre todos los accesos (sin filtro de ano) e incrementa el contador.
 *   3. Crea un vector de indices y lo ordena segun los contadores.
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

/*
 * Informe completo de suscriptores.
 * Muestra ID, apellido, nombre, DNI, email, tipo de suscripcion y total de reproducciones.
 * Primero pre-indexa los accesos en un mapa para contar reproducciones en O(N),
 * luego imprime una fila por suscriptor activo.
 */
void ReporteManager::reporteUsuarios() {
    system("cls");
    cout << "--- INFORME DE SUSCRIPTORES ---" << endl << endl;

    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    unordered_map<int,int> reprosPorSuscriptor;
    for (int i = 0; i < totalAcc; i++) {
        a.Leer(i);
        reprosPorSuscriptor[a.getIdSuscriptor()]++;
    }

    ArchivoSuscriptores archS;
    int total = archS.ObtenerCantidadRegistros();

    cout << left
         << setw(5)  << "ID"
         << setw(20) << "Apellido"
         << setw(20) << "Nombre"
         << setw(15) << "DNI"
         << setw(30) << "Email"
         << setw(10) << "Tipo"
         << setw(8)  << "Repros"
         << endl;
    cout << string(108, '-') << endl;

    for (int i = 0; i < total; i++) {
        Suscriptor s = archS.Leer(i);
        if (!s.getEstado()) continue;

        int repros = 0;
        auto it = reprosPorSuscriptor.find(s.getIdSuscriptor());
        if (it != reprosPorSuscriptor.end()) repros = it->second;

        string tipo = (s.getTipoSuscriptor() == 2) ? "Pago" : "Gratis";

        cout << left
             << setw(5)  << s.getIdSuscriptor()
             << setw(20) << s.getApellido()
             << setw(20) << s.getNombre()
             << setw(15) << s.getDni()
             << setw(30) << s.getEmail()
             << setw(10) << tipo
             << setw(8)  << repros
             << endl;
    }
}

/*
 * Exporta el informe de suscriptores a un archivo CSV.
 * El archivo se llama "suscriptores_informe.csv" y se crea en el directorio de trabajo.
 * Formato: ID,Apellido,Nombre,DNI,Email,FechaNacimiento,Tipo,Reproducciones
 * Los campos con comas se encierran entre comillas para cumplir con el estandar CSV.
 */
void ReporteManager::exportarReporteSuscriptoresCSV() {
    Accesos a;
    int totalAcc = a.ObtenerCantidadRegistros();
    unordered_map<int,int> reprosPorSuscriptor;
    for (int i = 0; i < totalAcc; i++) {
        a.Leer(i);
        reprosPorSuscriptor[a.getIdSuscriptor()]++;
    }

    ofstream archivo("suscriptores_informe.csv");
    if (!archivo.is_open()) {
        cout << "Error: no se pudo crear el archivo CSV." << endl;
        return;
    }

    archivo << "ID,Apellido,Nombre,DNI,Email,FechaNacimiento,Tipo,Reproducciones" << endl;

    ArchivoSuscriptores archS;
    int total = archS.ObtenerCantidadRegistros();
    int exportados = 0;

    for (int i = 0; i < total; i++) {
        Suscriptor s = archS.Leer(i);
        if (!s.getEstado()) continue;

        int repros = 0;
        auto it = reprosPorSuscriptor.find(s.getIdSuscriptor());
        if (it != reprosPorSuscriptor.end()) repros = it->second;

        Fecha fn = s.getFechaNacimiento();
        string tipo = (s.getTipoSuscriptor() == 2) ? "Pago" : "Gratis";

        // Encerrar email entre comillas por si contiene comas
        archivo << s.getIdSuscriptor() << ","
                << s.getApellido() << ","
                << s.getNombre() << ","
                << s.getDni() << ","
                << "\"" << s.getEmail() << "\","
                << fn.getDia() << "/" << fn.getMes() << "/" << fn.getAnio() << ","
                << tipo << ","
                << repros << endl;
        exportados++;
    }

    archivo.close();
    cout << "Exportacion exitosa: " << exportados << " suscriptores guardados en 'suscriptores_informe.csv'." << endl;
}
