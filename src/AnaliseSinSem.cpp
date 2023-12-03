#include "AnaliseSinSem.h"
#include <iostream>

AnaliseSinSem::AnaliseSinSem()
    :lexico("teste.uai") {};

void AnaliseSinSem::botaErro(string msg, tipo_erro err, token_encontrado t) {
    erro novoerro;
    novoerro.msg = msg;
    novoerro.tipo = err;
    novoerro.linha = t.linha;
    novoerro.t = t.t;
    erros.push_back(novoerro);
}

void AnaliseSinSem::mostrarErros() {
    if (erros.size() > 0) {
        cout << "!!! " << erros.size() << " !!! ERROS ENCONTRADOS!" << endl; 
        for (auto e : erros) {
            cout << "Erro: linha " << e.linha << endl;
            cout << "Problema: " << e.msg << endl;
            cout << "Token encontrado: " << e.t.key << endl << endl;
        }
    } else
        cout << "Código compilado com sucesso, ô trem bão!" << endl;
}

void AnaliseSinSem::consomeQualquer(string alvo) {
    while (tokenAtual.t.key != alvo) {
        for (int i=0; i<38; i++)
            consome(lexico.getTokenPeloID(i).key, 1);
    }
}

bool AnaliseSinSem::atualIgual(string alvo) {
    return tokenAtual.t.key == alvo ;
}

void AnaliseSinSem::consome(string t, bool suprimir = 0) {
    if ( t == tokenAtual.t.key )
        tokenAtual = lexico.getToken();
    else
        if (not suprimir)
            botaErro("erro de sintaxe", errsin, tokenAtual); 
}

void AnaliseSinSem::declaracoes() {
    while(var_type()) {
        novoid();
        endline();
        variaveis.push_back(novavar);
    }
}

void AnaliseSinSem::novoid() {
    if (atualIgual("id")) {
        novavar.id = tokenAtual.encontrado;
        consome("id");
    } else
        botaErro("esperava-se um identificador", errsin, tokenAtual);
}

bool AnaliseSinSem::var_type() {
    if (atualIgual("queijo")) {
        consome("queijo");
        novavar.tipo = inteiro;
        return 1;
    } else if (atualIgual("pamonha")) {
        consome("pamonha");
        novavar.tipo = texto;
        return 1;
    }
    return 0;
}

void AnaliseSinSem:: comandos() {
    if (atualIgual("id") or
        atualIgual("caso") or
        atualIgual("faiz") or
        atualIgual("cata") or
        atualIgual("bota")) {
        comando();
        comandos();
    }
}

void AnaliseSinSem:: comando() {
    if (atualIgual("id"))
        atribuicao();
    else if (atualIgual("caso"))
        caso();
    else if (atualIgual("faiz"))
        faiz();
    else if (atualIgual("cata"))
        cata();
    else if (atualIgual("bota"))
        bota();
}

variavel AnaliseSinSem::getVarPeloID(string id) {
    for (auto i : variaveis) {
        if (id == i.id) {
            return i;
        }
    }
    variavel errvar;
    errvar.id = "erro";
    errvar.ivalor = 0;
    errvar.svalor = "";
    errvar.tipo = inteiro;
    return errvar;
}

void AnaliseSinSem::atribuicao() {
    novavar = getVarPeloID(tokenAtual.encontrado);
    consome("id");
    if (atualIgual("<>")) {
        consome("<>");
        conteudo();
        endline();
    } else
        botaErro("esperava-se um <>", errsin, tokenAtual);
}

void AnaliseSinSem::endline() {
    if (atualIgual("~"))
        consome("~");
    else
        botaErro("esperava-se um ~", errsin, tokenAtual);
}

void AnaliseSinSem::conteudo() {
    terminal();
    Elinha();
}

bool AnaliseSinSem::terminal() {
    if (atualIgual("num")) {
        consome("num");
    } else if (atualIgual("literal"))  {
        consome("literal");
    } else if (atualIgual("id")) {
        id();
    } else {
        botaErro("esperava-se um valor", errsin, tokenAtual);
        return 0;
    }
    return 1;
}

bool AnaliseSinSem::terminalatrib() {
    if (atualIgual("num")) {
        if (novavar.tipo == inteiro)
            consome("num");
        else
            botaErro("tentativa de atribuir valor textual em variavel numérica", errsem, tokenAtual);
    } else if (atualIgual("literal"))  {
        if (novavar.tipo == texto)
            consome("literal");
        else
            botaErro("tentativa de atribuir valor inteiro em variavel textual", errsem, tokenAtual);
    } else if (atualIgual("id")) {
        if (novavar.tipo == getVarPeloID(tokenAtual.encontrado).tipo)
            id();
        else if (novavar.tipo == inteiro and getVarPeloID(tokenAtual.encontrado).tipo == texto)
            botaErro("tentativa de atribuir valor de variavel inteira em variavel textual", errsem, tokenAtual);
        else if (novavar.tipo == texto and getVarPeloID(tokenAtual.encontrado).tipo == inteiro)
            botaErro("tentativa de atribuir valor de variavel textual em variavel inteira", errsem, tokenAtual);
    } else {
        botaErro("esperava-se um valor", errsin, tokenAtual);
        return 0;
    }
    return 1;
}

