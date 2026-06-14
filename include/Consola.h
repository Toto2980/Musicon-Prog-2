/*
 * Consola.h
 * Abstraccion de la interaccion con la terminal.
 *
 * Reemplaza las llamadas dispersas a system("cls") y system("pause"), que son
 * lentas (lanzan un shell), poco portables e inseguras. Aqui se concentran el
 * limpiado de pantalla, la pausa y la configuracion inicial de la consola.
 */

#ifndef CONSOLA_H
#define CONSOLA_H

namespace Consola {

    /** Configura la consola al iniciar el programa (codepage, etc.). */
    void iniciar();

    /** Limpia la pantalla sin lanzar un proceso externo. */
    void limpiar();

    /** Detiene la ejecucion hasta que el usuario presiona ENTER. */
    void pausa();

} // namespace Consola

#endif // CONSOLA_H
