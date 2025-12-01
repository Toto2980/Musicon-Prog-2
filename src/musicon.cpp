#include "musicon.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>

// Incluimos las cabeceras de las clases
#include "Canciones.h"
#include "Suscriptor.h"
#include "Artista.h"
#include "Album.h"
#include "Generos.h"
#include "Accesos.h"

using namespace std;

// --- CONSTRUCTOR Y DESTRUCTOR ---

musicon::musicon() {
    //ctor
}

musicon::~musicon() {
    //dtor
}

// --- MENÚ PRINCIPAL Y DE CARGAS (Lógica completa) ---

void musicon::mostrarMenuPrincipal() {
    int opcion;
    do {
        system("cls"); // Limpia pantalla (en Windows)
        cout << "===========================================" << endl;
        cout << "      SISTEMA DE GESTION MUSICON" << endl;
        cout << "===========================================" << endl;
        cout << "1. GESTION DE DATOS (Cargas)" << endl;
        cout << "2. INFORMES Y ESTADISTICAS" << endl;
        cout << "3. CONFIGURACION (Copias de Seguridad)" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "0. SALIR" << endl;
        cout << "===========================================" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;



        switch (opcion) {
            case 1:
                menuCargas();
                break;
            case 2:
                mostrarMenuReportes();
                break;
            case 3:
                menuConfiguracionprotected();
                break;
            case 0:
                cout << "Gracias por usar Musicon." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
                break;
        }
        if (opcion != 0) {
            cout << endl;
            system("pause");
        }
    } while (opcion != 0);
}

