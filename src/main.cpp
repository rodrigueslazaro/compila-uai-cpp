#include <iostream>
#include <vector>
#include "Compilador.h"

int main() {
    Compilador compilador = Compilador();

    if (compilador.fazerAnaliseLexica())
        cout << "Análise léxica concluida com sucesso!" << endl;
    else 
        cout << "Análise léxica falhou!!" << endl;
    
}