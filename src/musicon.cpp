#include "musicon.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>

#include "Canciones.h"
#include "Suscriptor.h"
#include "Artista.h"
#include "Album.h"
#include "Generos.h"
#include "Accesos.h"
#include "DetallePlaylist.h"
#include "Listas.h"

using namespace std;

// Funcion auxiliar para sacar el año del sistema
int obtenerAnioActual() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_year + 1900;
}

musicon::musicon() {
    //ctor
    // Inicializamos con usuario visitante por defecto
    _idUsuarioLogueado = 0;
    strcpy(_nombreUsuarioLogueado, "Visitante");
}

musicon::~musicon() {
    //dtor
}

// Utilidad generica para calcular IDs autoincrementales leyendo el archivo
int obtenerNuevoIdGenerico(const char* archivo, int size) {
    FILE *p = fopen(archivo, "rb");
    if (p == NULL) return 1; // Si no existe, es el primero
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return (bytes / size) + 1;
}

// Wrappers para cada entidad
int musicon::obtenerNuevoIdCancion() { return obtenerNuevoIdGenerico("canciones.dat", sizeof(Canciones)); }
int musicon::obtenerNuevoIdSuscriptor() { return obtenerNuevoIdGenerico("suscriptores.dat", sizeof(Suscriptor)); }
int musicon::obtenerNuevoIdGenero() { return obtenerNuevoIdGenerico("generos.dat", sizeof(Genero)); }
int musicon::obtenerNuevoIdAlbum() { return obtenerNuevoIdGenerico("albumes.dat", sizeof(Album)); }
int musicon::obtenerNuevoIdArtista() { return obtenerNuevoIdGenerico("artistas.dat", sizeof(Artista)); }

