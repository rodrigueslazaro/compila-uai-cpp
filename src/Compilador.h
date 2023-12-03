#pragma once
#include <vector>
#include "Token.h"

class Compilador {
public:
    Compilador(){};
    ~Compilador(){};
    int fazerAnaliseLexica();
    void compilar();
private:
};