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

void AnaliseSinSem::mostraErros() {
    if (erros.size() > 0) {
        cout << "!!! " << erros.size() << " !!! ERROS ENCONTRADOS!" << endl; 
        for (auto e : erros) {
            cout << "Erro: linha " << e.linha << endl;
            cout << "Proglema: " << e.msg << endl;
            cout << "Token encontrado: " << e.t.key << endl << endl;
        }
    } else
        cout << "Código compilado com sucesso, ô trem bão!" << endl;
}
void AnaliseSinSem::consomeQualquer(string alvo) {
    int i = 0;
    while (tokenAtual.t.key != alvo) {
        consome(lexico.getTokenPeloID(i), 1);
        i++;
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
        id()
        endline()
    }
}

bool AnaliseSinSem::var_type() {
    if (atualIgual("queijo")) {
        consome("queijo");
        return 1;
    } else if (atualIgual("pamonha")) {
        consome("pamonha");
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

void AnaliseSinSem:: atribuicao() {
    consome("id");
    if (atualIgual("<>")) {
        consome("<>");
        conteudo();
        endline();
    } else
        botaErro("esperava-se um <>", errsin, tokenAtual);
}

void AnaliseSinSem::endline():
    if atualIgual("~")
        consome("~");
    else
        botaErro("esperava-se um ~", errsin, tokenAtual);

void AnaliseSinSem:: conteudo():
    terminal()
    Elinha()

void AnaliseSinSem:: terminal():
    if (atualIgual(tt['num'])):
        consome(tt['num'])
    elif (atualIgual(tt['id'])):
        id()
    else:
        print("Esperava-se um valor")
        return False
    return True

void AnaliseSinSem:: Elinha():
    if (operador()):
        terminal()
        Elinha()
    else:
        pass

void AnaliseSinSem:: operador():
    if atualIgual(tt['mais']):
        consome(tt['mais'])
    elif atualIgual(tt['menos']):
        consome(tt['menos'])
    elif atualIgual(tt['veiz']):
        consome(tt['veiz'])
    elif atualIgual(tt['por']):
        consome(tt['por'])
    else:
        return False
    return True

void AnaliseSinSem:: caso(): 
    consome(tt['caso'])
    expressao()
    if (not atualIgual(tt['|'])):
        print("Da um jeito nessa expressão ai meu fi, tudo errado!")
    while (not atualIgual(tt['|'])):
        consomequalquer()
    pipe()
    comandos()
    pipe()
    otoscaso()

void AnaliseSinSem:: otoscaso():
    if atualIgual(tt['otos-caso']):
        consome(tt['otos-caso'])
        pipe()
        comandos()
        pipe()	
    else:
        if atualIgual(tt['otos-caso-se']):
            consome(tt['otos-caso-se'])
            expressao()
            pipe()
            comandos()
            pipe()
            otoscaso()
        else:
            pass

bool AnaliseSinSem::pipe():
    if atualIgual(tt['|']):
        consome(tt['|'])
        return 1
    else:
        print("Esperava-se um |")
        return 0

void AnaliseSinSem:: expressao():
    terminalLogico()
    Llinha()

bool AnaliseSinSem::terminalLogico():
    if (atualIgual(tt['num'])):
        consome(tt['num'])
    elif (atualIgual(tt['id'])):
        id()
    elif (atualIgual(tt['trem-bao'])):
        consome(tt['trem-baum'])
    elif (atualIgual(tt['trem-ruim'])): 
        consome(tt['trem-ruim'])
    else:
        print("Esperava-se um símbolo lógico")
        return 0
    return 1

void AnaliseSinSem::Mlinha():
    if (operadorEOu()):
        terminal()
        if not atualIgual(tt['|']):
            Llinha()

bool AnaliseSinSem::operadorEOu():
    if (atualIgual(tt['e'])):
        consome(tt['e'])
    elif (atualIgual(tt['ou'])):
        consome(tt['ou'])
    else:
        print("Esperave-se um E ou OU")
        return 0
    return 1

void AnaliseSinSem::Llinha():
    if (operadorLogico()):
        terminal()
        if not atualIgual(tt['|']):
            Mlinha()

bool AnaliseSinSem::operadorLogico():
    if (atualIgual(tt['mema-coisa'])):
        consome(tt['mema-coisa'])
    elif (atualIgual(tt['diferente-de'])):
        consome(tt['diferente-de'])
    elif (atualIgual(tt['maior-que'])):
        consome(tt['maior-que'])
    elif (atualIgual(tt['menor-que'])):
        consome(tt['menor-que'])
    elif (atualIgual(tt['maior-que-ou-mema-coisa'])):
        consome(tt['maior-que-ou-mema-coisa'])
    elif (atualIgual(tt['menor-que-ou-mema-coisa'])):
        consome(tt['menor-que-ou-mema-coisa'])
    elif (atualIgual(tt['aneim'])):
        consome(tt['aneim'])
    elif (atualIgual(tt['e'])):
        consome(tt['e'])
    elif (atualIgual(tt['ou'])):
        consome(tt['ou'])
    else:
        return 0
    return 1

void AnaliseSinSem::faiz():
    consome(tt['faiz'])
    if (atualIgual(tt['id'])):
        id()
    elif (atualIgual(tt['num'])):
        consome(tt['num'])
    consome(tt['rodada'])
    pipe()
    comandos()
    pipe()

void AnaliseSinSem::cata():
    if atualIgual(tt['cata']):
        consome(tt['cata'])
        id()
        endline()

void AnaliseSinSem::id():
    if atualIgual(tt['id']):
        consome(tt['id'])
    else:
        print("Esperava-se um identificador")

void AnaliseSinSem::bota():
    consome(tt['bota'])
    if (atualIgual(tt['literal'])):
        consome(tt['literal'])
    elif (atualIgual(tt['id'])):
        consome(tt['id'])
    consome(tt['~'])

void AnaliseSinSem::uai():
    if atualIgual(tt['uai']):
        consome(tt['uai'])
    else:
        print("Esperava-se um 'uai', uai!")

// def main():
//     global tokenAtual
//     tokenAtual = getToken(arquivo, linha)
//     if comentario: print('Atual: main')
//     uai()
//     pipe()
//     declaracoes()
//     comandos()
//     pipe()
//     print("Compilo certin hein sô!")