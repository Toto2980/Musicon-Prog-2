/**
 * Este archivo define la clase Accesos, que registra cuándo un usuario reproduce una canción.
 * Mantiene un historial (log) de reproducciones con ID de usuario, canción y fecha/hora.
 */

#ifndef ACCESOS_H
#define ACCESOS_H

#include "Fecha.h"

/** Representa un registro de acceso o reproducción de una canción por un suscriptor. */
class Accesos {
    private:
        int _idSuscriptor;
        int _idCancion;
        Fecha _fechaHora;

    public:
        /** Constructor por defecto de la clase Accesos. */
        Accesos();

        // --- SETTERS ---
        /** Establece el ID del suscriptor que realizó el acceso. */
        void setIdSuscriptor(int id);
        /** Establece el ID de la canción accedida. */
        void setIdCancion(int id);
        /** Establece la fecha y hora del acceso. */
        void setFechaHora(Fecha fecha);

        // --- GETTERS ---
        /** Obtiene el ID del suscriptor. */
        int getIdSuscriptor();
        /** Obtiene el ID de la canción. */
        int getIdCancion();
        /** Obtiene la fecha y hora del acceso. */
        Fecha getFechaHora();

        // --- METODOS DE ARCHIVO (NUEVO) ---
        // Accesos es un log (historial), generalmente solo se agrega y se lee secuencialmente.
        /** Guarda el registro de acceso en el archivo. */
        bool Guardar();
        /** Lee un registro de acceso desde el archivo en la posición especificada. */
        bool Leer(int pos);
        /** Obtiene la cantidad total de registros de acceso en el archivo. */
        int ObtenerCantidadRegistros();

        // No solemos "Modificar" o "Buscar por ID" un acceso porque es un log histórico,
        // pero Leer() y ObtenerCantidad son vitales para los reportes.
};

#endif // ACCESOS_H
