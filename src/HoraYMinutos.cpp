#include <iostream>
#include "../include/HoraYMinutos.h"
#include <string>

using namespace std;

/**
 * Este archivo implementa la clase HoraYMinutos, que maneja horas y minutos para el sistema Musicon.
 * Permite crear, mostrar y comparar tiempos simples.
 */

/**
 * Prepara una nueva hora vacía.
 * Establece la hora y minutos a cero, como si fuera medianoche.
 */
HoraYMinutos::HoraYMinutos(){
    _hora = 0;
    _minutos = 0;
}

/**
 * Crea una hora específica con hora y minutos dados.
 * Parámetros: hora (0-23, donde 0 es medianoche), minutos (0-59).
 */
HoraYMinutos::HoraYMinutos(int hora, int minutos)
{
    _hora = hora;
    _minutos = minutos;
}

/**
 * Dice cuál es la hora actual guardada.
 * Retorna: El número de la hora (ej. 14 para las 2 PM).
 */
int HoraYMinutos::getHora(){
    return _hora;
}

/**
 * Dice cuáles son los minutos actuales guardados.
 * Retorna: El número de minutos (ej. 30 para media hora).
 */
int HoraYMinutos::getMinutos(){
    return _minutos;
}

/**
 * Cambia la hora a un nuevo valor.
 * Parámetros: hora - La nueva hora a guardar.
 */
void HoraYMinutos::setHora(int hora) {
    _hora = hora;
}

/**
 * Cambia los minutos a un nuevo valor.
 * Parámetros: minutos - Los nuevos minutos a guardar.
 */
void HoraYMinutos::setMinutos(int minutos) {
    _minutos = minutos;
}

/**
 * Convierte la hora y minutos a un texto fácil de leer.
 * Retorna: Un texto como "14:30" para las 2:30 PM.
 */
std::string HoraYMinutos::toString() {

    string minStr = std::to_string(_minutos);
    if(_minutos < 10) minStr = "0" + minStr; // Agrega un cero al inicio si es necesario para que se vea bien

    return std::to_string(_hora) + ":" + minStr;
}
