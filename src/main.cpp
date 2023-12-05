#include <iostream>
#include <vector>
#include "Compilador.h"

int main(int argc, char* argv[]) {
    Compilador compilador = Compilador(argv[1]);
    compilador.compilar();
}
