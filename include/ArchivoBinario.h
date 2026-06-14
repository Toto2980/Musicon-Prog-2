/*
 * ArchivoBinario.h
 * Motor de persistencia generico para registros de tamano fijo.
 *
 * Antes existian 5 clases casi identicas (ArchivoCanciones, ArchivoArtistas,
 * ArchivoAlbum, ArchivoGeneros, ArchivoSuscriptores) y ademas varias entidades
 * repetian la misma logica de fopen/fread/fwrite embebida. Toda esa duplicacion
 * (~400 lineas) ahora vive en un unico lugar parametrizado por el tipo T.
 *
 * Requisito sobre T: debe ser un tipo "volcable" en binario, es decir, sin
 * punteros internos, sin std::string ni metodos virtuales (las entidades del
 * sistema usan char[] justamente por esto). El layout en disco es exactamente
 * sizeof(T) bytes por registro, igual que el codigo original, de modo que los
 * archivos .dat existentes siguen siendo compatibles.
 */

#ifndef ARCHIVOBINARIO_H
#define ARCHIVOBINARIO_H

#include <cstdio>
#include <string>
#include <vector>

template <class T>
class ArchivoBinario {
    private:
        std::string _ruta;

    public:
        explicit ArchivoBinario(const std::string& ruta) : _ruta(ruta) {}

        /** Ruta del archivo gestionado. */
        const std::string& ruta() const { return _ruta; }

        /** Cantidad de registros almacenados. */
        int contar() const {
            FILE* f = std::fopen(_ruta.c_str(), "rb");
            if (f == nullptr) return 0;
            std::fseek(f, 0, SEEK_END);
            long bytes = std::ftell(f);
            std::fclose(f);
            if (bytes <= 0) return 0;
            return static_cast<int>(bytes / static_cast<long>(sizeof(T)));
        }

        /** Lee el registro en la posicion dada sobre 'reg'. Retorna true si lo leyo. */
        bool leer(int pos, T& reg) const {
            if (pos < 0) return false;
            FILE* f = std::fopen(_ruta.c_str(), "rb");
            if (f == nullptr) return false;
            std::fseek(f, static_cast<long>(pos) * sizeof(T), SEEK_SET);
            bool ok = std::fread(&reg, sizeof(T), 1, f) == 1;
            std::fclose(f);
            return ok;
        }

        /** Agrega un registro al final del archivo. */
        bool agregar(const T& reg) const {
            FILE* f = std::fopen(_ruta.c_str(), "ab");
            if (f == nullptr) return false;
            bool ok = std::fwrite(&reg, sizeof(T), 1, f) == 1;
            std::fclose(f);
            return ok;
        }

        /** Sobrescribe el registro en la posicion dada (actualizacion in-place). */
        bool escribir(int pos, const T& reg) const {
            if (pos < 0) return false;
            FILE* f = std::fopen(_ruta.c_str(), "rb+");
            if (f == nullptr) return false;
            std::fseek(f, static_cast<long>(pos) * sizeof(T), SEEK_SET);
            bool ok = std::fwrite(&reg, sizeof(T), 1, f) == 1;
            std::fclose(f);
            return ok;
        }

        /** Carga todos los registros en memoria de una sola pasada.
         *  Evita el patron O(n^2) de reabrir el archivo en cada lectura. */
        std::vector<T> leerTodos() const {
            std::vector<T> regs;
            FILE* f = std::fopen(_ruta.c_str(), "rb");
            if (f == nullptr) return regs;
            T reg;
            while (std::fread(&reg, sizeof(T), 1, f) == 1) {
                regs.push_back(reg);
            }
            std::fclose(f);
            return regs;
        }

        /** Reescribe el archivo completo con los registros dados. */
        bool guardarTodos(const std::vector<T>& regs) const {
            FILE* f = std::fopen(_ruta.c_str(), "wb");
            if (f == nullptr) return false;
            bool ok = true;
            if (!regs.empty()) {
                ok = std::fwrite(regs.data(), sizeof(T), regs.size(), f) == regs.size();
            }
            std::fclose(f);
            return ok;
        }
};

#endif // ARCHIVOBINARIO_H
