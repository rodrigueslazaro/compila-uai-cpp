#include "AnaliseLexica.h"
#include <cctype>
#include <iostream>
#include <cstdio>
using namespace std;

AnaliseLexica::AnaliseLexica(string nomeArquivo)
	:nomeArquivo(nomeArquivo)
	,estado(1)
	,car('\0')
	,lexema("")
	,linha(1) { }

AnaliseLexica::~AnaliseLexica() {
	arquivo.close();
}

void AnaliseLexica::carregarDicionarioDeTokens() {
    token newtoken;
    vector<pair<string, string>> dicionario = {
        {"uai", "main"},
        {"queijo", "inteiro"},
        {"pamonha", "texto"},
        {"num", "numero"},
        {"id", "id"},
        {"casadinho", "bool"},
        {"otos-caso", "senao"},
        {"otos-caso-se", "senaose"},
        {"rodada", "rodada"},
        {"bota", "cout"},
        {"caso", "caso"},
        {"faiz", "faiz"},
        {"cata", "cin"},
        {"xuxa", "return"},
        {"trem-bao", "verdadeiro"},
        {"trem-ruim", "falso"},
        {"e", "e"},
        {"ou", "ou"},
        {"aneim", "nao"},
        {"menor-que", "menor-que"},
        {"maior-que", "maior-que"},
        {"menor-que-ou-mema-coisa", "menor-que-ou-mema-coisa"},
        {"maior-que-ou-mema-coisa", "maior-que-ou-mema-coisa"},
        {"mema-coisa", "mema-coisa"},
        {"diferente-de", "diferente-de"},
        {"mais", "soma"},
        {"menos", "sub"},
        {"veiz", "vezes"},
        {"por", "divisao"},
        {"(", "("},
        {")", ")"},
        {"~", "endlinha"},
        {"<>", "atrib"},
        {"|", "pipe"},
        {"literal", "literal"},
        {"end", "end"},
        {"erro", "erro"},
        {" ", "espaco"}
    };
    for (size_t i=0; i<dicionario.size(); i++) {
        newtoken.id = i;
        newtoken.key = dicionario[i].first;
        newtoken.desc = dicionario[i].second;
        tokens.push_back(newtoken);
    }
}

bool AnaliseLexica::abrirArquivo() {
    arquivo.open(nomeArquivo);
    return arquivo.is_open();
}

token AnaliseLexica::getTokenPelaChave(string chave) {
	for (token i : tokens)
		if (chave == i.key)
			return i;
	token errtoken;
	errtoken.id = 0;
	errtoken.key = "erro";
	errtoken.desc = "TOKEN NAO ENCONTRADO";
	return errtoken;
}

token AnaliseLexica::getTokenPeloID(int id) {
	if (id < static_cast<int>(tokens.size()))
		return tokens[id];
	token errtoken;
	errtoken.id = 0;
	errtoken.key = "erro";
	errtoken.desc = "TOKEN NAO ENCONTRADO";
	return errtoken;
}

void AnaliseLexica::getChar() {
    int aux = arquivo.get();
    car = (aux == EOF) ? '\0' : static_cast<char>(aux);
	if (car == '\n') {
		linha++;
	}
}

token_encontrado AnaliseLexica::retorno(string chave, string encontrado) {
	token_encontrado novotoken_encontrado;
	novotoken_encontrado.t = getTokenPelaChave(chave);
	novotoken_encontrado.encontrado = encontrado;
	novotoken_encontrado.linha = linha;
	return novotoken_encontrado;
}

token_encontrado AnaliseLexica::getToken() {
	lexema = "";
	estado = 1;
	for (;;) {
		// O estado 1 verifica quais sao os estados iniciais
		if (estado == 1) {
			getChar();
			// se não é o fim do arquivo
			if ((car != ' ') and (car != '\n') and (car != '\t')) {
				if (car == '\0') {
					return retorno("end", "EOF");
				}
				// Verifica se sao letras
				else if (isalpha(car))
					estado = 2;
				// Verifica se sao numeros
				else if (isdigit(car))
					estado = 3;
				// Verifica se sao tokens primitivos
				else if (car == '~' or car == '(' or car == ')' or car == '|')
					estado = 4;
				// Verifica o comentario
				else if (car == '!')
					estado = 5;
				// Cadeia
				else if (car == '-')
					estado = 6;
				else if (car == '<')
					estado = 7;
				else {
					string encontrado = "<";
					encontrado += car + ">";
					return retorno("erro", encontrado);
				}
			}
		} else if (estado == 2) {
			// Estado que trata nomes (identificadores ou palavras reservadas)
			lexema += car;
			getChar();
			if (car == ':' or car == '$')
				return retorno(lexema, lexema);
			else if (car == ' ')
				return retorno("id", lexema);
			else if (car == '\0') {
				string encontrado = "<";
				encontrado += car + ">";
				return retorno("erro", encontrado);
			}
		} else if (estado == 3) {
			// Estado que trata numeros inteiros
			lexema += car;
			getChar();
			if (car == ' ')
				return retorno("num", lexema);
			else if (not isdigit(car)) {
				string encontrado = "<";
				encontrado += car + ">";
				return retorno("erro", encontrado);
			}
		} else if (estado == 4) {
			// estado que trata outros tokens primitivos comuns
			lexema += car;
			if (car == '~')
				return retorno("~", lexema);
			else if (car == '(')
				return retorno("(", lexema);
			else if (car == ')')
				return retorno(")", lexema);
			else if (car == '|')
				return retorno("|", lexema);
		// O estado 5 trata comentarios
		} else if (estado == 5) {
			getChar();
			if (car == '!')
				estado = 1;	
		// O estado 6 trata da cadeia entre os hifens
		} else if (estado == 6) {
			getChar();
			while ((not car == '\0') and (car != '-')) {
				lexema += car;
				getChar();
			}
			estado = 1;
			return retorno("literal", lexema);
		
		} else if (estado == 7) {
			lexema += car;
			getChar();
			if (car == '>')
				estado = 8;
		} else if (estado == 8) {
			lexema += car;
			getChar();
			if (car == ' ')
				return retorno("<>", lexema);
		}
	}
}