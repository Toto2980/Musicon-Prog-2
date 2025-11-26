#include "musicon.h"

#include <iostream>
#include <cstring>
#include <cstdio>


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
    cout << "--- SISTEMA DE INFORMES MUSICON (Modo Clase) ---" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. Reproducciones anuales" << endl;
    cout << "2. Reproducciones por suscriptor" << endl;
    cout << "3. Cantidad de reproducciones por genero" << endl;
    cout << "4. Reproducciones por cancion" << endl;
    cout << "5. Listar canciones de un genero" << endl;
    cout << "6. Cantidad de canciones por artista" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "0. Salir" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Ingrese su opcion: ";
}



bool musicon::existeCancion(int idCancion) {
    Canciones obj;

    FILE *p = fopen("canciones.dat", "rb");
    if (p == NULL) return false;

    while(fread(&obj, sizeof(Canciones), 1, p) == 1){
        if(obj.getIdCancion() == idCancion && obj.getEstado() == true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool musicon::existeSuscriptor(int idSuscriptor) {
    Suscriptor obj;
    FILE *p = fopen("suscriptores.dat", "rb");
    if (p == NULL) return false;

    while(fread(&obj, sizeof(Suscriptor), 1, p) == 1){
        if(obj.getIdSuscriptor() == idSuscriptor && obj.getEstado() == true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool musicon::existeArtista(int idArtista) {
    Artista obj;
    FILE *p = fopen("artistas.dat", "rb");
    if (p == NULL) return false;

    while(fread(&obj, sizeof(Artista), 1, p) == 1){
        if(obj.getIdArtista() == idArtista && obj.getEstado() == true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool musicon::existeAlbum(int idAlbum) {
    Album obj;
    FILE *p = fopen("albumes.dat", "rb");
    if (p == NULL) return false;

    while(fread(&obj, sizeof(Album), 1, p) == 1){
        if(obj.getIdAlbum() == idAlbum && obj.getEstado() == true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool musicon::existeGenero(int idGenero) {
    Genero obj;
    FILE *p = fopen("generos.dat", "rb");
    if (p == NULL) return false;

    while(fread(&obj, sizeof(Genero), 1, p) == 1){
        if(obj.getIdGeneros() == idGenero && obj.getEstado() == true){
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool musicon::existeLista(int idLista) {
    return false;
}


int musicon::contarRegistros(const char* nombreArchivo, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / tamanioRegistro;
}


// --- FUNCIONES DE REPORTES (Placeholders) ---

void musicon::reporteReproduccionesAnuales() {
    cout << "\n[!] Funcion no implementada: Reproducciones Anuales" << endl;
}

void musicon::reporteReproduccionesPorSuscriptor() {
    cout << "\n[!] Funcion no implementada: Por Suscriptor" << endl;
}

void musicon::reporteReproduccionesPorGenero() {
    cout << "\n[!] Funcion no implementada: Por Genero" << endl;
}

void musicon::reporteReproduccionesPorCancion() {
    cout << "\n[!] Funcion no implementada: Por Cancion" << endl;
}

void musicon::reporteListarCancionesPorGenero() {
    cout << "\n[!] Funcion no implementada: Listar Canciones" << endl;
}

void musicon::reporteCantidadCancionesPorArtista() {
    cout << "\n[!] Funcion no implementada: Cantidad por Artista" << endl;
}

// --- FUNCIONES DE BÚSQUEDA ---

std::string musicon::buscarNombreGenero(int idGeneroBuscado) {
    return "Desconocido"; // Placeholder
}

bool musicon::buscarCancion(int idCancionBuscada, Canciones& regCancion) {
    return false; // Placeholder
}

bool musicon::buscarArtista(int idArtistaBuscada, Artista& regArtista) {
    return false; // Placeholder
}

bool musicon::buscarAlbum(int idAlbumBuscado, Album& regAlbum) {
    return false; // Placeholder
}

