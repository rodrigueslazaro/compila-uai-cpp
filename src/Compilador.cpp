#include <iostream>
#include "Compilador.h"
#include "AnaliseLexica.h"
#include "AnaliseSinSem.h"

Compilador::Compilador(string arquivo)
    :arquivo(arquivo) {};

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

void Compilador::compilar() {
    AnaliseSinSem analisador = AnaliseSinSem();
    analisador.analisar(arquivo);
    analisador.mostrarErros();
}
