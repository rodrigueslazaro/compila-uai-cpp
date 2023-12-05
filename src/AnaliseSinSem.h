#pragma once
#include "AnaliseLexica.h"
#include "Token.h"

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

typedef enum {
    inteiro,
    texto
} tipo_var;

typedef struct {
    string id;
    tipo_var tipo;
    int ivalor;
    string svalor;
} variavel;

class AnaliseSinSem {
public:
    AnaliseSinSem();
    ~AnaliseSinSem(){};
    void analisar(string arquivo);
    void mostrarErros();
private:
    token_encontrado tokenAtual;
    AnaliseLexica lexico;
    void botaErro(string msg, tipo_erro err, token_encontrado t);
    bool atualIgual(string alvo);
    void consomeQualquer(string alvo);
    void consome(string t, bool suprimir);
    variavel getVarPeloID(string id);
    bool naoExiste(string v);
    vector<erro> erros;
    vector<variavel> variaveis;
    variavel novavar;
    variavel varatrib;

    void declaracoes();
    bool var_type();
    void comandos();
    void comando();
    void atribuicao();
    void endline();
    void conteudo();
    bool terminal();
    void terminalnum();
    bool terminalatrib();
    void Elinha();
    bool operador();
    void caso();
    void otoscaso();
    bool pipe();
    void expressao();
    bool terminalLogico();
    void Mlinha();
    bool operadorEOu();
    void Llinha();
    bool operadorLogico();
    void faiz();
    void cata();
    void id();
    void novoid();
    void literal();
    void bota();
    void uai();
};
