/**
* Este archivo implementa la clase CancionManager. Maneja la lógica de negocio para canciones,
* incluyendo CRUD, importación/exportación, backups y registro de accesos. Utiliza archivos binarios
* para persistencia y coordina con otros archivos para mantener la integridad de datos.
*/

#include "../include/CancionManager.h"
#include "../include/Accesos.h"
#include "../include/InputHelper.h"

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <ctime>

using namespace std;

vector<string> parsearCSV(string linea) {
    vector<string> campos;
    string campo;
    bool enComillas = false;
    
    for (char c : linea) {
        if (c == '"') {
            enComillas = !enComillas;
        } else if (c == ',' && !enComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

// --- VISUALIZACIÓN HUMANA ---

void CancionManager::ListarDetallado() {
    int cantidad = _archivoCanciones.ObtenerCantidadRegistros();
    
    cout << left << setw(5) << "ID"
         << setw(30) << "TITULO"
         << setw(20) << "ARTISTA"
         << setw(30) << "ALBUM"
         << setw(15) << "GENERO"
         << setw(10) << "DURACION" << endl;
    cout << string(110, '-') << endl;
    
    for (int i = 0; i < cantidad; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        
        if (c.getEstado()) {
            Album alb = _archivoAlbum.BuscarPorID(c.getIdAlbum());
            string nombreAlbum = (alb.getEstado()) ? alb.getTitulo() : "Desconocido";
            string nombreArtista = "Desconocido";
            
            if (alb.getEstado()) {
                Artista art = _archivoArtistas.BuscarPorID(alb.getIdArtista());
                if (art.getEstado()) nombreArtista = art.getNombre();
            }
            
            Genero gen = _archivoGeneros.BuscarPorID(c.getIdGenero());
            string nombreGenero = (gen.getEstado()) ? gen.getNombre() : "Desconocido";
            
            cout << left << setw(5) << c.getIdCancion()
                 << setw(30) << c.getNombre()
                 << setw(20) << nombreArtista
                 << setw(30) << nombreAlbum
                 << setw(15) << nombreGenero
                 << c.getDuracionSegundos() / 60 << "m " << c.getDuracionSegundos() % 60 << "s"
                 << endl;
        }
    }
    InputHelper::pausa();
}

// --- LOGICA DE NEGOCIO ---

void CancionManager::Agregar() {
    cout << endl << "--- SUBIR CANCION ---" << endl;
    
    Canciones nueva;
    int id = _archivoCanciones.GenerarIDNuevo();
    nueva.setIdCancion(id);
    
    char nombre[100];
    InputHelper::pedirCadena("Titulo de la cancion: ", nombre, 100);
    nueva.setNombre(nombre);
    
    char nombreAlbum[100];
    InputHelper::pedirCadena("Album (Enter si es Single): ", nombreAlbum, 100);
    int idAlbum = 0;
    if (strlen(nombreAlbum) > 0) {
        idAlbum = _archivoAlbum.BuscarIDPorTitulo(nombreAlbum);
        if (idAlbum == -1) {
            idAlbum = crearAlbumRapido(nombreAlbum);
        }
    }
    nueva.setIdAlbum(idAlbum);
    
    char nombreGenero[50];
    InputHelper::pedirCadena("Genero (ej: Rock, Pop): ", nombreGenero, 50);
    int idGenero = 0;
    if (strlen(nombreGenero) > 0) {
        idGenero = _archivoGeneros.BuscarIDPorNombre(nombreGenero);
        if (idGenero == -1) {
            Genero g;
            int nuevoIdG = _archivoGeneros.GenerarIDNuevo();
            g.setIdGeneros(nuevoIdG);
            g.setNombre(nombreGenero);
            g.setEstado(true);
            
            _archivoGeneros.Guardar(g);
            idGenero = nuevoIdG;
            cout << "   [!] Genero nuevo creado: " << nombreGenero << endl;
        }
    }
    nueva.setIdGenero(idGenero);
    
    int seg = InputHelper::pedirEntero("Duracion (segundos): ");
    nueva.setDuracionSegundos(seg);
    nueva.setEstado(true);
    
    if(_archivoCanciones.Guardar(nueva)) {
        cout << "   [OK] Cancion guardada exitosamente (ID " << id << ")." << endl;
    } else {
        cout << "   [ERROR] No se pudo guardar." << endl;
    }
    InputHelper::pausa();
}

int CancionManager::crearAlbumRapido(const char* tituloAlbum) {
    cout << endl << "   >>> NUEVO ALBUM DETECTADO: " << tituloAlbum << " <<<" << endl;
    
    char nombreArtista[100];
    InputHelper::pedirCadena("   Artista del album: ", nombreArtista, 100);
    
    int idArtista = _archivoArtistas.BuscarIDPorNombre(nombreArtista);
    if (idArtista == -1) {
        cout << "   [!] Artista nuevo. Creando perfil para '" << nombreArtista << "'..." << endl;
        idArtista = _archivoArtistas.GenerarIDNuevo();
        
        Artista art;
        art.setIdArtista(idArtista);
        art.setNombre(nombreArtista);
        art.setNacionalidad("Desconocida");
        art.setEstado(true);
        _archivoArtistas.Guardar(art);
    }
    
    Album nuevo;
    int idAlbum = _archivoAlbum.GenerarIDNuevo();
    nuevo.setIdAlbum(idAlbum);
    nuevo.setTitulo(tituloAlbum);
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0);
    nuevo.setEstado(true);
    
    _archivoAlbum.Guardar(nuevo);
    cout << "   [OK] Album creado (ID " << idAlbum << ")." << endl;
    return idAlbum;
}

void CancionManager::Modificar() {
    char nombreBuscado[100];
    InputHelper::pedirCadena("Nombre de la cancion a modificar: ", nombreBuscado, 100);
    
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int pos = -1;
    
    for(int i = 0; i < total; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        if(InputHelper::sonIgualesSinMayusculas(c.getNombre(), nombreBuscado) && c.getEstado()) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        Canciones reg = _archivoCanciones.Leer(pos);
        cout << "--- EDITANDO ---" << endl;
        reg.Mostrar();
        
        char buffer[100];
        InputHelper::pedirCadena("Nuevo Nombre [Enter mantiene]: ", buffer, 100);
        if(strlen(buffer) > 0) reg.setNombre(buffer);
        
        int dur = InputHelper::pedirEntero("Nueva Duracion [0 mantiene]: ", false);
        if(dur > 0) reg.setDuracionSegundos(dur);
        
        if(_archivoCanciones.Modificar(pos, reg)) cout << "Actualizado." << endl;
    } else {
        cout << "No encontrado." << endl;
    }
    InputHelper::pausa();
}

void CancionManager::Eliminar() {
    char nombreBuscado[100];
    InputHelper::pedirCadena("Nombre de la cancion a eliminar: ", nombreBuscado, 100);
    
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int pos = -1;
    
    for(int i = 0; i < total; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        if(InputHelper::sonIgualesSinMayusculas(c.getNombre(), nombreBuscado) && c.getEstado()) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        Canciones reg = _archivoCanciones.Leer(pos);
        reg.Mostrar();
        
        cout << "Confirmar eliminacion? (s/n): ";
        char op; 
        cin >> op;
        
        if(op == 's' || op == 'S') {
            reg.setEstado(false);
            if(_archivoCanciones.Modificar(pos, reg)) cout << "Eliminado." << endl;
        }
    } else {
        cout << "No encontrado." << endl;
    }
    InputHelper::pausa();
}

void CancionManager::Listar() {
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    for(int i = 0; i < total; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        if(c.getEstado()) c.Mostrar();
    }
    InputHelper::pausa();
}

void CancionManager::MostrarMenu() {
    int opcion;
    do {
        system("cls");
        cout << "--- CANCIONES ---\n"
             << "1. Listar Todas (Detallado)\n"
             << "2. Agregar Nueva Cancion\n"
             << "3. Eliminar Cancion\n"
             << "4. Modificar Cancion\n"
             << "0. Volver\n";
             
        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4);
        
        switch (opcion) {
            case 1: ListarDetallado(); break;
            case 2: Agregar(); break;
            case 3: Eliminar(); break;
            case 4: Modificar(); break;
        }
    } while (opcion != 0);
}

void CancionManager::RegistrarAcceso(int idSuscriptor) {
    char nomC[100];
    InputHelper::pedirCadena("Cancion a escuchar: ", nomC, 100);
    
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int idC = -1;
    
    for (int i = 0; i < total; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        if (InputHelper::sonIgualesSinMayusculas(c.getNombre(), nomC) && c.getEstado()) {
            idC = c.getIdCancion();
            break;
        }
    }
    
    if (idC == -1) {
        cout << "No existe." << endl;
        return;
    }
    
    Accesos a;
    a.setIdSuscriptor(idSuscriptor);
    a.setIdCancion(idC);
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    a.setFechaHora(Fecha(ltm->tm_min, ltm->tm_hour, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year));
    a.Guardar();
    
    cout << "Reproduciendo..." << endl;
}

void CancionManager::HacerBackup() {
    cout << "Haciendo backup..." << endl;
    FILE *d = fopen("canciones.bak", "wb");
    
    if(d) {
        int total = _archivoCanciones.ObtenerCantidadRegistros();
        for(int i = 0; i < total; i++) {
            Canciones c = _archivoCanciones.Leer(i);
            fwrite(&c, sizeof(Canciones), 1, d);
        }
        fclose(d);
        cout << "Backup listo." << endl;
    } else {
        cout << "Error al crear backup." << endl;
    }
}

void CancionManager::ExportarACSV() {
    ofstream salida("ListadoCanciones.csv");
    if (!salida.is_open()) {
        cout << "No se pudo crear el archivo CSV." << endl;
        return;
    }
    
    salida << "ID,Nombre,Artista,Album,Genero,DuracionSegundos\n";
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    
    for(int i = 0; i < total; i++) {
        Canciones c = _archivoCanciones.Leer(i);
        if (!c.getEstado()) continue;
        
        Album alb = _archivoAlbum.BuscarPorID(c.getIdAlbum());
        string nombreAlbum = (alb.getEstado()) ? alb.getTitulo() : "";
        string nombreArtista = "";
        
        if (alb.getEstado()) {
            Artista art = _archivoArtistas.BuscarPorID(alb.getIdArtista());
            if (art.getEstado()) nombreArtista = art.getNombre();
        }
        
        Genero gen = _archivoGeneros.BuscarPorID(c.getIdGenero());
        string nombreGenero = (gen.getEstado()) ? gen.getNombre() : "";
        
        salida << c.getIdCancion() << ","
               << "\"" << c.getNombre() << "\"," 
               << "\"" << nombreArtista << "\"," 
               << "\"" << nombreAlbum << "\"," 
               << "\"" << nombreGenero << "\"," 
               << c.getDuracionSegundos() << "\n";
    }
    
    salida.close();
    cout << "Exportacion finalizada." << endl;
}

// --- IMPORTACIÓN MASIVA INTELIGENTE ---

void CancionManager::ImportarDesdeCSV() {
    string rutaArchivo;
    cout << "Ingrese nombre del archivo (ej: En_una_Nota.csv): ";
    getline(cin, rutaArchivo);
    if(rutaArchivo.empty()) rutaArchivo = "En_una_Nota.csv";
    
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        InputHelper::pausa();
        return;
    }
    
    string linea;
    getline(archivo, linea); // Saltar cabecera
    
    int contadorImportados = 0;
    int contadorReemplazados = 0;
    int contadorOmitidos = 0;
    
    bool aplicarATodosReemplazar = false;
    bool aplicarATodosSaltar = false;
    
    cout << "Procesando..." << endl;
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = parsearCSV(linea);
        if (campos.size() >= 11) {
            string nombreCancion = campos[1];
            string nombreAlbum   = campos[2];
            string nombreArtista = campos[3];
            string nombreGenero  = campos[10];
            
            size_t posArt = nombreArtista.find(';');
            if (posArt != string::npos) nombreArtista = nombreArtista.substr(0, posArt);
            
            size_t posGen = nombreGenero.find(',');
            if (posGen != string::npos) nombreGenero = nombreGenero.substr(0, posGen);
            if (nombreGenero.empty()) nombreGenero = "Varios";
            
            int duracionMs = 0;
            try { duracionMs = stoi(campos[5]); } catch (...) { duracionMs = 0; }
            int duracionSeg = duracionMs / 1000;
            
            // 1. Resolver Padres (Buscar o Crear)
            int idArtista = _archivoArtistas.BuscarOCrear(nombreArtista);
            int idAlbum = _archivoAlbum.BuscarOCrear(nombreAlbum, idArtista);
            int idGenero = _archivoGeneros.BuscarOCrear(nombreGenero);
            
            // 2. DETECTAR CONFLICTO
            int posExistente = _archivoCanciones.BuscarPosicionPorNombreYAlbum(nombreCancion.c_str(), idAlbum);
            
            if (posExistente != -1) {
                if (aplicarATodosSaltar) {
                    contadorOmitidos++;
                    continue;
                }
                
                if (aplicarATodosReemplazar) {
                    Canciones existente = _archivoCanciones.Leer(posExistente);
                    existente.setIdGenero(idGenero);
                    existente.setDuracionSegundos(duracionSeg);
                    existente.setEstado(true);
                    
                    _archivoCanciones.Modificar(posExistente, existente);
                    contadorReemplazados++;
                    cout << " ~ Reemplazado (Auto): " << nombreCancion << endl;
                    continue;
                }
                
                cout << endl << ">>> CONFLICTO: La cancion '" << nombreCancion << "' ya existe en el album." << endl;
                cout << "   1. Reemplazar (Sobrescribir)\n"
                     << "   2. Saltar (Conservar la vieja)\n"
                     << "   3. Reemplazar TODO (Para este y futuros conflictos)\n"
                     << "   4. Saltar TODO (Para este y futuros conflictos)\n";
                
                int op = InputHelper::pedirEnteroRango("   Elija opcion: ", 1, 4);
                
                if (op == 1 || op == 3) {
                    if (op == 3) aplicarATodosReemplazar = true;
                    
                    Canciones existente = _archivoCanciones.Leer(posExistente);
                    existente.setIdGenero(idGenero);
                    existente.setDuracionSegundos(duracionSeg);
                    existente.setEstado(true);
                    
                    _archivoCanciones.Modificar(posExistente, existente);
                    contadorReemplazados++;
                    cout << " ~ Reemplazado: " << nombreCancion << endl;
                } else {
                    if (op == 4) aplicarATodosSaltar = true;
                    contadorOmitidos++;
                    cout << " . Saltado: " << nombreCancion << endl;
                }
            } else {
                Canciones nueva;
                nueva.setIdCancion(_archivoCanciones.GenerarIDNuevo());
                nueva.setNombre(nombreCancion.c_str());
                nueva.setIdAlbum(idAlbum);
                nueva.setIdGenero(idGenero);
                nueva.setDuracionSegundos(duracionSeg);
                nueva.setEstado(true);
                
                _archivoCanciones.Guardar(nueva);
                contadorImportados++;
                cout << " + Importado: " << nombreCancion << endl;
            }
        }
    }
    
    archivo.close();
    cout << "-----------------------------------\n"
         << "RESUMEN DE IMPORTACION:\n"
         << " + Nuevas agregadas : " << contadorImportados << "\n"
         << " ~ Reemplazadas     : " << contadorReemplazados << "\n"
         << " . Omitidas         : " << contadorOmitidos << endl;
    InputHelper::pausa();
}
