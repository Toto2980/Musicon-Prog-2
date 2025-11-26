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

// --- MENÚS ---

void musicon::mostrarMenuReportes() {
    cout << endl;
    cout << "--- SISTEMA DE INFORMES MUSICON (Memoria Dinamica) ---" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "1. Reproducciones anuales" << endl;
    cout << "2. Reproducciones por suscriptor" << endl;
    cout << "3. Cantidad de reproducciones por genero" << endl;
    cout << "4. Reproducciones por cancion" << endl;
    cout << "5. Listar canciones de un genero" << endl;
    cout << "6. Cantidad de canciones por artista" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "0. Salir" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Ingrese su opcion: ";
}

// --- FUNCIÓN CLAVE: CONTAR REGISTROS ---
// Esta función es fundamental para pedir la memoria exacta.
int musicon::contarRegistros(const char* nombreArchivo, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END); // Mover el cursor al final del archivo
    int bytes = ftell(p);  // Ver en qué byte estamos (tamaño total)
    fclose(p);

    return bytes / tamanioRegistro; // Total bytes / tamaño de uno = cantidad
}

// --- FUNCIONES AUXILIARES ---

int obtenerAnioActual() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_year + 1900;
}

// Buscamos el nombre del género (lectura directa para no complicar con otro vector dinámico)
std::string musicon::buscarNombreGenero(int idGeneroBuscado) {
    Genero reg;
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return "Desconocido";
    
    while(fread(&reg, sizeof(Genero), 1, p) == 1) {
        if(reg.getIdGeneros() == idGeneroBuscado) {
            fclose(p);
            return reg.getNombre();
        }
    }
    fclose(p);
    return "Desconocido";
}

// --- REPORTES CON NEW / DELETE ---

void musicon::reporteReproduccionesAnuales() {
    int anio;
    cout << "INGRESE AÑO: ";
    cin >> anio;

    int contadores[12] = {0}; // Array estático para los meses (son fijos)
    const char* nombresMeses[12] = {"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", 
                                    "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"};

    // 1. Cargar ACCESOS en Memoria Dinámica
    int cantAccesos = contarRegistros("accesos.dat", sizeof(Accesos));
    if (cantAccesos == 0) {
        cout << "No hay accesos registrados." << endl;
        return;
    }

    // PEDIR MEMORIA: Creamos un vector del tamaño exacto
    Accesos* vAccesos = new Accesos[cantAccesos];

    // CARGAR VECTOR
    FILE *p = fopen("accesos.dat", "rb");
    if (p != NULL) {
        fread(vAccesos, sizeof(Accesos), cantAccesos, p);
        fclose(p);
    }

    // 2. Procesar en memoria (usamos vAccesos como un vector normal)
    for (int i = 0; i < cantAccesos; i++) {
        if (vAccesos[i].getFechaHora().getAnio() == anio) {
            int mes = vAccesos[i].getFechaHora().getMes();
            if (mes >= 1 && mes <= 12) {
                contadores[mes - 1]++;
            }
        }
    }

    // LIBERAR MEMORIA
    delete[] vAccesos; 

    cout << endl << "REPRODUCCIONES DEL AÑO " << anio << endl;
    cout << "MES\t\tREPRODUCCIONES" << endl;
    cout << "==============================" << endl;
    for (int i = 0; i < 12; i++) {
        cout << nombresMeses[i] << "\t\t" << contadores[i] << endl;
    }
}