void musicon::menuCargas() {
    int opcion;
    do {
        system("cls");
        cout << "--- MENU DE CARGAS ---" << endl;
        cout << "1. GESTION DE CANCIONES (ABM)" << endl;
        cout << "2. Nuevo Suscriptor" << endl;
        cout << "3. Registrar Acceso (Simular Reproduccion)" << endl;
        cout << "4. GESTION DE PLAYLISTS (ABM)" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "----------------------" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        cin.ignore(10000, '\n');


        switch (opcion) {
            case 1:
                cargarNuevaCancionEnLista();
                break;
            case 2:
                cargarNuevaSuscripcion();
                break;
            case 3:
                registrarAcceso();
                break;
            case 4:
                menuPlaylists();
                break;
            case 0:
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void musicon::menuCanciones() {
    int opcion;
    do {
        system("cls");
        cout << "--- GESTION DE CANCIONES ---" << endl;
        cout << "1. Agregar Nueva Cancion" << endl;
        cout << "2. Modificar Cancion" << endl;
        cout << "3. Eliminar Cancion (Baja Logica)" << endl;
        cout << "0. Volver" << endl;
        cout << "----------------------------" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarNuevaCancionEnLista();
                break;
            case 2:
                modificarCancion();
                break;
            case 3:
                eliminarCancion();
                break;
            case 0:
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void musicon::modificarCancion() {
    int idBuscado;
    cout << "Ingrese el ID de la cancion a modificar: ";
    cin >> idBuscado;

    // Abrimos en modo lectura/escritura binaria ("r+b")
    // "r+" permite leer y escribir sin borrar el archivo existente
    FILE *p = fopen("canciones.dat", "r+b");
    if (p == NULL) {
        cout << "Error al abrir el archivo canciones.dat" << endl;
        return;
    }

    Canciones reg;
    bool encontrado = false;

    // Leemos registro por registro
    while (fread(&reg, sizeof(Canciones), 1, p) == 1) {
        if (reg.getIdCancion() == idBuscado && reg.getEstado() == true) {
            encontrado = true;
            cout << endl << "--- CANCION ENCONTRADA ---" << endl;
            reg.Mostrar(); // Mostramos la info actual
            
            cout << endl << "--- INGRESE NUEVOS DATOS ---" << endl;
            // Aquí podrías hacer setters específicos si no quieres cambiar el ID
            // Por ejemplo:
            char nuevoNombre[100];
            int nuevoAlbum, nuevoGenero, nuevaDuracion;
            
            cin.ignore(); 
            cout << "Nuevo Nombre: ";
            cin.getline(nuevoNombre, 100);
            
            cout << "Nuevo ID Album: ";
            cin >> nuevoAlbum;
            
            cout << "Nuevo ID Genero: ";
            cin >> nuevoGenero;
            
            cout << "Nueva Duracion: ";
            cin >> nuevaDuracion;

            // Actualizamos el objeto en memoria
            reg.setNombre(nuevoNombre);
            reg.setIdAlbum(nuevoAlbum);
            reg.setIdGenero(nuevoGenero);
            reg.setDuracionSegundos(nuevaDuracion);
            
            // IMPORTANTE: Retroceder el cursor del archivo para sobrescribir
            // fseek mueve el cursor desde la posición actual (SEEK_CUR) hacia atrás
            fseek(p, -sizeof(Canciones), SEEK_CUR);
            
            // Escribimos el registro modificado
            fwrite(&reg, sizeof(Canciones), 1, p);
            
            cout << "Cancion modificada exitosamente." << endl;
            break; // Salimos del while
        }
    }

    if (!encontrado) {
        cout << "No se encontro una cancion activa con ese ID." << endl;
    }

    fclose(p);
}

void musicon::eliminarCancion() {
    int idBuscado;
    cout << "Ingrese el ID de la cancion a eliminar: ";
    cin >> idBuscado;

    FILE *p = fopen("canciones.dat", "r+b");
    if (p == NULL) {
        cout << "Error al abrir el archivo canciones.dat" << endl;
        return;
    }

    Canciones reg;
    bool encontrado = false;

    while (fread(&reg, sizeof(Canciones), 1, p) == 1) {
        if (reg.getIdCancion() == idBuscado && reg.getEstado() == true) {
            encontrado = true;
            reg.Mostrar();
            
            char confirma;
            cout << "Esta seguro de eliminar esta cancion? (s/n): ";
            cin >> confirma;

            if (confirma == 's' || confirma == 'S') {
                // BAJA LÓGICA: Solo cambiamos el estado a false
                reg.setEstado(false);

                // Retrocedemos y sobrescribimos
                fseek(p, -sizeof(Canciones), SEEK_CUR);
                fwrite(&reg, sizeof(Canciones), 1, p);
                
                cout << "Cancion eliminada (baja logica) correctamente." << endl;
            } else {
                cout << "Operacion cancelada." << endl;
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro una cancion activa con ese ID." << endl;
    }

    fclose(p);
}

void musicon::menuPlaylists() {
    int opcion;
    do {
        system("cls");
        cout << "--- GESTION DE PLAYLISTS ---" << endl;
        cout << "1. Crear Nueva Playlist" << endl;
        cout << "2. Modificar Playlist" << endl;
        cout << "3. Eliminar Playlist (Baja Logica)" << endl;
        cout << "0. Volver" << endl;
        cout << "---------------------------" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: cargarNuevaPlaylist(); break;
            case 2: modificarPlaylist(); break;
            case 3: eliminarPlaylist(); break;
            case 0: break;
            default: cout << "Opcion incorrecta." << endl;
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void musicon::mostrarMenuReportes() {
    int opcion;
    do {
        system("cls");
        cout << "--- INFORMES Y ESTADISTICAS ---" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "1. Reproducciones anuales" << endl;
        cout << "2. Reproducciones por suscriptor" << endl;
        cout << "3. Cantidad de reproducciones por genero" << endl;
        cout << "4. Reproducciones por cancion" << endl;
        cout << "5. Listar canciones de un genero" << endl;
        cout << "6. Cantidad de canciones por artista" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "0. Volver" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: reporteReproduccionesAnuales(); break;
            case 2: reporteReproduccionesPorSuscriptor(); break;
            case 3: reporteReproduccionesPorGenero(); break;
            case 4: reporteReproduccionesPorCancion(); break;
            case 5: reporteListarCancionesPorGenero(); break;
            case 6: reporteCantidadCancionesPorArtista(); break;
            case 0: break;
            default: cout << "Opcion incorrecta." << endl;
        }
        if(opcion != 0) system("pause");
    } while(opcion != 0);
}

// --- FUNCIONES DE CARGA Y CONFIGURACIÓN ---

void musicon::cargarNuevaCancionEnLista() {
    cout << endl << "--- CARGAR NUEVA CANCION ---" << endl;
    Canciones nuevaCancion;
    nuevaCancion.Cargar();

    if (nuevaCancion.getEstado()) {
        FILE *p = fopen("canciones.dat", "ab");
        if (p == NULL) {
            cout << "Error al abrir el archivo canciones.dat" << endl;
            return;
        }
        fwrite(&nuevaCancion, sizeof(Canciones), 1, p);
        fclose(p);
        cout << "Cancion guardada exitosamente!" << endl;
    }
}

void musicon::cargarNuevaSuscripcion() {
    cout << endl << "--- CARGAR NUEVO SUSCRIPTOR ---" << endl;
    Suscriptor nuevoSus;
    nuevoSus.Cargar();

    if (nuevoSus.getEstado()) {
        FILE *p = fopen("suscriptores.dat", "ab");
        if (p == NULL) {
            cout << "Error al abrir el archivo suscriptores.dat" << endl;
            return;
        }
        fwrite(&nuevoSus, sizeof(Suscriptor), 1, p);
        fclose(p);
        cout << "Suscriptor registrado exitosamente!" << endl;
    }
}

void musicon::cargarNuevoAcceso() {
    cout << endl << "--- REGISTRAR NUEVO ACCESO ---" << endl;

    // Usamos la clase Accesos
    Accesos nuevoAcceso;

    // Esta función ya la programe en Accesos.cpp, pedirá ID Suscriptor, ID Canción y Fecha
    nuevoAcceso.Cargar();

    // Guardamos en el archivo accesos.dat
    FILE *p = fopen("accesos.dat", "ab");
    if (p == NULL) {
        cout << "Error al abrir el archivo accesos.dat" << endl;
        return;
    }

    // Escribimos el registro
    fwrite(&nuevoAcceso, sizeof(Accesos), 1, p);
    fclose(p);

    cout << "Reproduccion registrada exitosamente!" << endl;
}


void musicon::menuConfiguracion() {
    cout << endl << "--- CONFIGURACION / BACKUP ---" << endl;
    cout << "Creando copia de seguridad de canciones..." << endl;
    FILE *origen = fopen("canciones.dat", "rb");
    FILE *destino = fopen("canciones.bak", "wb");
    if (origen && destino) {
        Canciones reg;
        while(fread(&reg, sizeof(Canciones), 1, origen)) fwrite(&reg, sizeof(Canciones), 1, destino);
        cout << "Backup creado: canciones.bak" << endl;
    }
    if (origen) fclose(origen);
    if (destino) fclose(destino);
}

// --- HERRAMIENTAS AUXILIARES ---

int musicon::contarRegistros(const char* nombreArchivo, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / tamanioRegistro;
}

int obtenerAnioActual() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_year + 1900;
}

// --- REPORTES (IMPLEMENTACIÓN COMPLETA CON MEMORIA DINÁMICA) ---

void musicon::reporteReproduccionesAnuales() {
    int anio;
    cout << "INGRESE ANIO: ";
    cin >> anio;

    int contadores[12] = {0};
    const char* nombresMeses[12] = {"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO",
                                    "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"};

    int cantAccesos = contarRegistros("accesos.dat", sizeof(Accesos));
    if (cantAccesos == 0) { cout << "No hay accesos." << endl; return; }

    Accesos* vAccesos = new Accesos[cantAccesos];
    FILE *p = fopen("accesos.dat", "rb");
    if (p) { fread(vAccesos, sizeof(Accesos), cantAccesos, p); fclose(p); }

    for (int i = 0; i < cantAccesos; i++) {
        if (vAccesos[i].getFechaHora().getAnio() == anio) {
            int mes = vAccesos[i].getFechaHora().getMes();
            if (mes >= 1 && mes <= 12) contadores[mes - 1]++;
        }
    }
    delete[] vAccesos;

    cout << endl << "REPRODUCCIONES DEL AO " << anio << endl;
    cout << "MES\t\tREPRODUCCIONES" << endl;
    for (int i = 0; i < 12; i++) cout << nombresMeses[i] << "\t\t" << contadores[i] << endl;
}

void musicon::reporteReproduccionesPorSuscriptor() {
    int anio;
    cout << "INGRESE ANIO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    int cantSus = contarRegistros("suscriptores.dat", sizeof(Suscriptor));
    Suscriptor* vSus = new Suscriptor[cantSus];
    FILE *pSus = fopen("suscriptores.dat", "rb");
    if (pSus) { fread(vSus, sizeof(Suscriptor), cantSus, pSus); fclose(pSus); }
    else { delete[] vSus; return; }

    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];
    FILE *pAcc = fopen("accesos.dat", "rb");
    if (pAcc) { fread(vAcc, sizeof(Accesos), cantAcc, pAcc); fclose(pAcc); }

    cout << endl << "REPRODUCCIONES POR SUSCRIPTOR (" << anio << ")" << endl;
    cout << "APELLIDO\tNOMBRE\t\tTOTAL" << endl;

    for (int i = 0; i < cantSus; i++) {
        if (vSus[i].getEstado()) {
            int idSus = vSus[i].getIdSuscriptor();
            int contador = 0;
            for (int j = 0; j < cantAcc; j++) {
                if (vAcc[j].getFechaHora().getAnio() == anio && vAcc[j].getIdSuscriptor() == idSus) {
                    contador++;
                }
            }
            if (contador > 0) {
                cout << vSus[i].getApellido() << "\t" << vSus[i].getNombre() << "\t\t" << contador << endl;
            }
        }
    }
    delete[] vSus;
    delete[] vAcc;
}

void musicon::reporteReproduccionesPorGenero() {
    int anio;
    cout << "INGRESE ANIO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    int cantGen = contarRegistros("generos.dat", sizeof(Genero));
    Genero* vGen = new Genero[cantGen];
    FILE *pGen = fopen("generos.dat", "rb");
    if(pGen) { fread(vGen, sizeof(Genero), cantGen, pGen); fclose(pGen); }

    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];
    FILE *pAcc = fopen("accesos.dat", "rb");
    if(pAcc) { fread(vAcc, sizeof(Accesos), cantAcc, pAcc); fclose(pAcc); }

    cout << endl << "REPRODUCCIONES POR GENERO (" << anio << ")" << endl;
    cout << "GENERO\t\tCANTIDAD" << endl;

    for(int i = 0; i < cantGen; i++) {
        int idGen = vGen[i].getIdGeneros();
        int totalGenero = 0;
        for(int j = 0; j < cantCan; j++) {
            if(vCan[j].getIdGenero() == idGen) {
                int idCancion = vCan[j].getIdCancion();
                for(int k = 0; k < cantAcc; k++) {
                    if(vAcc[k].getFechaHora().getAnio() == anio && vAcc[k].getIdCancion() == idCancion) {
                        totalGenero++;
                    }
                }
            }
        }
        if (totalGenero > 0) cout << vGen[i].getNombre() << "\t\t" << totalGenero << endl;
    }
    delete[] vGen; delete[] vCan; delete[] vAcc;
}

void musicon::reporteReproduccionesPorCancion() {
    int anio;
    cout << "INGRESE ANIO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];
    FILE *pAcc = fopen("accesos.dat", "rb");
    if (pAcc) { fread(vAcc, sizeof(Accesos), cantAcc, pAcc); fclose(pAcc); }

    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if (pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "REPRODUCCIONES POR CANCION (" << anio << ")" << endl;
    cout << "TITULO\t\t\tTOTAL" << endl;

    for(int i = 0; i < cantCan; i++) {
        if (vCan[i].getEstado()) {
            int idCancion = vCan[i].getIdCancion();
            int total = 0;
            for(int j = 0; j < cantAcc; j++) {
                if(vAcc[j].getFechaHora().getAnio() == anio && vAcc[j].getIdCancion() == idCancion) {
                    total++;
                }
            }
            if (total > 0) cout << vCan[i].getNombre() << "\t\t" << total << endl;
        }
    }
    delete[] vAcc; delete[] vCan;
}

void musicon::reporteListarCancionesPorGenero() {
    char nombreGenero[50];
    cout << "Ingrese nombre del genero: ";
    cin.ignore();
    cin.getline(nombreGenero, 50);

    int cantGen = contarRegistros("generos.dat", sizeof(Genero));
    Genero* vGen = new Genero[cantGen];
    FILE *pGen = fopen("generos.dat", "rb");
    if(pGen) { fread(vGen, sizeof(Genero), cantGen, pGen); fclose(pGen); }

    int idEncontrado = -1;
    for(int i=0; i<cantGen; i++) {
        if(strcasecmp(vGen[i].getNombre(), nombreGenero) == 0) {
            idEncontrado = vGen[i].getIdGeneros();
            break;
        }
    }
    delete[] vGen;

    if(idEncontrado == -1) { cout << "Genero no encontrado." << endl; return; }

    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "CANCIONES DE: " << nombreGenero << endl;
    for(int i=0; i<cantCan; i++) {
        if(vCan[i].getIdGenero() == idEncontrado && vCan[i].getEstado()) {
            cout << "- " << vCan[i].getNombre() << endl;
        }
    }
    delete[] vCan;
}

void musicon::reporteCantidadCancionesPorArtista() {
    int cantArt = contarRegistros("artistas.dat", sizeof(Artista));
    Artista* vArt = new Artista[cantArt];
    FILE *pArt = fopen("artistas.dat", "rb");
    if(pArt) { fread(vArt, sizeof(Artista), cantArt, pArt); fclose(pArt); }

    int cantAlb = contarRegistros("albumes.dat", sizeof(Album));
    Album* vAlb = new Album[cantAlb];
    FILE *pAlb = fopen("albumes.dat", "rb");
    if(pAlb) { fread(vAlb, sizeof(Album), cantAlb, pAlb); fclose(pAlb); }

    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "--- CANTIDAD DE CANCIONES POR ARTISTA ---" << endl;
    cout << "ARTISTA\t\t\tCANTIDAD" << endl;
    cout << "-----------------------------------------" << endl;

    for(int i = 0; i < cantArt; i++) {
        if (vArt[i].getEstado()) {
            int idArtista = vArt[i].getIdArtista();
            int contadorCanciones = 0;

            for(int j = 0; j < cantAlb; j++) {
                if(vAlb[j].getEstado() && vAlb[j].getIdArtista() == idArtista) {
                    int idAlbum = vAlb[j].getIdAlbum();

                    for(int k = 0; k < cantCan; k++) {
                        if(vCan[k].getEstado() && vCan[k].getIdAlbum() == idAlbum) {
                            contadorCanciones++;
                        }
                    }
                }
            }
            cout << vArt[i].getNombre() << "\t\t" << contadorCanciones << endl;
        }
    }

    cout << "-----------------------------------------" << endl;

    delete[] vArt;
    delete[] vAlb;
    delete[] vCan;
}


void musicon::registrarAcceso() {
    cout << endl << "--- REGISTRAR ACCESO (SIMULACION) ---" << endl;

    int idSuscriptor, idCancion;

    cout << "Ingrese ID del Suscriptor que escucha: ";
    cin >> idSuscriptor;


    cout << "Ingrese ID de la Cancion escuchada: ";
    cin >> idCancion;


    time_t now = time(0);
    tm *ltm = localtime(&now);

    int anio = 1900 + ltm->tm_year;
    int mes = 1 + ltm->tm_mon;
    int dia = ltm->tm_mday;
    int hora = ltm->tm_hour;
    int min = ltm->tm_min;

    Fecha fechaActual(min, hora, dia, mes, anio);

    Accesos nuevoAcceso;
    nuevoAcceso.setIdSuscriptor(idSuscriptor);
    nuevoAcceso.setIdCancion(idCancion);
    nuevoAcceso.setFechaHora(fechaActual);

    FILE *p = fopen("accesos.dat", "ab");
    if (p == NULL) {
        cout << "Error al abrir accesos.dat" << endl;
        return;
    }
    fwrite(&nuevoAcceso, sizeof(Accesos), 1, p);
    fclose(p);

    cout << endl << "[OK] Reproduccion registrada con fecha: " << fechaActual.toString() << endl;
}


void musicon::cargarNuevaPlaylist() {
    cout << endl << "--- CREAR NUEVA PLAYLIST ---" << endl;
    Playlist nuevaP;
    nuevaP.Cargar(); // Asegúrate que Playlist::Cargar pida los datos y ponga _estado = true

    if (nuevaP.getEstado()) {
        FILE *p = fopen("playlists.dat", "ab");
        if (p == NULL) {
            cout << "Error al abrir el archivo playlists.dat" << endl;
            return;
        }
        fwrite(&nuevaP, sizeof(Playlist), 1, p);
        fclose(p);
        cout << "Playlist creada exitosamente!" << endl;
    }
}

// 2. MODIFICACIÓN
void musicon::modificarPlaylist() {
    int idBuscado;
    cout << "Ingrese el ID de la Playlist a modificar: ";
    cin >> idBuscado;

    FILE *p = fopen("playlists.dat", "r+b");
    if (p == NULL) {
        cout << "Error al abrir playlists.dat (quizas no existe aun)." << endl;
        return;
    }

    Playlist reg;
    bool encontrado = false;

    while (fread(&reg, sizeof(Playlist), 1, p) == 1) {
        // Buscamos por ID y que esté activa
        if (reg.getIdPlaylist() == idBuscado && reg.getEstado() == true) {
            encontrado = true;
            cout << endl << "--- PLAYLIST ENCONTRADA ---" << endl;
            reg.Mostrar();

            cout << endl << "--- INGRESE NUEVOS DATOS ---" << endl;
            
            char nuevoNombre[50];
            int nuevoCreador;

            cout << "Nuevo Nombre: ";
            cin.ignore();
            cin.getline(nuevoNombre, 50);

            cout << "Nuevo ID Creador: ";
            cin >> nuevoCreador;

            // Actualizamos el objeto
            reg.setNombre(nuevoNombre);
            reg.setIdSuscriptorCreador(nuevoCreador);

            // Retrocedemos y guardamos
            fseek(p, -sizeof(Playlist), SEEK_CUR);
            fwrite(&reg, sizeof(Playlist), 1, p);

            cout << "Playlist modificada exitosamente." << endl;
            break;
        }
    }

    if (!encontrado) cout << "No se encontro una playlist activa con ese ID." << endl;
    fclose(p);
}

// 3. BAJA LÓGICA
void musicon::eliminarPlaylist() {
    int idBuscado;
    cout << "Ingrese el ID de la Playlist a eliminar: ";
    cin >> idBuscado;

    FILE *p = fopen("playlists.dat", "r+b");
    if (p == NULL) {
        cout << "Error al abrir playlists.dat" << endl;
        return;
    }

    Playlist reg;
    bool encontrado = false;

    while (fread(&reg, sizeof(Playlist), 1, p) == 1) {
        if (reg.getIdPlaylist() == idBuscado && reg.getEstado() == true) {
            encontrado = true;
            reg.Mostrar();

            char confirma;
            cout << "Confirmar eliminacion? (s/n): ";
            cin >> confirma;

            if (confirma == 's' || confirma == 'S') {
                reg.setEstado(false); // Baja lógica
                fseek(p, -sizeof(Playlist), SEEK_CUR);
                fwrite(&reg, sizeof(Playlist), 1, p);
                cout << "Playlist eliminada correctamente." << endl;
            } else {
                cout << "Operacion cancelada." << endl;
            }
            break;
        }
    }

    if (!encontrado) cout << "No se encontro una playlist activa con ese ID." << endl;
    fclose(p);
}