void AnaliseSinSem:: Elinha() {
    if (operador()) {
        terminal();
        Elinha();
    } 
}

bool AnaliseSinSem::operador() {
    if (atualIgual("mais"))
        consome("mais");
    else if (atualIgual("menos"))
        consome("menos");
    else if (atualIgual("veiz"))
        consome("veiz");
    else if (atualIgual("por"))
        consome("por");
    else
        return 0;
    return 1;
}

void AnaliseSinSem::caso() {
    consome("caso");
    expressao();
    if (not atualIgual("|"))
        botaErro("da um jeito nessa expressão ai meu fi, tudo errado!", errsin, tokenAtual);
    consomeQualquer("|");
    pipe();
    comandos();
    pipe();
    otoscaso();
}

void AnaliseSinSem:: otoscaso() {
    if (atualIgual("otos-caso")) {
        consome("otos-caso");
        pipe();
        comandos();
        pipe();
    } else if (atualIgual("otos-caso-se")) {
        consome("otos-caso-se");
        expressao();
        if (not atualIgual("|"))
            botaErro("da um jeito nessa expressão ai meu fi, tudo errado!", errsin, tokenAtual);
        consomeQualquer("|");
        pipe();
        comandos();
        pipe();
        otoscaso();
    }
}

bool AnaliseSinSem::pipe() {
    if (atualIgual("|")) {
        consome("|");
        return 1;
    } else {
        botaErro("esperave-se um |", errsin, tokenAtual);
        return 0;
    }
}

void AnaliseSinSem::expressao() {
    terminalLogico();
    Llinha();
}

bool AnaliseSinSem::terminalLogico() {
    if (atualIgual("num"))
        consome("num");
    else if (atualIgual("id"))
        id();
    else if (atualIgual("trem-bao"))
        consome("trem-baum");
    else if (atualIgual("trem-ruim"))
        consome("trem-ruim");
    else {
        botaErro("esperava-se um símbolo lógico", errsin, tokenAtual);
        return 0;
    }
    return 1;
}

void AnaliseSinSem::Mlinha() {
    if (operadorEOu()) {
        terminal();
        if (not atualIgual("|"))
            Llinha();
    }
}

bool AnaliseSinSem::operadorEOu() {
    if (atualIgual("e"))
        consome("e");
    else if (atualIgual("ou"))
        consome("ou");
    else {
        botaErro("esperava-se um e$ ou ou$", errsin, tokenAtual);
        return 0;
    }
    return 1;
}

void AnaliseSinSem::Llinha() {
    if (operadorLogico()) {
        terminal();
        if (not atualIgual("|"))
            Mlinha();
    }
}

bool AnaliseSinSem::operadorLogico() {
    if (atualIgual("mema-coisa"))
        consome("mema-coisa");
    else if (atualIgual("diferente-de"))
        consome("diferente-de");
    else if (atualIgual("maior-que"))
        consome("maior-que");
    else if (atualIgual("menor-que"))
        consome("menor-que");
    else if (atualIgual("maior-que-ou-mema-coisa"))
        consome("maior-que-ou-mema-coisa");
    else if (atualIgual("menor-que-ou-mema-coisa"))
        consome("menor-que-ou-mema-coisa");
    else if (atualIgual("aneim"))
        consome("aneim");
    else if (atualIgual("e"))
        consome("e");
    else if (atualIgual("ou"))
        consome("ou");
    else
        return 0;
    return 1;
}

void AnaliseSinSem::faiz() {
    consome("faiz");
    if (atualIgual("id"))
        id();
    else if (atualIgual("num"))
        consome("num");
    consome("rodada");
    pipe();
    comandos();
    pipe();
}

void AnaliseSinSem::cata() {
    consome("cata");
    id();
    endline();
}

void AnaliseSinSem::id() {
    if (atualIgual("id"))
        consome("id");
    else
        botaErro("esperava-se um identificador", errsin, tokenAtual);
}

void AnaliseSinSem::literal() {
    if (atualIgual("literal"))
        consome("literal");
    else
        botaErro("esperava-se um literal", errsin, tokenAtual);
}

void AnaliseSinSem::bota() {
    consome("bota");
    if (atualIgual("literal"))
        consome("literal");
    else if (atualIgual("id"))
        id();
    endline();
}

void AnaliseSinSem::uai() {
    if (atualIgual("uai"))
        consome("uai");
    else
        botaErro("esperava-se um 'uai', uai!", errsin, tokenAtual);
}

void AnaliseSinSem::analisar() {
    lexico.carregarDicionarioDeTokens();
    if (not lexico.abrirArquivo()) {
        cout << "Arquivo não encontrado!" << endl;
    }
    tokenAtual = lexico.getToken();
    uai();
    pipe();
    declaracoes();
    comandos();
    pipe();
}