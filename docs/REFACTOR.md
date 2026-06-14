# Refactor profesional — bitácora de cambios

Resumen de la modernización aplicada al código original. Objetivo: código más
profesional, mantenible y sin duplicación, **conservando todas las features y la
compatibilidad de los archivos `.dat`**. Objetivo de lenguaje: **C++14**
(compatible con MinGW g++ 6.3.0).

## Qué cambió

### Persistencia unificada
- Nuevo `ArchivoBinario<T>` (template, header-only): único motor de E/S binaria.
- Las 5 clases `Archivo*` y la persistencia *Active Record* embebida en
  `Playlist`, `Album`, `Genero`, `DetallePlaylist` y `Accesos` ahora **delegan**
  en ese motor. Se eliminaron ~400 líneas casi idénticas.
- Las búsquedas (`BuscarPosicion`, `BuscarPorNombre`, …) cargan los registros en
  una sola pasada (`leerTodos`) en vez de reabrir el archivo en cada lectura.

### Utilidades centralizadas
- `Texto`: comparación sin mayúsculas, `trim`, `contiene`. Antes estaba
  **duplicado** en `InputHelper`, `CancionManager`, `PlaylistManager` y
  `ReporteManager`; ahora hay una sola implementación y todos delegan en ella.
- `Consola`: limpiar pantalla y pausar **sin `system()`**. Se reemplazaron ~15
  llamadas a `system("cls")` / `system("pause")` repartidas por el código.
- `Constantes` (`namespace cfg`): se eliminaron números mágicos
  (`admin = -1`, tipos `1`/`2`, límite `3` de playlists, top `5` del ranking) y
  se centralizaron las rutas de los `.dat`.

### Controlador `musicon`
- Reescrito limpio: encoding corregido, formato consistente, `Consola` en lugar
  de `system()`, constantes en lugar de literales, `menuPrincipalAdmin` /
  `menuPrincipalUsuario` separados.
- Se eliminaron declaraciones muertas del header (métodos declarados y nunca
  implementados).
- `registrarAcceso` ahora delega en `CancionManager::RegistrarAcceso` (antes la
  lógica estaba duplicada).

### Proyecto
- `build.bat`, `Makefile` y `.gitignore` agregados.
- `README.md` y `docs/` (antes vacío) con documentación de uso y arquitectura.
- Compila sin warnings con `-Wall -Wextra`.

## Qué NO cambió (a propósito)
- **Formato de los `.dat`**: el layout binario de cada entidad es idéntico
  (mismos campos, tipos y orden), por lo que los datos existentes siguen
  funcionando. Verificado leyendo los `.dat` actuales tras el refactor.
- **Features**: todas las funciones del sistema se conservan (CRUD, 9 reportes,
  import/export CSV, backup, playlists con límite y upsell, login admin, etc.).
- **Las entidades siguen usando `char[]`** (correcto para records binarios; no se
  reemplazó por `std::string` porque rompería la serialización y el formato).

## Verificación
- Compilación limpia (`-Wall -Wextra`, C++14).
- Lectura de `.dat` existentes correcta (canciones, géneros, suscriptores).
- Prueba end-to-end por consola: login admin → listado detallado con joins
  (artista/álbum/género) → navegación de menús → salida.
