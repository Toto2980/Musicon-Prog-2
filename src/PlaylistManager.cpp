/**
 * Este archivo implementa la clase PlaylistManager. Gestiona las playlists de usuarios,
 * incluyendo creación, modificación, eliminación y gestión de canciones en playlists.
 * Maneja la relación muchos-a-muchos entre usuarios y canciones.
 */

#include "../include/PlaylistManager.h"
#include "../include/InputHelper.h"
#include "../include/ArchivoCanciones.h"
#include "../include/ArchivoSuscriptores.h"
#include "../include/Canciones.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;

/**
 * Función helper local para verificar si un texto contiene una subcadena, ignorando mayúsculas/minúsculas.
 * Parámetros: texto - Texto donde buscar, busqueda - Subcadena a buscar.
 * Retorna: true si encuentra la subcadena.
 */
static bool contieneSubcadenaLocal(const char* texto, const char* busqueda) {
    string t = texto;
    string b = busqueda;
    for (auto& c : t) c = tolower(c); // Convierte a minúsculas
    for (auto& c : b) c = tolower(c);
    return t.find(b) != string::npos; // Busca la subcadena
}

/*
 * Busca el ID de una canción por su nombre.
 * Parámetros: nombre - Nombre de la canción a buscar.
 * Retorno: ID de la canción si existe y está activa, -1 si no se encuentra.
 */
int PlaylistManager::buscarIdCancionPorNombre(const char* nombre) {
    ArchivoCanciones arch;
    int total = arch.ObtenerCantidadRegistros();
    for (int i = 0; i < total; i++) { // Busca linealmente
        Canciones c = arch.Leer(i);
        if (InputHelper::sonIgualesSinMayusculas(c.getNombre(), nombre) && c.getEstado()) {
            return c.getIdCancion();
        }
    }
    return -1;
}

/*
 * Muestra el menú de gestión de playlists para un usuario específico.
 * Parámetros: idUsuario - ID del usuario que gestiona las playlists.
 */
void PlaylistManager::MostrarMenu(int idUsuario) {
    int opcion;
    do {
        system("cls");
        cout << "--- PLAYLISTS ---\n";
        cout << "1. Mis Playlists\n";
        cout << "2. Crear Playlist\n";
        cout << "3. Modificar Playlist\n";
        cout << "4. Eliminar Playlist\n";
        cout << "5. Agregar Cancion a Playlist\n";
        cout << "0. Volver\n";
        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 5);
        switch (opcion) {
            case 1: MostrarMisPlaylists(idUsuario); break;
            case 2: CrearPlaylist(idUsuario); break;
            case 3: ModificarPlaylist(idUsuario); break;
            case 4: EliminarPlaylist(idUsuario); break;
            case 5: AgregarCancionAPlaylist(); break;
        }
    } while (opcion != 0);
}

/*
 * Muestra todas las playlists creadas por un usuario específico.
 * Parámetros: idUsuario - ID del usuario cuyas playlists mostrar.
 */
void PlaylistManager::MostrarMisPlaylists(int idUsuario) {
    Playlist p;
    int total = p.ObtenerCantidadRegistros();
    bool hay = false;

    cout << "--- MIS PLAYLISTS ---" << endl;
    for (int i = 0; i < total; i++) { // Itera sobre todas las playlists
        if (!p.Leer(i)) continue; // Salta si no se puede leer
        if (p.getEstado() && p.getIdSuscriptorCreador() == idUsuario) { // Filtra por usuario y estado
            p.Mostrar(); // Muestra la playlist
            hay = true;
        }
    }

    if (!hay) {
        cout << "No tenes playlists creadas." << endl;
    }
}

/*
 * Crea una nueva playlist para un usuario específico.
 * Genera ID único, solicita datos y establece fecha de creación actual.
 * Parámetros: idUsuario - ID del usuario creador de la playlist.
 */
