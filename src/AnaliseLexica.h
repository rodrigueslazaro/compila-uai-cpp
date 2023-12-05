#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Token.h"
using namespace std;

class AnaliseLexica {
public:
    AnaliseLexica(string nomeArquivo);
    ~AnaliseLexica();

    void carregarDicionarioDeTokens();
    token_encontrado getToken();
    bool abrirArquivo();
    token getTokenPeloID(int id);
    void setArquivo(string nome) { nomeArquivo = nome; }
private:
    void getChar();
    token_encontrado retorno(string chave, string encontrado);
    token getTokenPelaChave(string chave);

    vector<token> tokens;
    ifstream arquivo;
    string nomeArquivo;
    int estado;
    char car;
    string lexema;
    int linha;
};
