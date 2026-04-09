/**
 * Este archivo implementa la clase CancionManager. Maneja la l\u00f3gica de negocio para canciones,
 * incluyendo CRUD, importación/exportación, backups y registro de accesos. Utiliza archivos binarios
 * para persistencia y coordina con otros archivos para mantener la integridad de datos.
 */

#include "../include/CancionManager.h"
#include "../include/Accesos.h"
#include "InputHelper.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <ctime>

using namespace std;

/**
 * Compara dos textos sin distinguir mayúsculas y minúsculas.
 */
static bool sonIgualesSinMayusculas(const char* texto1, const char* texto2) {
    if (texto1 == nullptr || texto2 == nullptr) return texto1 == texto2;

    while (*texto1 && *texto2) {
        if (std::tolower(static_cast<unsigned char>(*texto1)) !=
            std::tolower(static_cast<unsigned char>(*texto2))) {
            return false;
        }
        ++texto1;
        ++texto2;
    }

    return *texto1 == *texto2;
}

/*
 * Función helper para parsear líneas CSV respetando comillas.
 * Parámetros: linea - La línea CSV a parsear.
 * Retorno: Vector de strings con los campos separados.
 */
vector<string> parsearCSV(string linea) {
    vector<string> campos; // Vector para almacenar los campos
    string campo; // Campo actual
    bool enComillas = false; // Bandera para saber si estamos dentro de comillas

    for (char c : linea) { // Itera sobre cada carácter
        if (c == '"') {
            enComillas = !enComillas; // Cambia el estado de comillas
        } else if (c == ',' && !enComillas) { // Si es coma y no en comillas, separa campo
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c; // Agrega carácter al campo
        }
    }
    campos.push_back(campo); // Agrega el último campo
    return campos;
}

// --- VISUALIZACIÓN HUMANA ---
/*
 * Lista todas las canciones con detalles completos: ID, título, artista, álbum, género y duración.
 * Utiliza joins con archivos de artistas, álbumes y géneros para mostrar información relacionada.
 */