// Buscador generico de usuarios
int musicon::buscarIdSuscriptorPorNombre(const char* nombreBuscado) {
    FILE *p = fopen("suscriptores.dat", "rb");
    if (p == NULL) return -1;
    Suscriptor reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Suscriptor), 1, p)) {
        // Comparamos sin importar mayusculas/minusculas
        if (stricmp(reg.getNombre(), nombreBuscado) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdSuscriptor();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

// ... (Resto de buscadores siguen la misma logica: abrir, recorrer, comparar, cerrar)

int musicon::buscarIdAlbumPorTitulo(const char* titulo) {
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return -1;
    Album reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Album), 1, p)) {
        if (stricmp(reg.getTitulo(), titulo) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdAlbum();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

int musicon::buscarIdGeneroPorNombre(const char* nombre) {
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return -1;
    Genero reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Genero), 1, p)) {
        if (stricmp(reg.getNombre(), nombre) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdGeneros();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

int musicon::buscarIdArtistaPorNombre(const char* nombre) {
    FILE *p = fopen("artistas.dat", "rb");
    if (p == NULL) return -1;
    Artista reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Artista), 1, p)) {
        if (stricmp(reg.getNombre(), nombre) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdArtista();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

int musicon::buscarIdPlaylistPorNombre(const char* nombre) {
    FILE *p = fopen("playlists.dat", "rb");
    if (p == NULL) return -1;
    Playlist reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Playlist), 1, p)) {
        if (stricmp(reg.getNombre(), nombre) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdPlaylist();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

int musicon::buscarIdCancionPorNombre(const char* nombre) {
    FILE *p = fopen("canciones.dat", "rb");
    if (p == NULL) return -1;
    Canciones reg;
    int idEncontrado = -1;
    while (fread(&reg, sizeof(Canciones), 1, p)) {
        if (stricmp(reg.getNombre(), nombre) == 0 && reg.getEstado()) {
            idEncontrado = reg.getIdCancion();
            break;
        }
    }
    fclose(p);
    return idEncontrado;
}

// Punto de entrada del sistema
void musicon::iniciarSistema() {
    menuBienvenida();
}

void musicon::menuBienvenida() {
    int opcion;
    do {
        system("cls");
        cout << "===========================================" << endl;
        cout << "           M  U  S  I  C  O  N             " << endl;
        cout << "===========================================" << endl;
        cout << "1. INICIAR SESION (Login)" << endl;
        cout << "2. REGISTRARSE (Sign Up)" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "0. SALIR DEL SISTEMA" << endl;
        cout << "===========================================" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;
        cin.ignore(10000, '\n'); // Limpiamos el buffer

        switch (opcion) {
            case 1: login(); break;
            case 2: registrarse(); break;
            case 0: cout << "Nos vemos!" << endl; break;
            default: cout << "Ingrese una opcion valida." << endl; system("pause"); break;
        }
    } while (opcion != 0);
}

void musicon::login() {
    char nombreUser[50];
    system("cls");
    cout << "--- LOGIN ---" << endl;
    cout << "Usuario: ";
    cin.getline(nombreUser, 50);

    // Verificamos si existe en el archivo
    int id = buscarIdSuscriptorPorNombre(nombreUser);

    if (id != -1) {
        // Login exitoso: guardamos el estado en memoria
        _idUsuarioLogueado = id;
        strcpy(_nombreUsuarioLogueado, nombreUser);
        cout << "Bienvenido de nuevo, " << _nombreUsuarioLogueado << "!" << endl;
        system("pause");
        mostrarMenuPrincipal();
        // Logout al volver
        _idUsuarioLogueado = 0;
        strcpy(_nombreUsuarioLogueado, "Visitante");
    } else {
        cout << "Usuario no encontrado. Registrate primero." << endl;
        system("pause");
    }
}

void musicon::registrarse() {
    char nombreUser[50];
    system("cls");
    cout << "--- REGISTRO ---" << endl;

    // Bucle para asegurar nombre unico
    while (true) {
        cout << "Usuario deseado: ";
        cin.getline(nombreUser, 50);
        if (buscarIdSuscriptorPorNombre(nombreUser) != -1) {
            cout << "[!] Ese nombre ya existe." << endl;
        } else { break; }
    }

    Suscriptor nuevo;
    int idAuto = obtenerNuevoIdSuscriptor();

    nuevo.setIdSuscriptor(idAuto);
    nuevo.setNombre(nombreUser);

    nuevo.Cargar();
    nuevo.setEstado(true);

    // Guardado append binario
    FILE *p = fopen("suscriptores.dat", "ab");
    if (p) {
        fwrite(&nuevo, sizeof(Suscriptor), 1, p);
        fclose(p);
        cout << endl << "Usuario creado! Tu ID es " << idAuto << "." << endl;
    } else {
        cout << "Error al guardar usuario." << endl;
    }
    system("pause");
}

void musicon::mostrarMenuPrincipal() {
    int opcion = -1;
    do {
        system("cls");
        cout << "MUSICON | User: " << _nombreUsuarioLogueado << " (ID: " << _idUsuarioLogueado << ")" << endl;
        cout << "1. GESTION DE DATOS (Cargas)" << endl;
        cout << "2. INFORMES Y ESTADISTICAS" << endl;
        cout << "3. CONFIGURACION (Backup / Export)" << endl;
        cout << "0. CERRAR SESION" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: menuCargas(); break;
            case 2: mostrarMenuReportes(); break;
            case 3: menuConfiguracion(); break;
            case 0: cout << "Cerrando sesion..." << endl; break;
            default: break;
        }
    } while (opcion != 0);
}

// ... (Resto de menus siguen estructura estandar) ...

void musicon::menuCargas() {
    int opcion;
    do {
        system("cls");
        cout << "--- CARGAS ---" << endl;
        cout << "1. CANCIONES (ABM)" << endl;
        cout << "2. Registrar Reproduccion (Acceso)" << endl;
        cout << "3. PLAYLISTS (ABM)" << endl;
        cout << "0. Volver" << endl;
        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: menuCanciones(); break;
            case 2: registrarAcceso(); break;
            case 3: menuPlaylists(); break;
            case 0: break;
        }
        if (opcion!=0) system("pause");
    } while (opcion != 0);
}

