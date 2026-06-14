@echo off
REM ============================================================
REM  Musicon - Script de compilacion (MinGW g++ / C++14)
REM  Uso:  build.bat          -> compila a musicon.exe
REM        build.bat run      -> compila y ejecuta
REM        build.bat clean    -> borra binarios y objetos
REM ============================================================

setlocal
set CXX=g++
set CXXFLAGS=-std=c++14 -Wall -Wextra -Iinclude
set OUT=musicon.exe
set SRC=main.cpp src\*.cpp

if "%1"=="clean" (
    echo Limpiando...
    if exist %OUT% del %OUT%
    if exist obj rmdir /s /q obj
    echo Listo.
    goto :eof
)

echo Compilando Musicon ^(C++14^)...
%CXX% %CXXFLAGS% %SRC% -o %OUT%
if errorlevel 1 (
    echo.
    echo [ERROR] La compilacion fallo.
    exit /b 1
)
echo [OK] Compilacion exitosa -^> %OUT%

if "%1"=="run" (
    echo.
    echo Ejecutando...
    %OUT%
)
endlocal
