#ifndef FUNC_HPP
#define FUNC_HPP

// Definições de cores
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define CINZA "\033[37m"
#define RESETAR_COR "\033[0m"

#include <string>

//Estruturas de dados
struct No {
    std::string info;  
    No *eloA, *eloP;
};

struct LDE {
    No *comeco;
    No *fim;
};

//Funções para LDE
void inicializarLDE(LDE &lista);
bool inserirFinalLDE(LDE &lista, const std::string &valor);
bool retirarLDE(LDE &lista, const std::string &valor);
No * pesquisarLDE(LDE &lista, const std:: string valor);
int contadorLDE(LDE &lista);
No* elementoPosicaoLDE(LDE &lista, int pos);
void liberarLDE(LDE &lista);

//Funções auxiliares
void clear();
void limparLinha();

//Funções do jogo
void menu();
void menuJogar();
void jogarNovamente();
void jogarModo(int modo);

//Funções termo
void coletarEntrada(LDE &lista);
void converterParaChar(LDE &lista, const std::string &entrada);
bool compararListas(LDE &listaPalavra, LDE &listaEntrada);

//Funções palavras
std::string selecionarPalavra();
std::string selecionarPalavraDiferente(const LDE &palavrasEscolhidas);
void mostrarPalavraVerde(LDE &listaPalavra);
void inserirPalavra();
void removerPalavra();



#endif