void musicon::menuCanciones() {
    int opcion;
    do {
        system("cls");
        cout << "--- CANCIONES ---" << endl;
        cout << "1. Subir Cancion" << endl;
        cout << "2. Modificar (Por nombre)" << endl;
        cout << "3. Eliminar (Por nombre)" << endl;
        cout << "4. Listar Todas" << endl;
        cout << "0. Volver" << endl;
        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: cargarNuevaCancionEnLista(); break;
            case 2: modificarCancion(); break;
            case 3: eliminarCancion(); break;
            case 4: listarCanciones(); break;
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void musicon::menuPlaylists() {
    int opcion;
    do {
        system("cls");
        cout << "--- PLAYLISTS ---" << endl;
        cout << "1. Crear Playlist" << endl;
        cout << "2. Modificar Playlist" << endl;
        cout << "3. Eliminar Playlist" << endl;
        cout << "4. Agregar Cancion a Playlist" << endl;
        cout << "5. MIS PLAYLISTS" << endl;
        cout << "0. Volver" << endl;
        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: cargarNuevaPlaylist(); break;
            case 2: modificarPlaylist(); break;
            case 3: eliminarPlaylist(); break;
            case 4: agregarCancionAPlaylist(); break;
            case 5: {
                Listas gestorListas;
                gestorListas.mostrarMisPlaylists(_idUsuarioLogueado);
                break;
            }
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

// --- LOGICA SMART ---

int musicon::crearAlbumRapido(const char* tituloAlbum) {
    // Funcion inteligente: Si subis una cancion de un album que no existe, te lo crea aca mismo
    cout << endl << "   >>> NUEVO ALBUM DETECTADO: " << tituloAlbum << " <<<" << endl;
    Album nuevo;
    int id = obtenerNuevoIdAlbum();
    nuevo.setIdAlbum(id);
    nuevo.setTitulo(tituloAlbum);

    char nombreArtista[100];
    cout << "   Artista del album: ";
    cin.getline(nombreArtista, 100);

    // Si el artista tampoco existe, lo creamos tambien
    int idArtista = buscarIdArtistaPorNombre(nombreArtista);
    if (idArtista == -1) {
        cout << "   [!] Artista nuevo. Creando perfil para '" << nombreArtista << "'..." << endl;
        idArtista = obtenerNuevoIdArtista();
        Artista nuevoArt;
        nuevoArt.setIdArtista(idArtista);
        nuevoArt.setNombre(nombreArtista);
        nuevoArt.setNacionalidad("Desconocida"); // Dato default
        nuevoArt.setEstado(true);
        FILE *p = fopen("artistas.dat", "ab");
        if(p) { fwrite(&nuevoArt, sizeof(Artista), 1, p); fclose(p); }
    }
    nuevo.setIdArtista(idArtista);

    int anio;
    cout << "   Anio de lanzamiento: "; cin >> anio;
    nuevo.setAnioPublicacion(anio);
    nuevo.setEstado(true);

    FILE *p = fopen("albumes.dat", "ab");
    if(p) { fwrite(&nuevo, sizeof(Album), 1, p); fclose(p); }

    cout << "   [OK] Album creado (ID " << id << ")." << endl;
    return id;
}

void musicon::cargarNuevaCancionEnLista() {
    cout << endl << "--- SUBIR CANCION ---" << endl;
    Canciones nueva;

    int id = obtenerNuevoIdCancion();
    nueva.setIdCancion(id);

    char nombre[100];
    cout << "Titulo de la cancion: "; cin.getline(nombre, 100);
    nueva.setNombre(nombre);

    // Logica de Album Smart
    char nombreAlbum[100];
    cout << "Album (Enter si es Single): "; cin.getline(nombreAlbum, 100);

    int idAlbum = 0;
    bool seCreoAlbum = false;

    if (strlen(nombreAlbum) > 0) {
        idAlbum = buscarIdAlbumPorTitulo(nombreAlbum);
        if (idAlbum == -1) {
            idAlbum = crearAlbumRapido(nombreAlbum);
            seCreoAlbum = true;
        }
    }
    nueva.setIdAlbum(idAlbum);

    if (seCreoAlbum) {
        cin.ignore(); // Limpiamos buffer si hubo entradas anidadas
    }

    // Logica de Genero Smart
    char nombreGenero[50];
    cout << "Genero (ej: Rock, Pop): ";
    cin.getline(nombreGenero, 50);

    int idGenero = buscarIdGeneroPorNombre(nombreGenero);
    if (idGenero == -1) {
        if (strlen(nombreGenero) > 0) {
            idGenero = obtenerNuevoIdGenero();
            cout << "   [!] Genero nuevo. Creando ID " << idGenero << "..." << endl;
            Genero g(idGenero, nombreGenero, true);
            FILE *p = fopen("generos.dat", "ab");
            if(p) { fwrite(&g, sizeof(Genero), 1, p); fclose(p); }
        } else {
            idGenero = 0; // Default: Desconocido
        }
    }
    nueva.setIdGenero(idGenero);

    int seg;
    cout << "Duracion (segundos): "; cin >> seg;
    nueva.setDuracionSegundos(seg);
    nueva.setEstado(true);

    FILE *p = fopen("canciones.dat", "ab");
    if(p) {
        fwrite(&nueva, sizeof(Canciones), 1, p);
        fclose(p);
        cout << "   [OK] Cancion guardada exitosamente." << endl;
    }
}

void musicon::modificarCancion() {
    char nombreBuscado[100];
    cout << "Nombre de la cancion a modificar: ";
    cin.getline(nombreBuscado, 100);

    // Modo r+b: lectura y escritura
    FILE *p = fopen("canciones.dat", "r+b");
    if(!p) { cout << "Error de archivo." << endl; return; }

    Canciones reg;
    bool encontrado = false;
    while(fread(&reg, sizeof(Canciones), 1, p)) {
        if(stricmp(reg.getNombre(), nombreBuscado) == 0 && reg.getEstado()) {
            encontrado = true;
            cout << endl << "--- CANCION ENCONTRADA ---" << endl;
            reg.Mostrar();

            cout << endl << "Ingrese los nuevos datos (Enter para mantener el actual):" << endl;

            char buffer[100];
            cout << "Nuevo Nombre [" << reg.getNombre() << "]: ";
            cin.getline(buffer, 100);
            if(strlen(buffer) > 0) reg.setNombre(buffer);

            int dur;
            cout << "Nueva Duracion [" << reg.getDuracionSegundos() << "]: ";
            char durStr[10];
            cin.getline(durStr, 10);
            if(strlen(durStr) > 0) {
                dur = atoi(durStr);
                if(dur > 0) reg.setDuracionSegundos(dur);
            }

            // Volvemos atras el puntero y sobreescribimos
            fseek(p, -(long)sizeof(Canciones), SEEK_CUR);
            fwrite(&reg, sizeof(Canciones), 1, p);
            cout << "   [OK] Cancion actualizada." << endl;
            break;
        }
    }

    if(!encontrado) cout << "No se encontro ninguna cancion con el nombre '" << nombreBuscado << "'." << endl;
    fclose(p);
}

void musicon::eliminarCancion() {
    char nombreBuscado[100];
    cout << "Nombre de la cancion a eliminar: ";
    cin.getline(nombreBuscado, 100);

    FILE *p = fopen("canciones.dat", "r+b");
    if(!p) { cout << "Error de archivo." << endl; return; }

    Canciones reg;
    bool encontrado = false;

    while(fread(&reg, sizeof(Canciones), 1, p)) {
        if(stricmp(reg.getNombre(), nombreBuscado) == 0 && reg.getEstado()) {
            encontrado = true;
            cout << endl << "Encontrada: "; reg.Mostrar();

            char confirm;
            cout << "Seguro que queres eliminarla? (s/n): ";
            cin >> confirm;

            if(confirm == 's' || confirm == 'S') {
                // Baja logica: cambiamos estado a false
                reg.setEstado(false);
                fseek(p, -(long)sizeof(Canciones), SEEK_CUR);
                fwrite(&reg, sizeof(Canciones), 1, p);
                cout << "   [OK] Cancion eliminada." << endl;
            } else {
                cout << "Operacion cancelada." << endl;
            }
            break;
        }
    }

    if(!encontrado) cout << "No se encontro '" << nombreBuscado << "'." << endl;
    fclose(p);
}

void musicon::listarCanciones() {
    FILE *p = fopen("canciones.dat", "rb"); if(!p) return;
    Canciones r;
    cout << "--- LISTADO ---" << endl;
    while(fread(&r, sizeof(Canciones), 1, p)) {
        if(r.getEstado()) r.Mostrar();
    }
    fclose(p);
}

void musicon::registrarAcceso() {
    char nombreCancion[100];
    cout << "Que cancion estas escuchando?: ";
    cin.getline(nombreCancion, 100);

    int idCancionEncontrada = buscarIdCancionPorNombre(nombreCancion);

    if (idCancionEncontrada == -1) {
        cout << "No encontramos esa cancion en el catalogo." << endl;
        return;
    }

    Accesos acc;
    acc.setIdSuscriptor(_idUsuarioLogueado);
    acc.setIdCancion(idCancionEncontrada);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    acc.setFechaHora(Fecha(ltm->tm_min, ltm->tm_hour, ltm->tm_mday, 1+ltm->tm_mon, 1900+ltm->tm_year));

    FILE *p = fopen("accesos.dat", "ab");
    if(p) { fwrite(&acc, sizeof(Accesos), 1, p); fclose(p); cout << "   [PLAY] Reproduciendo " << nombreCancion << "..." << endl; }
}

void musicon::cargarNuevaSuscripcion() { }

void musicon::cargarNuevaPlaylist() {
    Playlist p;

    // Buscamos el ultimo ID para autoincrementar manualmente
    FILE *f = fopen("playlists.dat", "rb");
    int id = 1;
    if (f) {
        fseek(f, 0, SEEK_END);
        if(ftell(f)>0) {
            fseek(f, -(long)sizeof(Playlist), SEEK_END);
            Playlist ult; fread(&ult, sizeof(Playlist), 1, f);
            id = ult.getIdPlaylist() + 1;
        }
        fclose(f);
    }
    p.setIdPlaylist(id);
    p.setIdSuscriptorCreador(_idUsuarioLogueado);

    char nom[50];
    cout << "Nombre de la Nueva Playlist: ";
    cin.getline(nom, 50);
    p.setNombre(nom);
    p.setEstado(true);

    f = fopen("playlists.dat", "ab");
    if(f) {
        fwrite(&p, sizeof(Playlist), 1, f);
        fclose(f);
        cout << "   [OK] Playlist '" << nom << "' creada exitosamente." << endl;
    }
}

void musicon::modificarPlaylist() {
    char nombreBuscado[50];
    cout << "Nombre de la Playlist a modificar: ";
    cin.getline(nombreBuscado, 50);

    FILE *p = fopen("playlists.dat", "r+b");
    if(!p) { cout << "No hay playlists." << endl; return; }

    Playlist reg;
    bool encontrado = false;
    while(fread(&reg, sizeof(Playlist), 1, p)) {
        if(stricmp(reg.getNombre(), nombreBuscado) == 0 && reg.getEstado()) {

            // Validacion de seguridad: solo el dueño edita
            if (reg.getIdSuscriptorCreador() != _idUsuarioLogueado) {
                cout << "   [!] No puedes modificar esta playlist porque no eres el creador." << endl;
                encontrado = true;
                break;
            }

            encontrado = true;
            cout << endl << "--- PLAYLIST ENCONTRADA ---" << endl;
            reg.Mostrar();

            char nuevoNombre[50];
            cout << "Nuevo Nombre (Enter para mantener): ";
            cin.getline(nuevoNombre, 50);

            if (strlen(nuevoNombre) > 0) {
                reg.setNombre(nuevoNombre);
                fseek(p, -(long)sizeof(Playlist), SEEK_CUR);
                fwrite(&reg, sizeof(Playlist), 1, p);
                cout << "   [OK] Playlist modificada." << endl;
            } else {
                cout << "   [!] Sin cambios." << endl;
            }
            break;
        }
    }
    if (!encontrado) cout << "No se encontro la playlist '" << nombreBuscado << "'." << endl;
    fclose(p);
}

void musicon::eliminarPlaylist() {
    char nombreBuscado[50];
    cout << "Nombre de la Playlist a eliminar: ";
    cin.getline(nombreBuscado, 50);

    FILE *p = fopen("playlists.dat", "r+b");
    if(!p) { cout << "No hay playlists." << endl; return; }

    Playlist reg;
    bool encontrado = false;
    while(fread(&reg, sizeof(Playlist), 1, p)) {
        if(stricmp(reg.getNombre(), nombreBuscado) == 0 && reg.getEstado()) {

            if (reg.getIdSuscriptorCreador() != _idUsuarioLogueado) {
                cout << "   [!] No puedes eliminar esta playlist porque no eres el creador." << endl;
                encontrado = true;
                break;
            }

            encontrado = true;
            cout << endl << "Encontrada: " << reg.getNombre() << endl;
            char confirm;
            cout << "Confirmar eliminacion? (s/n): "; cin >> confirm;

            if (confirm == 's' || confirm == 'S') {
                reg.setEstado(false);
                fseek(p, -(long)sizeof(Playlist), SEEK_CUR);
                fwrite(&reg, sizeof(Playlist), 1, p);
                cout << "   [OK] Playlist eliminada." << endl;
            }
            break;
        }
    }
    if (!encontrado) cout << "No se encontro la playlist." << endl;
    fclose(p);
}

void musicon::agregarCancionAPlaylist() {
    char nombrePlaylist[50];
    cout << "Nombre de la Playlist destino: ";
    cin.getline(nombrePlaylist, 50);

    int idLista = buscarIdPlaylistPorNombre(nombrePlaylist);
    if(idLista == -1) {
        cout << "   [!] Playlist no encontrada." << endl;
        return;
    }

    char nombreCancion[100];
    cout << "Nombre de la Cancion a agregar: ";
    cin.getline(nombreCancion, 100);

    int idCancion = buscarIdCancionPorNombre(nombreCancion);
    if(idCancion == -1) {
        cout << "   [!] Cancion no encontrada." << endl;
        return;
    }

    DetallePlaylist d;
    d.setIdPlaylist(idLista);
    d.setIdCancion(idCancion);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    d.setFechaAgregado(Fecha(0,0,ltm->tm_mday, 1+ltm->tm_mon, 1900+ltm->tm_year));
    d.setEstado(true);

    FILE *f = fopen("Listas_Canciones.dat", "ab");
    if(f) {
        fwrite(&d, sizeof(DetallePlaylist), 1, f);
        fclose(f);
        cout << "   [OK] Cancion '" << nombreCancion << "' agregada a '" << nombrePlaylist << "'." << endl;
    }
}

// --- REPORTES ---

void musicon::mostrarMenuReportes() {
    int op;
    do {
        system("cls");
        cout << "--- REPORTES ---" << endl;
        cout << "1. Reproducciones Anuales" << endl;
        cout << "2. Ranking Suscriptores" << endl;
        cout << "3. Ranking Generos" << endl;
        cout << "4. Ranking Canciones (TOP 5)" << endl;
        cout << "5. Listar por Genero" << endl;
        cout << "6. Cantidad x Artista" << endl;
        cout << "7. Canciones de Usuario en Listas" << endl;
        cout << "8. Buscar Cancion en Listas" << endl;
        cout << "0. Volver" << endl;
        cin >> op;
        cin.ignore(10000, '\n');

        switch(op){
            case 1: reporteReproduccionesAnuales(); break;
            case 2: reporteReproduccionesPorSuscriptor(); break;
            case 3: reporteReproduccionesPorGenero(); break;
            case 4: reporteRankingCanciones(); break;
            case 5: reporteListarCancionesPorGenero(); break;
            case 6: reporteCantidadCancionesPorArtista(); break;
            case 7: reporteCancionesPorUsuarioEnListas(); break;
            case 8: reporteBuscarCancionEnListas(); break;
        }
        if(op!=0) system("pause");
    } while(op!=0);
}

void musicon::reporteReproduccionesAnuales() {
    int anio; cout << "Anio: "; cin >> anio;
    int cont[12] = {0}; // Vector acumulador por mes
    FILE *p = fopen("accesos.dat", "rb"); if(!p) return;
    Accesos a;
    while(fread(&a, sizeof(Accesos), 1, p)){
        if(a.getFechaHora().getAnio() == anio) {
            int m = a.getFechaHora().getMes();
            if(m>=1 && m<=12) cont[m-1]++;
        }
    }
    fclose(p);
    cout << "Repros " << anio << ":" << endl;
    for(int i=0; i<12; i++) cout << "Mes " << i+1 << ": " << cont[i] << endl;
}

void musicon::reporteReproduccionesPorSuscriptor() {
    int anio; cout << "Anio (0=actual): "; cin >> anio;
    if(anio==0) anio = obtenerAnioActual();

    FILE *pS = fopen("suscriptores.dat", "rb"); if(!pS) return;
    Suscriptor s;
    while(fread(&s, sizeof(Suscriptor), 1, pS)) {
        if(s.getEstado()) {
            int c=0;
            // Recorremos accesos por cada usuario
            FILE *pA = fopen("accesos.dat", "rb");
            if(pA) {
                Accesos a;
                while(fread(&a, sizeof(Accesos), 1, pA)) {
                    if(a.getIdSuscriptor() == s.getIdSuscriptor() && a.getFechaHora().getAnio() == anio) c++;
                }
                fclose(pA);
            }
            if(c>0) cout << s.getNombre() << ": " << c << endl;
        }
    }
    fclose(pS);
}

void musicon::reporteReproduccionesPorGenero() {
    int anio; cout << "Anio (0=actual): "; cin >> anio;
    if(anio==0) anio = obtenerAnioActual();

    FILE *pG = fopen("generos.dat", "rb"); if(!pG) return;
    Genero g;
    // Doble corte de control implícito: Genero -> Cancion -> Acceso
    while(fread(&g, sizeof(Genero), 1, pG)) {
        int total = 0;
        FILE *pC = fopen("canciones.dat", "rb");
        if(pC) {
            Canciones c;
            while(fread(&c, sizeof(Canciones), 1, pC)) {
                if(c.getIdGenero() == g.getIdGeneros()) {
                    FILE *pA = fopen("accesos.dat", "rb");
                    if(pA) {
                        Accesos a;
                        while(fread(&a, sizeof(Accesos), 1, pA)) {
                            if(a.getIdCancion() == c.getIdCancion() && a.getFechaHora().getAnio() == anio) total++;
                        }
                        fclose(pA);
                    }
                }
            }
            fclose(pC);
        }
        if(total > 0) cout << g.getNombre() << ": " << total << endl;
    }
    fclose(pG);
}

void musicon::reporteReproduccionesPorCancion() {
    // Similar a los anteriores pero pivoteando por Cancion
    int anio; cout << "Anio: "; cin >> anio;
    FILE *pC = fopen("canciones.dat", "rb"); if(!pC) return;
    Canciones c;
    while(fread(&c, sizeof(Canciones), 1, pC)) {
        if(c.getEstado()) {
            int cnt = 0;
            FILE *pA = fopen("accesos.dat", "rb");
            if(pA) {
                Accesos a;
                while(fread(&a, sizeof(Accesos), 1, pA)) {
                    if(a.getIdCancion() == c.getIdCancion() && a.getFechaHora().getAnio() == anio) cnt++;
                }
                fclose(pA);
            }
            if(cnt>0) cout << c.getNombre() << ": " << cnt << endl;
        }
    }
    fclose(pC);
}

void musicon::reporteListarCancionesPorGenero() {
    char nom[50]; cout << "Genero: "; cin.ignore(); cin.getline(nom, 50);
    int idG = buscarIdGeneroPorNombre(nom);
    if(idG == -1) { cout << "No existe." << endl; return; }

    FILE *p = fopen("canciones.dat", "rb"); if(!p) return;
    Canciones c;
    while(fread(&c, sizeof(Canciones), 1, p)) {
        if(c.getIdGenero() == idG && c.getEstado()) {
            cout << "- " << c.getNombre() << endl;
        }
    }
    fclose(p);
}

void musicon::reporteCantidadCancionesPorArtista() {
    FILE *pArt = fopen("artistas.dat", "rb"); if(!pArt) return;
    Artista art;
    while(fread(&art, sizeof(Artista), 1, pArt)) {
        if(art.getEstado()) {
            int cant = 0;
            FILE *pAlb = fopen("albumes.dat", "rb");
            if(pAlb) {
                Album alb;
                while(fread(&alb, sizeof(Album), 1, pAlb)) {
                    if(alb.getIdArtista() == art.getIdArtista()) {
                        FILE *pC = fopen("canciones.dat", "rb");
                        if(pC) {
                            Canciones c;
                            while(fread(&c, sizeof(Canciones), 1, pC)) {
                                if(c.getIdAlbum() == alb.getIdAlbum() && c.getEstado()) cant++;
                            }
                            fclose(pC);
                        }
                    }
                }
                fclose(pAlb);
            }
            cout << art.getNombre() << ": " << cant << endl;
        }
    }
    fclose(pArt);
}

void musicon::reporteCancionesPorUsuarioEnListas() {
    int id; cout << "ID Usuario: "; cin >> id;
    if(!existeSuscriptor(id)) return;

    // Recorremos playlists del usuario y contamos las relaciones en detalle
    FILE *pL = fopen("playlists.dat", "rb"); if(!pL) return;
    Playlist l;
    int total = 0;
    while(fread(&l, sizeof(Playlist), 1, pL)) {
        if(l.getIdSuscriptorCreador() == id && l.getEstado()) {
            FILE *pD = fopen("Listas_Canciones.dat", "rb");
            if(pD) {
                DetallePlaylist d;
                while(fread(&d, sizeof(DetallePlaylist), 1, pD)) {
                    if(d.getIdPlaylist() == l.getIdPlaylist() && d.getEstado()) total++;
                }
                fclose(pD);
            }
        }
    }
    fclose(pL);
    cout << "Total canciones en sus playlists: " << total << endl;
}

void musicon::reporteBuscarCancionEnListas() {
    char nom[100]; cout << "Cancion: "; cin.ignore(); cin.getline(nom, 100);
    int idC = -1;
    FILE *pC = fopen("canciones.dat", "rb"); if(!pC) return;
    Canciones c;
    while(fread(&c, sizeof(Canciones), 1, pC)) {
        if(stricmp(c.getNombre(), nom)==0 && c.getEstado()) { idC = c.getIdCancion(); break; }
    }
    fclose(pC);

    if(idC == -1) { cout << "Cancion no encontrada." << endl; return; }

    cout << "Presente en Playlists:" << endl;
    FILE *pD = fopen("Listas_Canciones.dat", "rb"); if(!pD) return;
    DetallePlaylist d;
    while(fread(&d, sizeof(DetallePlaylist), 1, pD)) {
        if(d.getIdCancion() == idC && d.getEstado()) {
            FILE *pL = fopen("playlists.dat", "rb");
            if(pL) {
                Playlist l;
                while(fread(&l, sizeof(Playlist), 1, pL)) {
                    if(l.getIdPlaylist() == d.getIdPlaylist()) {
                        cout << "- " << l.getNombre() << endl;
                        break;
                    }
                }
                fclose(pL);
            }
        }
    }
    fclose(pD);
}

void musicon::menuConfiguracion() {
    int op = -1;
    do {
        system("cls");
        cout << "--- CONFIGURACION ---" << endl;
        cout << "1. Backup de Canciones (.bak)" << endl;
        cout << "2. Exportar Canciones a Excel (.csv)" << endl;
        cout << "0. Volver" << endl;
        cin >> op;
        cin.ignore(10000, '\n');

        if (op == 1) {
            cout << "Haciendo backup de canciones..." << endl;
            FILE *o = fopen("canciones.dat", "rb");
            FILE *d = fopen("canciones.bak", "wb");
            if(o && d) {
                Canciones c;
                while(fread(&c, sizeof(Canciones), 1, o)) fwrite(&c, sizeof(Canciones), 1, d);
                cout << "Backup listo." << endl;
            }
            if(o) fclose(o);
            if(d) fclose(d);
            system("pause");
        }
        else if (op == 2) {
            exportarCancionesACSV();
            system("pause");
        }
    } while (op != 0);
}

void musicon::exportarCancionesACSV() {
    FILE *p = fopen("canciones.dat", "rb");
    if (!p) {
        cout << "No se pudo abrir canciones.dat" << endl;
        return;
    }

    FILE *t = fopen("ListadoCanciones.csv", "wt");
    if (!t) {
        cout << "No se pudo crear el archivo CSV." << endl;
        fclose(p);
        return;
    }

    // Cabecera del CSV
    fprintf(t, "ID;Nombre;ID_Album;ID_Genero;Duracion(s)\n");

    Canciones c;
    while(fread(&c, sizeof(Canciones), 1, p)) {
        if (c.getEstado()) {
            fprintf(t, "%d;%s;%d;%d;%d\n",
                c.getIdCancion(),
                c.getNombre(),
                c.getIdAlbum(),
                c.getIdGenero(),
                c.getDuracionSegundos()
            );
        }
    }

    fclose(p);
    fclose(t);
    cout << "Exportacion exitosa! Busca el archivo 'ListadoCanciones.csv'." << endl;
}

void musicon::reporteRankingCanciones() {
    system("cls");
    cout << "--- RANKING DE CANCIONES MAS ESCUCHADAS ---" << endl;

    FILE *pC = fopen("canciones.dat", "rb");
    if (pC == NULL) {
        cout << "No se pudo abrir el archivo de canciones." << endl;
        return;
    }

    // Paso 1: Contar registros para vector dinamico
    int cantidadCanciones = 0;
    Canciones aux;
    while(fread(&aux, sizeof(Canciones), 1, pC)) {
        if (aux.getEstado()) {
            cantidadCanciones++;
        }
    }

    if (cantidadCanciones == 0) {
        cout << "No hay canciones cargadas." << endl;
        fclose(pC);
        return;
    }

    struct ItemRanking {
        int id;
        char nombre[100];
        int contador;
    };

    ItemRanking *vectorRanking = new ItemRanking[cantidadCanciones];

    // Paso 2: Cargar datos basicos al vector
    rewind(pC);
    int indice = 0;
    while(fread(&aux, sizeof(Canciones), 1, pC)) {
        if (aux.getEstado()) {
            vectorRanking[indice].id = aux.getIdCancion();
            strcpy(vectorRanking[indice].nombre, aux.getNombre());
            vectorRanking[indice].contador = 0;
            indice++;
        }
    }
    fclose(pC);

    // Paso 3: Leer historial y acumular en memoria
    FILE *pA = fopen("accesos.dat", "rb");
    if (pA != NULL) {
        Accesos acc;
        while(fread(&acc, sizeof(Accesos), 1, pA)) {
            for(int i = 0; i < cantidadCanciones; i++) {
                if (vectorRanking[i].id == acc.getIdCancion()) {
                    vectorRanking[i].contador++;
                    break;
                }
            }
        }
        fclose(pA);
    } else {
        cout << "[!] Advertencia: No hay historial de reproducciones." << endl;
    }

    // Paso 4: Ordenamiento Burbuja
    ItemRanking temp;
    for(int i = 0; i < cantidadCanciones - 1; i++) {
        for(int j = 0; j < cantidadCanciones - i - 1; j++) {
            if (vectorRanking[j].contador < vectorRanking[j+1].contador) {
                temp = vectorRanking[j];
                vectorRanking[j] = vectorRanking[j+1];
                vectorRanking[j+1] = temp;
            }
        }
    }

    cout << endl;
    cout << "PUESTO\tCANTIDAD\tTITULO" << endl;
    cout << "------------------------------------------" << endl;

    int tope = 5;
    if (cantidadCanciones < 5) tope = cantidadCanciones;

    for(int i = 0; i < tope; i++) {
        cout << "#" << i+1 << "\t" << vectorRanking[i].contador << "\t\t" << vectorRanking[i].nombre << endl;
    }

    delete[] vectorRanking;
}

// Implementacion de helpers de existencia
bool musicon::existeCancion(int id) {
    FILE *p = fopen("canciones.dat", "rb"); if(!p) return false;
    Canciones r; bool x=false;
    while(fread(&r, sizeof(Canciones), 1, p)) if(r.getIdCancion()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
bool musicon::existeSuscriptor(int id) {
    FILE *p = fopen("suscriptores.dat", "rb"); if(!p) return false;
    Suscriptor r; bool x=false;
    while(fread(&r, sizeof(Suscriptor), 1, p)) if(r.getIdSuscriptor()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
bool musicon::existeArtista(int id) {
    FILE *p = fopen("artistas.dat", "rb"); if(!p) return false;
    Artista r; bool x=false;
    while(fread(&r, sizeof(Artista), 1, p)) if(r.getIdArtista()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
bool musicon::existeAlbum(int id) {
    FILE *p = fopen("albumes.dat", "rb"); if(!p) return false;
    Album r; bool x=false;
    while(fread(&r, sizeof(Album), 1, p)) if(r.getIdAlbum()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
bool musicon::existeGenero(int id) {
    FILE *p = fopen("generos.dat", "rb"); if(!p) return false;
    Genero r; bool x=false;
    while(fread(&r, sizeof(Genero), 1, p)) if(r.getIdGeneros()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
bool musicon::existeLista(int id) {
    FILE *p = fopen("playlists.dat", "rb"); if(!p) return false;
    Playlist r; bool x=false;
    while(fread(&r, sizeof(Playlist), 1, p)) if(r.getIdPlaylist()==id && r.getEstado()) { x=true; break; }
    fclose(p); return x;
}