void musicon::reporteReproduccionesPorSuscriptor() {
    int anio;
    cout << "INGRESE AÑO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    // 1. Cargar Suscriptores en Memoria Dinámica
    int cantSus = contarRegistros("suscriptores.dat", sizeof(Suscriptor));
    Suscriptor* vSus = new Suscriptor[cantSus];
    
    FILE *pSus = fopen("suscriptores.dat", "rb");
    if (pSus == NULL) { delete[] vSus; return; }
    fread(vSus, sizeof(Suscriptor), cantSus, pSus);
    fclose(pSus);

    // 2. Cargar Accesos en Memoria Dinámica
    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];

    FILE *pAcc = fopen("accesos.dat", "rb");
    if (pAcc != NULL) {
        fread(vAcc, sizeof(Accesos), cantAcc, pAcc);
        fclose(pAcc);
    }

    cout << endl << "REPRODUCCIONES POR SUSCRIPTOR (" << anio << ")" << endl;
    cout << "APELLIDO\tNOMBRE\t\tTOTAL" << endl;
    cout << "---------------------------------------------" << endl;

    // 3. Procesamiento (Doble for en memoria, mucho más rápido que disco)
    for (int i = 0; i < cantSus; i++) {
        if (vSus[i].getEstado()) {
            int idSus = vSus[i].getIdSuscriptor();
            int contador = 0;

            // Recorro vector de accesos
            for (int j = 0; j < cantAcc; j++) {
                if (vAcc[j].getFechaHora().getAnio() == anio && 
                    vAcc[j].getIdSuscriptor() == idSus) {
                    contador++;
                }
            }

            if (contador > 0) {
                cout << vSus[i].getApellido() << "\t" 
                     << vSus[i].getNombre() << "\t\t" 
                     << contador << endl;
            }
        }
    }

    // LIBERAR MEMORIA
    delete[] vSus;
    delete[] vAcc;
}

void musicon::reporteReproduccionesPorGenero() {
    int anio;
    cout << "INGRESE AÑO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    // Cargamos Generos
    int cantGen = contarRegistros("generos.dat", sizeof(Genero));
    Genero* vGen = new Genero[cantGen];
    FILE *pGen = fopen("generos.dat", "rb");
    if(pGen) { fread(vGen, sizeof(Genero), cantGen, pGen); fclose(pGen); }

    // Cargamos Canciones
    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    // Cargamos Accesos
    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];
    FILE *pAcc = fopen("accesos.dat", "rb");
    if(pAcc) { fread(vAcc, sizeof(Accesos), cantAcc, pAcc); fclose(pAcc); }

    cout << endl << "REPRODUCCIONES POR GENERO (" << anio << ")" << endl;
    cout << "GENERO\t\tCANTIDAD" << endl;
    cout << "----------------------------" << endl;

    // Triple bucle en memoria (Genero -> Cancion -> Acceso)
    for(int i = 0; i < cantGen; i++) {
        int idGen = vGen[i].getIdGeneros();
        int totalGenero = 0;

        // Busco canciones de este género
        for(int j = 0; j < cantCan; j++) {
            if(vCan[j].getIdGenero() == idGen) {
                int idCancion = vCan[j].getIdCancion();
                
                // Cuento accesos de esta canción
                for(int k = 0; k < cantAcc; k++) {
                    if(vAcc[k].getFechaHora().getAnio() == anio &&
                       vAcc[k].getIdCancion() == idCancion) {
                        totalGenero++;
                    }
                }
            }
        }

        if (totalGenero > 0) {
            cout << vGen[i].getNombre() << "\t\t" << totalGenero << endl;
        }
    }

    delete[] vGen;
    delete[] vCan;
    delete[] vAcc;
}

