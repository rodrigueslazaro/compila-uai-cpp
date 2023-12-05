#pragma once
#include <vector>
#include "Token.h"

class Compilador {
public:
    Compilador(string arquivo);
    ~Compilador(){};
    int fazerAnaliseLexica();
    void compilar();
private:
    string arquivo;
};
