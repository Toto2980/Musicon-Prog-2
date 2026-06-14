# Arquitectura de Musicón

El sistema está organizado en **capas** con responsabilidades bien separadas.
Cada pieza tiene un único propósito y se comunica con las demás a través de
interfaces claras.

```
┌───────────────────────────────────────────────┐
│  main.cpp                                       │  Punto de entrada
└───────────────────────────────────────────────┘
                      │
┌───────────────────────────────────────────────┐
│  musicon (controlador)                          │  Navegación de menús
│  - menús de bienvenida / admin / usuario        │  (sin lógica de negocio)
└───────────────────────────────────────────────┘
                      │ delega en
┌───────────────────────────────────────────────┐
│  Managers                                       │  Lógica de negocio
│  CancionManager, PlaylistManager,               │  (CRUD, reglas, reportes,
│  SuscriptorManager, ArtistaManager,             │   import/export)
│  GeneroManager, ReporteManager                  │
└───────────────────────────────────────────────┘
                      │ usan
┌──────────────────────────┐   ┌─────────────────┐
│  Entidades               │   │  Persistencia    │
│  Canciones, Album,       │   │  ArchivoBinario<T>│ ← motor genérico
│  Artista, Genero,        │   │  + clases Archivo*│
│  Suscriptor, Playlist,   │   │  (repositorios)   │
│  DetallePlaylist,        │   └─────────────────┘
│  Accesos, Fecha,         │            │
│  HoraYMinutos            │            ▼
└──────────────────────────┘     Archivos .dat (binarios)

        Utilidades transversales: Texto · Consola · InputHelper · Constantes
```

## Capas

### 1. Controlador (`musicon`)
Solo navegación de menús. Mantiene la sesión (`_idUsuarioLogueado`) y delega
cada acción en el manager correspondiente. No abre archivos ni implementa reglas.

### 2. Managers
Contienen la lógica de negocio: validaciones, reglas (p. ej. límite de playlists
del plan gratuito), generación de reportes y operaciones de import/export.

### 3. Entidades
Representan los datos en memoria (canción, álbum, etc.). Usan **arreglos de
caracteres de tamaño fijo** (`char[]`), no `std::string`, porque se vuelcan tal
cual a disco en binario. Esto es deliberado: un `std::string` contiene punteros
internos y no es serializable con `fwrite`.

### 4. Persistencia — `ArchivoBinario<T>`
Motor de persistencia **genérico** (template) que centraliza toda la E/S binaria:
`contar`, `leer`, `agregar`, `escribir`, `leerTodos`, `guardarTodos`.

Antes existían 5 clases `Archivo*` casi idénticas y varias entidades repetían la
misma lógica de `fopen`/`fread`/`fwrite` embebida (~400 líneas duplicadas). Hoy
todo eso vive en un único lugar parametrizado por el tipo `T`, y las clases
`Archivo*` quedan como **repositorios finos** que sólo aportan las consultas
propias del dominio (buscar por nombre, por id, "buscar o crear"…).

**Compatibilidad de datos:** el formato en disco es exactamente `sizeof(T)` bytes
por registro, igual que el código original. Los archivos `.dat` existentes
siguen siendo válidos sin migración.

## Utilidades transversales

| Componente     | Responsabilidad                                                      |
|----------------|---------------------------------------------------------------------|
| `Texto`        | Comparar sin mayúsculas, `trim`, `contiene`, `aMinusculas` (antes duplicado en 3 archivos). |
| `Consola`      | Limpiar pantalla y pausar **sin** `system()` (API nativa de Windows / ANSI). |
| `InputHelper`  | Entrada robusta de enteros/cadenas; delega cadenas en `Texto` y pausa en `Consola`. |
| `Constantes`   | Reglas de negocio y rutas de archivos con nombre (sin "números mágicos"). |

## Decisiones de diseño destacadas

- **Sin `system("cls")` / `system("pause")`**: se reemplazaron por `Consola`,
  evitando lanzar un shell (más rápido, seguro y centralizado).
- **`namespace cfg`** para constantes (no `musicon`, para no chocar con la clase).
- **C++14** como objetivo (compatible con MinGW 6.3.0): se usan `std::vector`,
  `std::unordered_map`, lambdas y templates, pero no características de C++17+.
- **Eliminación lógica**: las entidades llevan un campo `_estado` (activo/inactivo)
  en vez de borrar registros físicamente.
