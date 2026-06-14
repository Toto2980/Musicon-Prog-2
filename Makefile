# ============================================================
#  Musicon - Makefile (para mingw32-make o make con MinGW)
#  Objetivos:
#    make          -> compila musicon.exe
#    make run      -> compila y ejecuta
#    make clean    -> borra el ejecutable
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -Iinclude
OUT      := musicon.exe
SOURCES  := main.cpp $(wildcard src/*.cpp)

all: $(OUT)

$(OUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(OUT)

run: all
	./$(OUT)

clean:
	-del /q $(OUT) 2>nul

.PHONY: all run clean
