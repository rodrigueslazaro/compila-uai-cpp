#pragma once
#include "AnaliseLexica.h"
#include "Token.h"

// tabelaSimbolos = {}
// arquivo_tabela = None
// comentario = True
// tokenAtual = None
// arquivo = None
// buffer = ''
// linha = [0]
// endDeclaracoes = False

typedef enum {
    errsin,
    errsem
} tipo_erro;

typedef struct {
    tipo_erro tipo;
    int linha;
    string msg;
    token t;
} erro;

class AnaliseSinSem {
public:
    AnaliseSinSem();
    ~AnaliseSinSem(){};
private:
    token_encontrado tokenAtual;
    AnaliseLexica lexico;
    void botaErro(string msg, tipo_erro err, token_encontrado t);
    void mostraErros();
    bool atualIgual(string alvo);
    void consomeQualquer(string alvo);
    void consome(string t, bool suprimir = 0);
    vector<erro> erros;

    void declaracoes();
    bool var_type();
    void comandos();
    void comando();
    void atribuicao();
    void endline();
    void conteudo();
    void terminal();
    void Elinha();
    void operado();
    void caso();
    void otoscaso();
    bool pipe();
    void expressao();
    bool terminalLogico();
    void Mlinha();
    bool operadorEOu();
    void LLinha();
    bool operadorLogico();
    void faiz();
    void cata();
    void id();
    void bota();
    void uai();
};
