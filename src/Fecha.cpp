/**
 * Esta clase implementa Fecha, que combina día/mes/año con un objeto HoraYMinutos.
 * Se usa en todo el sistema para registrar momentos exactos:
 *   - Accesos: cuándo se reprodujo una canción.
 *   - Playlists: cuándo se creó la lista.
 *   - DetallePlaylist: cuándo se agregó una canción a la lista.
 *
 * NOTA DE DISEÑO:
 *   - Fecha tiene TRES constructores:
 *     1. Fecha() — sin parámetros: crea una fecha vacía (0/0/0 00:00).
 *     2. Fecha(minutos, hora, dia, mes, anio) — para timestamps completos (accesos).
 *     3. Fecha(dia, mes, anio) — para fechas simples sin hora (playlists, nacimientos).
 *   - Tener varios constructores con diferente cantidad de parámetros se llama SOBRECARGA.
 */

#include "../include/Fecha.h"
#include "../include/InputHelper.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

/** Constructor vacío: crea una fecha con todos los campos en cero. */
Fecha::Fecha() {
    _dia = 0;
    _mes = 0;
    _anio = 0;
    _objetoHora = HoraYMinutos(); // Hora 0:00 por defecto
}

/**
 * Constructor completo con fecha y hora.
 * Se usa en Accesos para registrar el momento exacto de reproducción.
 * Parámetros: minutos, hora, dia, mes, anio.
 */
Fecha::Fecha(int minutos, int hora, int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
    _objetoHora = HoraYMinutos(hora, minutos);
}

/**
 * Constructor de solo fecha (sin hora).
 * Se usa para fechas de creación de playlists y fechas de nacimiento.
 * Parámetros: dia, mes, anio (la hora queda en 0:00).
 */
Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
    _objetoHora = HoraYMinutos(); // Sin hora: 0:00
}

/** Getters: devuelven cada componente de la fecha. */
int Fecha::getDia() { return _dia; }
int Fecha::getMes() { return _mes; }
int Fecha::getAnio() { return _anio; }
HoraYMinutos Fecha::getHorario() { return _objetoHora; }

/** Setters: permiten modificar componentes individuales de la fecha. */
void Fecha::setDia(int dia) { _dia = dia; }
void Fecha::setMes(int mes) { _mes = mes; }
void Fecha::setAnio(int anio) { _anio = anio; }
void Fecha::setHorario(HoraYMinutos horario) { _objetoHora = horario; }

/**
 * Solicita todos los componentes de la fecha al usuario por consola.
 * Usa pedirEnteroRango para forzar valores válidos (ej: mes entre 1 y 12).
 */
void Fecha::Cargar() {
    _dia = InputHelper::pedirEnteroRango("Dia: ", 1, 31);
    _mes = InputHelper::pedirEnteroRango("Mes: ", 1, 12);
    _anio = InputHelper::pedirEnteroRango("Anio: ", 1900, 2100);

    int hora = InputHelper::pedirEnteroRango("Hora: ", 0, 23);
    int minutos = InputHelper::pedirEnteroRango("Minutos: ", 0, 59);
    _objetoHora = HoraYMinutos(hora, minutos);
}

/** Imprime la fecha usando el método toString(). */
void Fecha::Mostrar() {
    cout << toString();
}

/**
 * Convierte la fecha a un string con formato "DD/MM/AAAA HH:MM".
 * Usa setw(2) y setfill('0') para agregar cero a la izquierda si el día o mes es menor a 10.
 * Ejemplo: día 5 de enero de 2024 a las 9:07 → "05/01/2024 09:07".
 */
std::string Fecha::toString() {
    ostringstream salida;
    salida << setfill('0') << setw(2) << _dia << "/"
           << setw(2) << _mes << "/"
           << _anio << " "
           << setw(2) << _objetoHora.getHora() << ":"
           << setw(2) << _objetoHora.getMinutos();
    return salida.str();
}