void musicon::reporteReproduccionesPorCancion() {
    int anio;
    cout << "INGRESE AÑO (0 para actual): ";
    cin >> anio;
    if(anio == 0) anio = obtenerAnioActual();

    // 1. Memoria para Accesos
    int cantAcc = contarRegistros("accesos.dat", sizeof(Accesos));
    Accesos* vAcc = new Accesos[cantAcc];
    FILE *pAcc = fopen("accesos.dat", "rb");
    if (pAcc) { fread(vAcc, sizeof(Accesos), cantAcc, pAcc); fclose(pAcc); }

    // 2. Memoria para Canciones
    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if (pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "REPRODUCCIONES POR CANCION (" << anio << ")" << endl;
    cout << "TITULO\t\t\tTOTAL" << endl;
    cout << "----------------------------------" << endl;

    for(int i = 0; i < cantCan; i++) {
        if (vCan[i].getEstado()) {
            int idCancion = vCan[i].getIdCancion();
            int total = 0;

            // Contar accesos en memoria
            for(int j = 0; j < cantAcc; j++) {
                if(vAcc[j].getFechaHora().getAnio() == anio &&
                   vAcc[j].getIdCancion() == idCancion) {
                    total++;
                }
            }

            if (total > 0) {
                cout << vCan[i].getNombre() << "\t\t" << total << endl;
            }
        }
    }

    delete[] vAcc;
    delete[] vCan;
}

void musicon::reporteListarCancionesPorGenero() {
    char nombreGenero[50];
    cout << "Ingrese nombre del genero: ";
    cin.ignore();
    cin.getline(nombreGenero, 50);

    // 1. Buscar ID Género (Leemos Generos en vector dinámico)
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
    delete[] vGen; // Ya no necesitamos géneros

    if(idEncontrado == -1) {
        cout << "Genero no encontrado." << endl;
        return;
    }

    // 2. Cargar Canciones y filtrar
    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "CANCIONES DE: " << nombreGenero << endl;
    cout << "------------------------" << endl;

    bool encontro = false;
    for(int i=0; i<cantCan; i++) {
        if(vCan[i].getIdGenero() == idEncontrado && vCan[i].getEstado()) {
            cout << "- " << vCan[i].getNombre() << endl;
            encontro = true;
        }
    }
    delete[] vCan;

    if(!encontro) cout << "No hay canciones." << endl;
}

void musicon::reporteCantidadCancionesPorArtista() {
    // 1. Cargar Artistas
    int cantArt = contarRegistros("artistas.dat", sizeof(Artista));
    Artista* vArt = new Artista[cantArt];
    FILE *pArt = fopen("artistas.dat", "rb");
    if(pArt) { fread(vArt, sizeof(Artista), cantArt, pArt); fclose(pArt); }

    // 2. Cargar Albumes
    int cantAlb = contarRegistros("albumes.dat", sizeof(Album));
    Album* vAlb = new Album[cantAlb];
    FILE *pAlb = fopen("albumes.dat", "rb");
    if(pAlb) { fread(vAlb, sizeof(Album), cantAlb, pAlb); fclose(pAlb); }

    // 3. Cargar Canciones
    int cantCan = contarRegistros("canciones.dat", sizeof(Canciones));
    Canciones* vCan = new Canciones[cantCan];
    FILE *pCan = fopen("canciones.dat", "rb");
    if(pCan) { fread(vCan, sizeof(Canciones), cantCan, pCan); fclose(pCan); }

    cout << endl << "CANTIDAD DE CANCIONES POR ARTISTA" << endl;
    cout << "ARTISTA\t\t\tCANTIDAD" << endl;
    cout << "----------------------------------------" << endl;

    // Recorrer Artistas -> Albumes -> Canciones
    for(int i=0; i<cantArt; i++) {
        if(vArt[i].getEstado()) {
            int idArtista = vArt[i].getIdArtista();
            int contador = 0;

            for(int j=0; j<cantAlb; j++) {
                if(vAlb[j].getIdArtista() == idArtista && vAlb[j].getEstado()) {
                    int idAlbum = vAlb[j].getIdAlbum();
                    
                    for(int k=0; k<cantCan; k++) {
                        if(vCan[k].getIdAlbum() == idAlbum && vCan[k].getEstado()) {
                            contador++;
                        }
                    }
                }
            }

            if(contador > 0) {
                cout << vArt[i].getNombre() << "\t\t" << contador << endl;
            }
        }
    }

    // Importante: Liberar toda la memoria
    delete[] vArt;
    delete[] vAlb;
    delete[] vCan;
}

// Funciones de validación/busqueda (para completar el .h)
bool musicon::existeCancion(int id) { 
    // Implementación básica leyendo archivo
    Canciones reg; FILE *p=fopen("canciones.dat","rb");
    if(!p) return false;
    bool existe=false;
    while(fread(&reg,sizeof(Canciones),1,p)){ if(reg.getIdCancion()==id && reg.getEstado()){existe=true; break;} }
    fclose(p); return existe;
}

void musicon::mostrarMenuPrincipal() {
    int opcion;
    do {
        system("cls"); // Limpia pantalla (usa "clear" en Linux/Mac)
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
                menuConfiguracion();
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
            system("pause"); // Pausa para leer mensajes
        }
    } while (opcion != 0);
}

