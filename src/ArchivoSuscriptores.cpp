/**
 * PATRON: Repository
 * Esta clase encapsula todo el acceso al archivo binario de suscriptores (usuarios).
 * La capa SuscriptorManager no sabe como se guardan los datos — solo pide Guardar/Leer/Buscar.
 *
 * COMO FUNCIONA UN ARCHIVO BINARIO EN ESTE PROYECTO:
 *   - Los objetos Suscriptor se escriben uno tras otro en el archivo, como un arreglo en disco.
 *   - Cada registro ocupa exactamente sizeof(Suscriptor) bytes (todos del mismo tamano).
 *   - Para leer el registro numero 'pos', saltamos pos * sizeof(Suscriptor) bytes desde el inicio.
 *   - Para saber cuantos registros hay: tamano total del archivo / sizeof(Suscriptor).
 *
 * ELIMINACION LOGICA vs FISICA:
 *   - No borramos registros del archivo (eso desplazaria todos los demas y romperia los IDs).
 *   - En cambio, marcamos estado=false. Asi las playlists siguen referenciando al suscriptor.
 */

#include "../include/ArchivoSuscriptores.h"
#include "../include/InputHelper.h"
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

/** Guarda el nombre del archivo en el atributo privado. */
ArchivoSuscriptores::ArchivoSuscriptores(string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

/**
 * Agrega un suscriptor al FINAL del archivo.
 * "ab" = append binary: si el archivo no existe, lo crea; si existe, escribe al final.
 * fwrite escribe sizeof(Suscriptor) bytes del objeto reg en el archivo.
 */
bool ArchivoSuscriptores::Guardar(Suscriptor reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return ok;
}

/**
 * Lee el suscriptor en la posicion 'pos' del archivo.
 * "rb" = read binary: solo lectura.
 * fseek salta exactamente pos * sizeof(Suscriptor) bytes desde el inicio (SEEK_SET).
 * Si el archivo no existe o la posicion es invalida, retorna un suscriptor con estado=false.
 */
Suscriptor ArchivoSuscriptores::Leer(int pos) {
    Suscriptor reg;
    reg.setEstado(false); // Valor por defecto si la lectura falla
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Suscriptor), SEEK_SET);
    fread(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return reg;
}

/**
 * Calcula la cantidad total de registros en el archivo.
 * Tecnica: ir al final del archivo (SEEK_END), leer la posicion con ftell()
 * y dividir por el tamano de cada registro.
 */
int ArchivoSuscriptores::ObtenerCantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);       // Va al final del archivo
    int cant = ftell(p) / sizeof(Suscriptor); // ftell() = bytes totales
    fclose(p);
    return cant;
}

/**
 * Genera un ID autoincremental leyendo el ultimo registro guardado.
 * Si el archivo esta vacio, devuelve 1 (primer ID).
 * El offset negativo fseek(p, -sizeof(Suscriptor), SEEK_END) apunta al ultimo registro.
 */
int ArchivoSuscriptores::GenerarIDNuevo() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 1; // Si el archivo no existe, el primer ID es 1
    fseek(p, 0, SEEK_END);
    long size = ftell(p);
    if (size <= 0) {
        fclose(p);
        return 1; // Archivo vacio: primer ID es 1
    }
    // Retrocede al inicio del ultimo registro
    fseek(p, -static_cast<long>(sizeof(Suscriptor)), SEEK_END);
    Suscriptor ultimo;
    if (fread(&ultimo, sizeof(Suscriptor), 1, p) != 1) {
        fclose(p);
        return 1;
    }
    fclose(p);
    return ultimo.getIdSuscriptor() + 1; // Siguiente ID = ultimo + 1

}

/**
 * Lee todos los suscriptores en un arreglo dinamico.
 * El llamador es responsable de liberar la memoria con delete[].
 * Se usa en ListarActivos/Inactivos/Todos del SuscriptorManager.
 */
Suscriptor* ArchivoSuscriptores::LeerTodos(int &cantidad) {
    cantidad = ObtenerCantidadRegistros();
    if (cantidad <= 0) return nullptr;

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) {
        cantidad = 0;
        return nullptr;
    }

    // Reserva memoria para todos los registros de una sola vez (mas eficiente que leer uno por uno)
    Suscriptor *buffer = new Suscriptor[cantidad];
    int leidos = fread(buffer, sizeof(Suscriptor), cantidad, p);
    fclose(p);

    if (leidos != cantidad) {
        cantidad = leidos; // Ajusta si no se leyeron todos
    }

    
    return buffer;


}

/**
 * Sobrescribe el registro en la posicion 'pos' con el nuevo valor.
 * "rb+" = read+write binary: permite modificar sin borrar el resto del archivo.
 * fseek ubica el puntero exactamente en el registro a modificar.
 * Esto es lo que hace posible la "eliminacion logica": modificamos estado=false en su lugar.
 */
bool ArchivoSuscriptores::Modificar(int pos, Suscriptor reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Suscriptor), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, p);
    fclose(p);
    return ok;
}

/**
 * Busca la posicion (indice en el archivo) de un suscriptor por su ID.
 * Recorre todos los registros secuencialmente hasta encontrar el ID y que este activo.
 * Retorna: posicion si lo encuentra, -1 si no existe o esta dado de baja.
 */
int ArchivoSuscriptores::BuscarPosicion(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        if(aux.getIdSuscriptor() == id && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca la posicion de un suscriptor por su nombre de usuario (case-insensitive).
 * Usa InputHelper::trim para ignorar espacios al inicio/fin antes de comparar.
 * Se usa en el login para encontrar al usuario que quiere entrar al sistema.
 */
int ArchivoSuscriptores::BuscarPosicionPorNombre(const char* nombre) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    std::string nombreBuscado = InputHelper::trim(nombre); // Limpia espacios
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        std::string nombreArchivo = InputHelper::trim(aux.getNombre());
        if(InputHelper::sonIgualesSinMayusculas(nombreArchivo, nombreBuscado) && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

/**
 * Busca la posicion de un suscriptor por su DNI exacto (case-sensitive con strcmp).
 * A diferencia de BuscarPosicionPorNombre, el DNI debe coincidir exactamente.
 */
int ArchivoSuscriptores::BuscarPosicionPorDNI(const char* dni) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;
    Suscriptor aux;
    int pos = 0;
    while(fread(&aux, sizeof(Suscriptor), 1, p)) {
        if(strcmp(aux.getDni(), dni) == 0 && aux.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
