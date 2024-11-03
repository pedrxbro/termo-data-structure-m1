#ifndef FUNC_HPP
#define FUNC_HPP

// Defini��es de cores
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

//Fun��es para LDE
void inicializarLDE(LDE &lista);
bool inserirFinalLDE(LDE &lista, const std::string &valor);
bool retirarLDE(LDE &lista, const std::string &valor);
No * pesquisarLDE(LDE &lista, const std:: string valor);
int contadorLDE(LDE &lista);
No* elementoPosicaoLDE(LDE &lista, int pos);
void liberarLDE(LDE &lista);

//Fun��es auxiliares
void clear();
void limparLinha();

//Fun��es do jogo
void menu();
void menuJogar();
void jogarNovamente();
void jogarModo(int modo);

//Fun��es termo
void coletarEntrada(LDE &lista);
void converterParaChar(LDE &lista, const std::string &entrada);
bool compararListas(LDE &listaPalavra, LDE &listaEntrada);

//Fun��es palavras
std::string selecionarPalavra();
std::string selecionarPalavraDiferente(const LDE &palavrasEscolhidas);
void mostrarPalavraVerde(LDE &listaPalavra);
void inserirPalavra();
void removerPalavra();



#endif