void PlaylistManager::CrearPlaylist(int idUsuario) {

    ArchivoSuscriptores archSus;

    int posSus = archSus.BuscarPosicion(idUsuario);

    if(posSus != -1){

        Suscriptor sus = archSus.Leer(posSus);

        if(sus.getTipoSuscriptor() == 1){

            Playlist aux;

            int totalPlaylists =
                aux.ObtenerCantidadRegistros();

            int cantidadUsuario = 0;

            for(int i = 0; i < totalPlaylists; i++){

                if(!aux.Leer(i)) continue;

                if(aux.getEstado() &&
                   aux.getIdSuscriptorCreador() == idUsuario){

                    cantidadUsuario++;
                }
            }

            if(cantidadUsuario >= 3){

                cout << endl;
                cout << "==================================" << endl;
                cout << "PLAN GRATUITO" << endl;
                cout << "==================================" << endl;
                cout << endl;

                cout << "Has alcanzado el limite de 3 playlists."
                     << endl << endl;

                cout << "1. Suscribirme al plan PAGO" << endl;
                cout << "2. Omitir" << endl;

                int op =
                InputHelper::pedirEnteroRango(
                    "Opcion: ",
                    1,
                    2
                );

                if(op == 1){

                    sus.setTipoSuscriptor(2);

                    archSus.Modificar(
                        posSus,
                        sus
                    );

                    cout << endl;
                    cout << "Ahora sos usuario PAGO."
                         << endl << endl;
                }
                else{

                    cout << endl;
                    cout << "Operacion cancelada."
                         << endl;

                    return;
                }
            }
        }
    }

    Playlist p;

    int id = p.GenerarIDNuevo();

    p.setIdPlaylist(id);

    p.setIdSuscriptorCreador(idUsuario);

    p.Cargar();

    time_t now = time(0);

    tm *ltm = localtime(&now);

    p.setFechaCreacion(
        Fecha(
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year
        )
    );

    p.setEstado(true);

    if (p.Guardar())
        cout << "   [OK] Playlist creada." << endl;
    else
        cout << "   [ERROR] No se pudo guardar la playlist." << endl;
}

/*
 * Modifica el nombre de una playlist existente del usuario.
 * Busca playlists por nombre parcial y permite selección si hay múltiples.
 * Parámetros: idUsuario - ID del usuario propietario de la playlist.
 */
void PlaylistManager::ModificarPlaylist(int idUsuario) {
    char nombreBuscado[50];
    InputHelper::pedirCadena("Nombre de la Playlist a modificar: ", nombreBuscado, 50); // Solicita nombre a buscar

    Playlist reg;
    int total = reg.ObtenerCantidadRegistros();
    int posicionesEncontradas[50]; // Almacena posiciones encontradas
    int cantidadEncontrados = 0;

    cout << endl << "--- SELECCION DE PLAYLIST ---" << endl;
    cout << "0. Cancelar" << endl;

    for (int i = 0; i < total; i++) { // Busca playlists que coincidan
        if (!reg.Leer(i)) continue;
        if (reg.getEstado() &&
            reg.getIdSuscriptorCreador() == idUsuario &&
            contieneSubcadenaLocal(reg.getNombre(), nombreBuscado)) { // Filtra por usuario y nombre

            if (cantidadEncontrados < 50) {
                posicionesEncontradas[cantidadEncontrados] = i; // Guarda posición
                cout << (cantidadEncontrados + 1) << ". " << reg.getNombre()
                     << " (ID: " << reg.getIdPlaylist() << ")" << endl;
                cantidadEncontrados++;
            }
        }
    }

    if (cantidadEncontrados == 0) { // Si no se encontraron
        cout << "No se encontraron playlists tuyas con ese nombre." << endl;
        InputHelper::pausa();
        return;
    }

    int seleccion = InputHelper::pedirOpcionDeLista(cantidadEncontrados); // Selecciona playlist
    if (seleccion == 0) return;

    int pos = posicionesEncontradas[seleccion - 1]; // Obtiene posición seleccionada
    reg.Leer(pos);

    cout << endl << "--- EDITANDO: " << reg.getNombre() << " ---" << endl;
    char nuevoNombre[50];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", nuevoNombre, 50); // Nuevo nombre

    if (strlen(nuevoNombre) > 0) { // Si se específico nuevo nombre
        reg.setNombre(nuevoNombre);
        if (reg.Modificar(pos)) cout << "   [OK] Playlist modificada." << endl; // Modifica
        else cout << "   [ERROR] No se pudo modificar la playlist." << endl;
    }
}

