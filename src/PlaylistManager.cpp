/**
 * PATRON: Manager (capa de logica de negocio)
 * Esta clase orquesta el CRUD de playlists y la relacion muchos-a-muchos entre
 * suscriptores y canciones. No accede directamente al archivo — delega en
 * _archivoPlaylist (Repository) y usa DetallePlaylist para la tabla de relacion.
 *
 * Relacion muchos-a-muchos (M:N):
 *   - Una playlist puede tener muchas canciones.
 *   - Una cancion puede estar en muchas playlists.
 *   - La tabla de relacion (DetallePlaylist / Listas_Canciones.dat) guarda los pares
 *     (idPlaylist, idCancion) — igual que una tabla intermedia en SQL.
 *
 * Logica de negocio extra: control de plan
 *   - Suscriptores GRATUITOS (tipo=1) tienen maximo 3 playlists.
 *   - Si llegan al limite se les ofrece cambiar al plan PAGO (tipo=2).
 *   - Esta regla vive aqui (en el Manager) — no en el Repository, que ignora el negocio.
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

using namespace std;

/*
 * Busca el ID de una cancion por su nombre.
 * Parametros: nombre - Nombre de la cancion a buscar.
 * Retorno: ID de la cancion si existe y esta activa, -1 si no se encuentra.
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
 * Muestra el menu de gestion de playlists para un usuario especifico.
 * Parametros: idUsuario - ID del usuario que gestiona las playlists.
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
 * Muestra todas las playlists creadas por un usuario especifico.
 * Parametros: idUsuario - ID del usuario cuyas playlists mostrar.
 */
void PlaylistManager::MostrarMisPlaylists(int idUsuario) {
    int total = _archivoPlaylist.ObtenerCantidadRegistros();
    bool hay = false;

    cout << "--- MIS PLAYLISTS ---" << endl;
    for (int i = 0; i < total; i++) {
        Playlist p = _archivoPlaylist.Leer(i);
        if (p.getEstado() && p.getIdSuscriptorCreador() == idUsuario) {
            p.Mostrar();
            hay = true;
        }
    }

    if (!hay) {
        cout << "No tenes playlists creadas." << endl;
    }
}

/*
 * Crea una nueva playlist para un usuario especifico.
 * Genera ID unico, solicita datos y establece fecha de creacion actual.
 * Parametros: idUsuario - ID del usuario creador de la playlist.
 */
