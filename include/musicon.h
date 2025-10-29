// musicon.h

#ifndef MUSICON_H
#define MUSICON_H

#include <iostream>
#include <cstring>

// --- ESTRUCTURAS DE DATOS (Según TP Programacion II.docx) ---
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct DateTime {
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
    int segundo;
};

struct Suscriptor {
    int idSuscriptor;
    char dni[11];
    char nombre[50];
    char apellido[50];
    char email[100];
    Fecha fechaNacimiento;
    int idSuscripcion;
    bool estado;
};

struct Artista {
    int idArtista;
    char nombre[100];
    char nacionalidad[50];
    bool estado;
};

struct Album {
    int idAlbum;
    char titulo[100];
    int idArtista;
    int anioPublicacion;
    bool estado;
};

struct Genero {
    int idGenero;
    char nombre[50];
};

struct Cancion {
    int idCancion;
    char nombre[100];
    int idAlbum;
    int idGenero;
    int duracionSegundos;
    bool estado;
};

struct Acceso {
    int idSuscriptor;
    int idCancion;
    DateTime fechaHora;
};

struct Lista {
    int idLista;
    char nombreLista[50];
    int idSuscriptorCreador;
    bool esPublica;
};

struct ListaCancion {
    int idLista;
    int idCancion;
};

struct Suscripcion {
    int idSuscripcion;
    char nombreSuscripcion[30];
    float precioMensual;
};


// --- DEFINICIÓN DE LA CLASE ---
class musicon
{
    public:

        musicon();

        virtual ~musicon();

        // --- DECLARACIONES DE FUNCIONES  ---
        // Pongo todas las funciones de reportes aquí, en 'public',

        // Función principal del menú
        void mostrarMenuReportes();

        // Las 6 funciones para los reportes
        void reporteReproduccionesAnuales();
        void reporteReproduccionesPorSuscriptor();
        void reporteReproduccionesPorGenero();
        void reporteReproduccionesPorCancion();
        void reporteListarCancionesPorGenero();
        void reporteCantidadCancionesPorArtista();

    protected:
        // No sé qué va aca me aparecio de la nada me perdi jaajj.
    private:

};

#endif // MUSICON_H

