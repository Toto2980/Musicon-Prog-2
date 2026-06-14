# 🎵 Musicón

Simulador de plataforma de música (estilo Spotify) por consola, escrito en **C++**.
Gestiona canciones, álbumes, artistas, géneros, suscriptores, playlists y un
historial de reproducciones, con persistencia en archivos binarios y reportes
estadísticos.

---

## ✨ Características

- **Gestión de catálogo**: canciones, álbumes, artistas y géneros (alta/baja/modificación/listado), con creación automática de entidades relacionadas al subir una canción.
- **Suscriptores**: registro, login, planes **Gratis** y **Pago** (con límite de playlists y _upsell_ al alcanzarlo).
- **Playlists**: creación, edición, eliminación y agregado de canciones (relación N:M canción↔playlist).
- **Reproducciones**: registro de accesos con fecha/hora.
- **9 reportes**: reproducciones anuales / por suscriptor / por género / por canción, canciones por género, canciones por artista, totales por usuario, búsqueda inteligente en playlists y ranking de más escuchadas.
- **Import/Export**: exportar catálogo a CSV, importar masivamente desde CSV (con resolución de conflictos) y backup binario.

## 🔐 Acceso

- Usuario administrador fijo: escribir **`admin`** en el login.
- Usuarios normales: registrarse primero (opción _Sign Up_) y luego iniciar sesión con el nombre.

---

## 🛠️ Compilación

Requiere un compilador con soporte **C++14** (probado con MinGW **g++ 6.3.0**).

### Opción 1 — Script (Windows)
```bat
build.bat        :: compila musicon.exe
build.bat run    :: compila y ejecuta
build.bat clean  :: limpia binarios
```

### Opción 2 — Make
```bash
mingw32-make        # o 'make'
mingw32-make run
```

### Opción 3 — Manual
```bash
g++ -std=c++14 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o musicon.exe
```

### Opción 4 — ZinjaI
Abrir `Musicon.zpr` y compilar normalmente.

---

## 🗂️ Estructura

```
Musicon/
├── include/        Headers (.h): entidades, persistencia, managers, utilidades
├── src/            Implementaciones (.cpp)
├── docs/           Documentación de arquitectura y diseño
├── main.cpp        Punto de entrada
├── build.bat       Script de compilación (Windows)
├── Makefile        Build con make / mingw32-make
└── *.dat           Datos persistidos (binarios)
```

Ver [`docs/ARQUITECTURA.md`](docs/ARQUITECTURA.md) para el detalle de capas y decisiones de diseño.

## 💾 Archivos de datos

| Archivo                 | Contenido                         |
|-------------------------|-----------------------------------|
| `canciones.dat`         | Canciones                         |
| `albumes.dat`           | Álbumes                           |
| `artistas.dat`          | Artistas                          |
| `generos.dat`           | Géneros                           |
| `suscriptores.dat`      | Usuarios suscriptores             |
| `playlists.dat`         | Playlists                         |
| `Listas_Canciones.dat`  | Canciones dentro de cada playlist |
| `accesos.dat`           | Historial de reproducciones       |

> Cada archivo es una secuencia de registros binarios de tamaño fijo
> (`sizeof(Entidad)` por registro).
