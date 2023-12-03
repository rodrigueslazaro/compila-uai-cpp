#pragma once
#include <string>
using namespace std;

typedef struct {
    int id;
    string key;
    string desc;
} token;

typedef struct {
    token t;
    string encontrado;
    int linha;
} token_encontrado;