void CancionManager::ListarDetallado() {
    int cantidad = _archivoCanciones.ObtenerCantidadRegistros(); // Obtiene el total de canciones

    // Imprime el encabezado de la tabla
    cout << left << setw(5) << "ID"
         << setw(30) << "TITULO"
         << setw(20) << "ARTISTA"
         << setw(30) << "ALBUM"
         << setw(15) << "GENERO"
         << setw(10) << "DURACION" << endl;
    cout << string(110, '-') << endl; // Línea separadora

    for (int i = 0; i < cantidad; i++) { // Itera sobre todas las canciones
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
/*
 * Agrega una nueva canción al sistema. Solicita datos al usuario y crea automáticamente
 * artistas, álbumes y géneros si no existen. Genera un ID único para la canción.
 */
void CancionManager::Agregar() {
    cout << endl << "--- SUBIR CANCION ---" << endl;
    Canciones nueva;
    int id = _archivoCanciones.GenerarIDNuevo(); // Genera ID único para la nueva canción
    nueva.setIdCancion(id);

    char nombre[100];
    InputHelper::pedirCadena("Titulo de la cancion: ", nombre, 100); // Solicita título
    nueva.setNombre(nombre);

    char nombreAlbum[100];
    InputHelper::pedirCadena("Album (Enter si es Single): ", nombreAlbum, 100); // Solicita álbum

    int idAlbum = 0;
    if (strlen(nombreAlbum) > 0) { // Si se especificó álbum
        idAlbum = _archivoAlbum.BuscarIDPorTitulo(nombreAlbum); // Busca si existe
        if (idAlbum == -1) {
            idAlbum = crearAlbumRapido(nombreAlbum); // Crea álbum si no existe
        }
    }
    nueva.setIdAlbum(idAlbum);

    char nombreGenero[50];
    InputHelper::pedirCadena("Genero (ej: Rock, Pop): ", nombreGenero, 50); // Solicita género

    int idGenero = 0;
    if (strlen(nombreGenero) > 0) { // Si se especificó género
        idGenero = _archivoGeneros.BuscarIDPorNombre(nombreGenero); // Busca si existe
        if (idGenero == -1) { // Si no existe, lo crea
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

    int seg = InputHelper::pedirEntero("Duracion (segundos): "); // Solicita duración
    nueva.setDuracionSegundos(seg);
    nueva.setEstado(true);

    if(_archivoCanciones.Guardar(nueva)) { // Guarda la canción
        cout << "   [OK] Cancion guardada exitosamente (ID " << id << ")." << endl;
    } else {
        cout << "   [ERROR] No se pudo guardar." << endl;
    }
    InputHelper::pausa();
}

/*
 * Crea un álbum rápidamente cuando se detecta uno nuevo durante la subida de canción.
 * Solicita el artista y lo crea si no existe. Retorna el ID del álbum creado.
 * Parámetros: tituloAlbum - Nombre del álbum a crear.
 * Retorno: ID del álbum creado.
 */
int CancionManager::crearAlbumRapido(const char* tituloAlbum) {
    cout << endl << "   >>> NUEVO ALBUM DETECTADO: " << tituloAlbum << " <<<" << endl;

    char nombreArtista[100];
    InputHelper::pedirCadena("   Artista del album: ", nombreArtista, 100); // Solicita artista

    int idArtista = _archivoArtistas.BuscarIDPorNombre(nombreArtista); // Busca si existe

    if (idArtista == -1) { // Si no existe, lo crea
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
    int idAlbum = _archivoAlbum.GenerarIDNuevo(); // Genera ID único
    nuevo.setIdAlbum(idAlbum);
    nuevo.setTitulo(tituloAlbum);
    nuevo.setIdArtista(idArtista);
    nuevo.setAnioPublicacion(0); // Año por defecto
    nuevo.setEstado(true);

    _archivoAlbum.Guardar(nuevo); // Guarda el álbum

    cout << "   [OK] Album creado (ID " << idAlbum << ")." << endl;
    return idAlbum;
}

/*
 * Modifica una canción existente. Busca por nombre y permite cambiar título y duración.
 * Utiliza búsqueda lineal para encontrar la canción activa.
 */
void CancionManager::Modificar() {
    char nombreBuscado[100];
    InputHelper::pedirCadena("Nombre de la cancion a modificar: ", nombreBuscado, 100); // Solicita nombre a buscar

    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int pos = -1;
    for(int i=0; i<total; i++) { // Busca la canción por nombre
        Canciones c = _archivoCanciones.Leer(i);
        if(sonIgualesSinMayusculas(c.getNombre(), nombreBuscado) && c.getEstado()) {
            pos = i;
            break;
        }
    }

    if (pos != -1) { // Si se encontró
        Canciones reg = _archivoCanciones.Leer(pos);
        cout << "--- EDITANDO ---" << endl;
        reg.Mostrar(); // Muestra datos actuales

        char buffer[100];
        InputHelper::pedirCadena("Nuevo Nombre [Enter mantiene]: ", buffer, 100); // Nuevo título
        if(strlen(buffer) > 0) reg.setNombre(buffer);

        int dur = InputHelper::pedirEntero("Nueva Duracion [0 mantiene]: ", false); // Nueva duración
        if(dur > 0) reg.setDuracionSegundos(dur);

        if(_archivoCanciones.Modificar(pos, reg)) cout << "Actualizado." << endl; // Guarda cambios
    } else {
        cout << "No encontrado." << endl;
    }
    InputHelper::pausa();
}

/*
 * Elimina una canción lógicamente (marca como inactiva). Busca por nombre y confirma antes de eliminar.
 * Utiliza búsqueda lineal para encontrar la canción activa.
 */
void CancionManager::Eliminar() {
    char nombreBuscado[100];
    InputHelper::pedirCadena("Nombre de la cancion a eliminar: ", nombreBuscado, 100); // Solicita nombre a buscar

    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int pos = -1;
    for(int i=0; i<total; i++) { // Busca la canción por nombre
        Canciones c = _archivoCanciones.Leer(i);
        if(sonIgualesSinMayusculas(c.getNombre(), nombreBuscado) && c.getEstado()) {
            pos = i;
            break;
        }
    }

    if (pos != -1) { // Si se encontró
        Canciones reg = _archivoCanciones.Leer(pos);
        reg.Mostrar(); // Muestra datos antes de eliminar
        cout << "Confirmar eliminacion? (s/n): ";
        char op; cin >> op;
        if(op == 's' || op == 'S') { // Confirma eliminación
            reg.setEstado(false); // Marca como inactiva
            if(_archivoCanciones.Modificar(pos, reg)) cout << "Eliminado." << endl; // Guarda cambios
        }
    } else {
        cout << "No encontrado." << endl;
    }
    InputHelper::pausa();
}

/*
 * Lista todas las canciones activas mostrando sus datos básicos.
 * Utiliza el método Mostrar() de la clase Canciones.
 */
void CancionManager::Listar() {
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    for(int i=0; i<total; i++) { // Itera sobre todas las canciones
        Canciones c = _archivoCanciones.Leer(i);
        if(c.getEstado()) c.Mostrar(); // Muestra solo activas
    }
    InputHelper::pausa();
}

/*
 * Muestra el menú principal de gestión de canciones y maneja la navegación.
 * Permite listar, agregar, eliminar y modificar canciones.
 */
void CancionManager::MostrarMenu() {
    int opcion;
    do {
        system("cls");
        cout << "--- CANCIONES ---\n";
        cout << "1. Listar Todas (Detallado)\n";
        cout << "2. Agregar Nueva Cancion\n";
        cout << "3. Eliminar Cancion\n";
        cout << "4. Modificar Cancion\n";
        cout << "0. Volver\n";
        opcion = InputHelper::pedirEnteroRango("Opcion: ", 0, 4); // Valida opción
        switch (opcion) {
            case 1: ListarDetallado(); break;
            case 2: Agregar(); break;
            case 3: Eliminar(); break;
            case 4: Modificar(); break;
        }
    } while (opcion != 0);
}

/*
 * Registra un acceso (reproducción) de un suscriptor a una canción.
 * Busca la canción por nombre y guarda el registro con fecha/hora actual.
 * Parámetros: idSuscriptor - ID del suscriptor que reproduce la canción.
 */
void CancionManager::RegistrarAcceso(int idSuscriptor) {
    char nomC[100];
    InputHelper::pedirCadena("Cancion a escuchar: ", nomC, 100); // Solicita nombre de canción

    int total = _archivoCanciones.ObtenerCantidadRegistros();
    int idC = -1;
    for (int i = 0; i < total; i++) { // Busca la canción por nombre
        Canciones c = _archivoCanciones.Leer(i);
        if (sonIgualesSinMayusculas(c.getNombre(), nomC) && c.getEstado()) {
            idC = c.getIdCancion();
            break;
        }
    }
    if (idC == -1) { // Si no se encontró
        cout << "No existe." << endl;
        return;
    }

    Accesos a;
    a.setIdSuscriptor(idSuscriptor);
    a.setIdCancion(idC);
    time_t now = time(0); // Obtiene fecha/hora actual
    tm *ltm = localtime(&now);
    a.setFechaHora(Fecha(ltm->tm_min, ltm->tm_hour, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year));
    a.Guardar(); // Guarda el registro de acceso
    cout << "Reproduciendo..." << endl;
}

/*
 * Crea un backup binario de todas las canciones en el archivo "canciones.bak".
 * Copia todos los registros tal cual están en el archivo original.
 */
void CancionManager::HacerBackup() {
    cout << "Haciendo backup..." << endl;
    FILE *d = fopen("canciones.bak", "wb"); // Abre archivo de backup en modo escritura binaria
    if(d) {
        int total = _archivoCanciones.ObtenerCantidadRegistros();
        for(int i=0; i<total; i++) { // Copia todos los registros
            Canciones c = _archivoCanciones.Leer(i);
            fwrite(&c, sizeof(Canciones), 1, d); // Escribe en binario
        }
        fclose(d);
        cout << "Backup listo." << endl;
    } else {
        cout << "Error al crear backup." << endl;
    }
}

/*
 * Exporta todas las canciones activas a un archivo CSV llamado "ListadoCanciones.csv".
 * Incluye información relacionada de artistas, álbumes y géneros mediante joins.
 */
void CancionManager::ExportarACSV() {
    ofstream salida("ListadoCanciones.csv");
    if (!salida.is_open()) {
        cout << "No se pudo crear el archivo CSV." << endl;
        return;
    }
    salida << "ID,Nombre,Artista,Album,Genero,DuracionSegundos\n";
    int total = _archivoCanciones.ObtenerCantidadRegistros();
    for(int i=0; i<total; i++) {
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
/*
 * Importa canciones desde un archivo CSV. Maneja conflictos inteligentes preguntando al usuario
 * si reemplazar o saltar canciones duplicadas. Crea automáticamente artistas, álbumes y géneros.
 * Soporta opciones de "aplicar a todos" para evitar preguntas repetitivas.
 */
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

    // Opcion de "Reemplazar todo" o "Saltar todo" para no preguntar 100 veces
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
            int idArtista = _archivoArtistas.BuscarOCrear(nombreArtista); // Busca o crea artista
            int idAlbum = _archivoAlbum.BuscarOCrear(nombreAlbum, idArtista); // Busca o crea álbum
            int idGenero = _archivoGeneros.BuscarOCrear(nombreGenero); // Busca o crea género

            // 2. DETECTAR CONFLICTO (¿Ya existe esta canción?)
            int posExistente = _archivoCanciones.BuscarPosicionPorNombreYAlbum(nombreCancion.c_str(), idAlbum);

            if (posExistente != -1) {
                // --- CONFLICTO ENCONTRADO ---

                // Si ya decidimos "Saltar todo", continuamos sin hacer nada
                if (aplicarATodosSaltar) {
                    contadorOmitidos++;
                    continue;
                }

                // Si ya decidimos "Reemplazar todo", procedemos a modificar directo
                if (aplicarATodosReemplazar) {
                    Canciones existente = _archivoCanciones.Leer(posExistente);
                    // Actualizamos datos manteniendo el ID original
                    existente.setIdGenero(idGenero);
                    existente.setDuracionSegundos(duracionSeg);
                    existente.setEstado(true); // Reactivar si estaba borrada

                    _archivoCanciones.Modificar(posExistente, existente);
                    contadorReemplazados++;
                    cout << " ~ Reemplazado (Auto): " << nombreCancion << endl;
                    continue;
                }

                // Si no hay decisi�n global, preguntamos al usuario
                cout << endl << ">>> CONFLICTO: La cancion '" << nombreCancion << "' ya existe en el album." << endl;
                cout << "   1. Reemplazar (Sobrescribir)" << endl;
                cout << "   2. Saltar (Conservar la vieja)" << endl;
                cout << "   3. Reemplazar TODO (Para este y futuros conflictos)" << endl;
                cout << "   4. Saltar TODO (Para este y futuros conflictos)" << endl;

                int op = InputHelper::pedirEnteroRango("   Elija opcion: ", 1, 4);

                if (op == 1 || op == 3) { // Reemplazar
                    if (op == 3) aplicarATodosReemplazar = true;

                    Canciones existente = _archivoCanciones.Leer(posExistente);
                    existente.setIdGenero(idGenero);
                    existente.setDuracionSegundos(duracionSeg);
                    existente.setEstado(true);

                    _archivoCanciones.Modificar(posExistente, existente);
                    contadorReemplazados++;
                    cout << " ~ Reemplazado: " << nombreCancion << endl;
                } else { // Saltar (op 2 o 4)
                    if (op == 4) aplicarATodosSaltar = true;
                    contadorOmitidos++;
                    cout << " . Saltado: " << nombreCancion << endl;
                }

            } else {
                // --- NO EXISTE: GUARDAR NUEVA ---
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
    cout << "-----------------------------------" << endl;
    cout << "RESUMEN DE IMPORTACION:" << endl;
    cout << " + Nuevas agregadas : " << contadorImportados << endl;
    cout << " ~ Reemplazadas     : " << contadorReemplazados << endl;
    cout << " . Omitidas         : " << contadorOmitidos << endl;
    InputHelper::pausa();
}