void PlaylistManager::CrearPlaylist(int idUsuario) {
	
	ArchivoSuscriptores archSus;

	int posSus = archSus.BuscarPosicion(idUsuario);

	// Logica de negocio: los usuarios GRATUITOS tienen un limite de 3 playlists
	if(posSus != -1){

		Suscriptor sus = archSus.Leer(posSus);

		if(sus.getTipoSuscriptor() == 1){ // 1 = GRATIS

			int totalPlaylists = _archivoPlaylist.ObtenerCantidadRegistros();

			int cantidadUsuario = 0;

			// Cuenta cuantas playlists activas tiene este usuario especifico
			for(int i = 0; i < totalPlaylists; i++){
				Playlist aux = _archivoPlaylist.Leer(i);
				if(aux.getEstado() && aux.getIdSuscriptorCreador() == idUsuario){
					cantidadUsuario++;
				}
			}

			if(cantidadUsuario >= 3){ // Limite alcanzado para plan GRATIS
				
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

	int id = _archivoPlaylist.GenerarIDNuevo();

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

	if (_archivoPlaylist.Guardar(p))
		cout << "   [OK] Playlist creada." << endl;
	else
		cout << "   [ERROR] No se pudo guardar la playlist." << endl;
}


/*
 * Modifica el nombre de una playlist existente del usuario.
 * Busca playlists por nombre parcial y permite seleccion si hay multiples.
 * Parametros: idUsuario - ID del usuario propietario de la playlist.
 */
void PlaylistManager::ModificarPlaylist(int idUsuario) {
    char nombreBuscado[50];
    InputHelper::pedirCadena("Nombre de la Playlist a modificar: ", nombreBuscado, 50);

    int total = _archivoPlaylist.ObtenerCantidadRegistros();
    int posicionesEncontradas[50];
    int cantidadEncontrados = 0;

    cout << endl << "--- SELECCION DE PLAYLIST ---" << endl;
    cout << "0. Cancelar" << endl;

    for (int i = 0; i < total; i++) {
        Playlist reg = _archivoPlaylist.Leer(i);
        if (reg.getEstado() &&
            reg.getIdSuscriptorCreador() == idUsuario &&
            InputHelper::contieneSubcadena(reg.getNombre(), nombreBuscado)) {

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

    int seleccion = InputHelper::pedirEnteroRango("Seleccione una opcion: ", 0, cantidadEncontrados);
    if (seleccion == 0) return;

    int pos = posicionesEncontradas[seleccion - 1];
    Playlist reg = _archivoPlaylist.Leer(pos);

    cout << endl << "--- EDITANDO: " << reg.getNombre() << " ---" << endl;
    char nuevoNombre[50];
    InputHelper::pedirCadena("Nuevo Nombre (Enter para mantener): ", nuevoNombre, 50);

    if (strlen(nuevoNombre) > 0) {
        reg.setNombre(nuevoNombre);
        if (_archivoPlaylist.Modificar(pos, reg)) cout << "   [OK] Playlist modificada." << endl;
        else cout << "   [ERROR] No se pudo modificar la playlist." << endl;
    }
}

/*
 * Elimina logicamente una playlist del usuario (estado=false).
 * Busca playlists del usuario que contengan el texto buscado (busqueda parcial).
 * Muestra una lista numerada para que el usuario elija cual eliminar.
 * Pide confirmacion antes de proceder. No borra del archivo — solo cambia estado.
 * Parametros: idUsuario - ID del usuario propietario de la playlist.
 */
void PlaylistManager::EliminarPlaylist(int idUsuario) {
    char nombreBuscado[50];
    InputHelper::pedirCadena("Nombre de la Playlist a eliminar: ", nombreBuscado, 50);

    int total = _archivoPlaylist.ObtenerCantidadRegistros();
    int posicionesEncontradas[50];
    int cantidadEncontrados = 0;

    cout << endl << "--- SELECCION PARA ELIMINAR ---" << endl;
    cout << "0. Cancelar" << endl;

    for (int i = 0; i < total; i++) {
        Playlist reg = _archivoPlaylist.Leer(i);
        if (reg.getEstado() &&
            reg.getIdSuscriptorCreador() == idUsuario &&
            InputHelper::contieneSubcadena(reg.getNombre(), nombreBuscado)) {

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

    int seleccion = InputHelper::pedirEnteroRango("Seleccione una opcion: ", 0, cantidadEncontrados);
    if (seleccion == 0) return;

    int pos = posicionesEncontradas[seleccion - 1];
    Playlist reg = _archivoPlaylist.Leer(pos);

    cout << endl << "Eliminaras: " << reg.getNombre() << endl;
    char confirm;
    cout << "Estas seguro? (s/n): ";
    cin >> confirm;
    cin.ignore(10000, '\n');

    if (confirm == 's' || confirm == 'S') {
        reg.setEstado(false);
        if (_archivoPlaylist.Modificar(pos, reg)) cout << "   [OK] Playlist eliminada." << endl;
        else cout << "   [ERROR] No se pudo eliminar la playlist." << endl;
    }
}

/*
 * Agrega una cancion a una playlist existente (relacion muchos-a-muchos).
 * La relacion se guarda en DetallePlaylist (Listas_Canciones.dat) — NO en la playlist en si.
 * Antes de agregar, verifica que la cancion no este ya en esa playlist (evita duplicados).
 *
 * Flujo:
 *   1. El usuario busca la playlist destino por nombre parcial.
 *   2. Se muestra una lista de coincidencias y el usuario elige una.
 *   3. El usuario escribe el nombre de la cancion a agregar.
 *   4. Se verifica que la cancion exista y no este ya en la lista.
 *   5. Se crea un DetallePlaylist con la fecha actual y se guarda.
 */
void PlaylistManager::AgregarCancionAPlaylist() {
    char nombrePlaylist[50];
    InputHelper::pedirCadena("Buscar Playlist destino: ", nombrePlaylist, 50);

    int total = _archivoPlaylist.ObtenerCantidadRegistros();
    int idsEncontrados[50];
    int cantidadEncontrados = 0;

    cout << endl << "--- RESULTADOS PLAYLISTS ---" << endl;
    cout << "0. Cancelar" << endl;

    ArchivoSuscriptores archSus;

    for (int i = 0; i < total; i++) {
        Playlist p = _archivoPlaylist.Leer(i);
        if (p.getEstado() && InputHelper::contieneSubcadena(p.getNombre(), nombrePlaylist)) {
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

    int seleccion = InputHelper::pedirEnteroRango("Seleccione una opcion: ", 0, cantidadEncontrados);
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