void PlaylistManager::EliminarPlaylist(int idUsuario) {
    char nombreBuscado[50];
    InputHelper::pedirCadena("Nombre de la Playlist a eliminar: ", nombreBuscado, 50);

    Playlist reg;
    int total = reg.ObtenerCantidadRegistros();
    int posicionesEncontradas[50];
    int cantidadEncontrados = 0;

    cout << endl << "--- SELECCION PARA ELIMINAR ---" << endl;
    cout << "0. Cancelar" << endl;

    for (int i = 0; i < total; i++) {
        if (!reg.Leer(i)) continue;
        if (reg.getEstado() &&
            reg.getIdSuscriptorCreador() == idUsuario &&
            contieneSubcadenaLocal(reg.getNombre(), nombreBuscado)) {

            if (cantidadEncontrados < 50) {
                posicionesEncontradas[cantidadEncontrados] = i;
                cout << (cantidadEncontrados + 1) << ". " << reg.getNombre()
                     << " (ID: " << reg.getIdPlaylist() << ")" << endl;
                cantidadEncontrados++;
            }
        }
    }

    if (cantidadEncontrados == 0) {
        cout << "No se encontraron playlists tuyas con ese nombre." << endl;
        InputHelper::pausa();
        return;
    }

    int seleccion = InputHelper::pedirOpcionDeLista(cantidadEncontrados);
    if (seleccion == 0) return;

    int pos = posicionesEncontradas[seleccion - 1];
    reg.Leer(pos);

    cout << endl << "Eliminaras: " << reg.getNombre() << endl;
    char confirm;
    cout << "Estas seguro? (s/n): ";
    cin >> confirm;
    cin.ignore(10000, '\n');

    if (confirm == 's' || confirm == 'S') {
        reg.setEstado(false);
        if (reg.Modificar(pos)) cout << "   [OK] Playlist eliminada." << endl;
        else cout << "   [ERROR] No se pudo eliminar la playlist." << endl;
    }
}

void PlaylistManager::AgregarCancionAPlaylist() {
    char nombrePlaylist[50];
    InputHelper::pedirCadena("Buscar Playlist destino: ", nombrePlaylist, 50);

    Playlist p;
    int total = p.ObtenerCantidadRegistros();
    int idsEncontrados[50];
    int cantidadEncontrados = 0;

    cout << endl << "--- RESULTADOS PLAYLISTS ---" << endl;
    cout << "0. Cancelar" << endl;

    ArchivoSuscriptores archSus;

    for (int i = 0; i < total; i++) {
        if (!p.Leer(i)) continue;
        if (p.getEstado() && contieneSubcadenaLocal(p.getNombre(), nombrePlaylist)) {
            if (cantidadEncontrados < 50) {
                idsEncontrados[cantidadEncontrados] = p.getIdPlaylist();

                int posCreador = archSus.BuscarPosicion(p.getIdSuscriptorCreador());
                string nombreCreador = "Desconocido";
                if (posCreador != -1) {
                    Suscriptor s = archSus.Leer(posCreador);
                    nombreCreador = s.getNombre();
                }

                cout << (cantidadEncontrados + 1) << ". " << p.getNombre()
                     << " (Creador: " << nombreCreador << ")"
                     << " - Fecha: " << p.getFechaCreacion().toString() << endl;
                cantidadEncontrados++;
            }
        }
    }

    if (cantidadEncontrados == 0) {
        cout << "No se encontraron playlists." << endl;
        InputHelper::pausa();
        return;
    }

    int seleccion = InputHelper::pedirOpcionDeLista(cantidadEncontrados);
    if (seleccion == 0) return;

    int idListaDestino = idsEncontrados[seleccion - 1];
    char nombreCancion[100];
    InputHelper::pedirCadena("Nombre de la Cancion a agregar: ", nombreCancion, 100);

    int idCancion = buscarIdCancionPorNombre(nombreCancion);
    if (idCancion == -1) {
        cout << "   [!] Cancion no encontrada." << endl;
        return;
    }

    DetallePlaylist d;
    if (d.BuscarCancionEnPlaylist(idListaDestino, idCancion) != -1) {
        cout << "   [!] La cancion ya esta en esa lista." << endl;
        return;
    }

    d.setIdPlaylist(idListaDestino);
    d.setIdCancion(idCancion);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    d.setFechaAgregado(Fecha(ltm->tm_mday, 1+ltm->tm_mon, 1900+ltm->tm_year));
    d.setEstado(true);

    if (d.Guardar()) cout << "   [OK] Cancion agregada a la playlist." << endl;
    else cout << "   [ERROR] No se pudo agregar la cancion." << endl;
}