void musicon::menuCargas() {
    int opcion;
    do {
        system("cls");
        cout << "--- MENU DE CARGAS ---" << endl;
        cout << "1. Nueva Cancion" << endl;
        cout << "2. Nuevo Suscriptor" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "----------------------" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarNuevaCancionEnLista();
                break;
            case 2:
                cargarNuevaSuscripcion();
                break;
            case 0:
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void musicon::cargarNuevaCancionEnLista() {
    cout << endl << "--- CARGAR NUEVA CANCION ---" << endl;
    
    Canciones nuevaCancion;
    nuevaCancion.Cargar(); // Usamos el método de tu clase Canciones
    
    // Si el usuario cargó datos validos (asumimos estado true por defecto al cargar)
    if (nuevaCancion.getEstado()) {
        FILE *p = fopen("canciones.dat", "ab"); // "ab" = append binary (agregar al final)
        if (p == NULL) {
            cout << "Error al abrir el archivo canciones.dat" << endl;
            return;
        }
        
        // Escribimos el objeto en el archivo
        fwrite(&nuevaCancion, sizeof(Canciones), 1, p);
        fclose(p);
        
        cout << "Cancion guardada exitosamente!" << endl;
    } else {
        cout << "La cancion no se guardo (Estado inactivo)." << endl;
    }
}

void musicon::cargarNuevaSuscripcion() {
    cout << endl << "--- CARGAR NUEVO SUSCRIPTOR ---" << endl;
    
    Suscriptor nuevoSus;
    nuevoSus.Cargar(); // Usamos el método de tu clase Suscriptor
    
    if (nuevoSus.getEstado()) {
        FILE *p = fopen("suscriptores.dat", "ab"); // Agregar al final
        if (p == NULL) {
            cout << "Error al abrir el archivo suscriptores.dat" << endl;
            return;
        }
        
        fwrite(&nuevoSus, sizeof(Suscriptor), 1, p);
        fclose(p);
        
        cout << "Suscriptor registrado exitosamente!" << endl;
    } else {
        cout << "El suscriptor no se guardo." << endl;
    }
}

void musicon::menuConfiguracion() {
    // Implementación básica de backup
    cout << endl << "--- CONFIGURACION / BACKUP ---" << endl;
    cout << "Creando copia de seguridad de canciones..." << endl;
    
    // Copia simple de archivos (lectura -> escritura)
    FILE *origen = fopen("canciones.dat", "rb");
    FILE *destino = fopen("canciones.bak", "wb");
    
    if (origen && destino) {
        Canciones reg;
        while(fread(&reg, sizeof(Canciones), 1, origen)) {
            fwrite(&reg, sizeof(Canciones), 1, destino);
        }
        cout << "Backup de canciones creado correctamente (canciones.bak)." << endl;
    } else {
        cout << "No se pudo crear el backup (verifique si existe canciones.dat)." << endl;
    }
    
    if (origen) fclose(origen);
    if (destino) fclose(destino);
}



bool musicon::existeSuscriptor(int id) { return false; } // Placeholder
bool musicon::existeArtista(int id) { return false; }
bool musicon::existeAlbum(int id) { return false; }
bool musicon::existeGenero(int id) { return false; }
bool musicon::existeLista(int id) { return false; }
bool musicon::buscarCancion(int id, Canciones& c) { return false; }
bool musicon::buscarArtista(int id, Artista& a) { return false; }
bool musicon::buscarAlbum(int id, Album& a) { return false; }

