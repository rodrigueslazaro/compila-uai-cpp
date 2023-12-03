#include "Compilador.h"
#include <iostream>
#include "AnaliseLexica.h"

int Compilador::fazerAnaliseLexica() {
    AnaliseLexica analisador_lexico = AnaliseLexica("teste.uai");
    analisador_lexico.carregarDicionarioDeTokens();
    if (not analisador_lexico.abrirArquivo()) {
        cout << "Arquivo não encontrado!" << endl;
        return 0;
    }
    token_encontrado token;
    while (token.t.key != "end") {
        token = analisador_lexico.getToken();
        cout << "token: " << token.t.key <<
                " encontrado: " << token.encontrado <<
                " linha: " << token.linha << endl;
    }
    return 1;
}
