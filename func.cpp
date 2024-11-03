#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>    
#include <string>
#include "func.hpp"

using namespace std;

void inicializarLDE(LDE &lista) {
	lista.comeco = nullptr;
	lista.fim = nullptr;
}

bool inserirFinalLDE(LDE &lista, const std::string &valor) {
	No *novo = new No;

	if (novo == nullptr) return false;
	novo->info = valor; 
	novo->eloA = nullptr;
	novo->eloP = nullptr;

	if (lista.comeco == nullptr) {
		lista.comeco = novo;
		lista.fim = novo;
	} else {
		lista.fim->eloP = novo;
		novo->eloA = lista.fim;
		lista.fim = novo;
	}
	return true;
}
No * pesquisarLDE(LDE &lista, string valor){
    No *aux = lista.comeco;
    while( aux != NULL ){
        if( valor == aux->info ) return aux;
        aux = aux->eloP;
    }
    return NULL;
}
bool retirarLDE(LDE &lista, const std::string &valor) {
    No *aux = pesquisarLDE(lista, valor);
    if (aux == nullptr) return false; // Não encontrou o valor

    //Caso a lista esteja vazia
    if (aux == lista.comeco && aux == lista.fim) {
        lista.comeco = nullptr;
        lista.fim = nullptr;
    }
    //Caso o nó a ser removido seja o início da lista
    else if (aux == lista.comeco) {
        lista.comeco = aux->eloP;
        lista.comeco->eloA = nullptr;
    }
    //Caso o nó a ser removido seja o fim da lista
    else if (aux == lista.fim) {
        lista.fim = aux->eloA;
        lista.fim->eloP = nullptr;
    }
    //Caso o nó a ser removido esteja no meio da lista
    else {
        No *ant = aux->eloA;
        No *prox = aux->eloP;
        ant->eloP = prox;
        if (prox != nullptr) {
            prox->eloA = ant;
        }
    }

    delete aux;
    return true;
}

//Conta o número de nós da lista
int contadorLDE(LDE &lista) {
	No *aux = lista.comeco;
	int contador = 0;

	while (aux != nullptr) {
		contador++;
		aux = aux->eloP;
	}

	return contador;
}

//Libera a memória dos nós da lista.
void liberarLDE(LDE &lista) {
	No *aux = lista.comeco;
	No *aux2;

	while (aux != nullptr) {
		aux2 = aux;
		aux = aux->eloP;
		delete aux2;
	}
}

//Limpa a tela
void clear() {
	system("cls");
}

//Limpa a linha anterior do console
void limparLinha() {
	cout << "\033[F";  // Move o cursor para a linha anterior
	cout << "\033[K";  // Limpa a linha
}

//Função para selecionar palavra aleatória
std::string selecionarPalavra() {
	LDE palavras;
	inicializarLDE(palavras);

	ifstream arquivo("palavras.txt");

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo." << endl;
		exit(1); 
	}

	string linha;
	while (getline(arquivo, linha)) {
		inserirFinalLDE(palavras, linha);
	}

	arquivo.close();

	//Verifica se a lista está preenchida.
	int numPalavras = contadorLDE(palavras);
	if (numPalavras == 0) {
		cout << "Nenhuma palavra encontrada no arquivo." << endl;
		exit(1);
	}

	//Inicializa a semente baseada no tempo
	srand(static_cast<unsigned int>(time(nullptr)));

	//Gera um número aleatório entre 1 e numPalavras
	int pos = rand() % numPalavras + 1;

	//Obtém a palavra na posição aleatória.
	return elementoPosicaoLDE(palavras, pos)->info;
}
//Retorna o nó na posição especificada
No* elementoPosicaoLDE(LDE &lista, int pos) {
	No *aux = lista.comeco;
	int contador = 1; //Por conta do número aleatório começar gerar em 1. 

	while (aux != nullptr && contador < pos) {
		aux = aux->eloP;
		contador++;
	}

	return aux;
}
//Separa a palavra (string) por caracter (do tipo string)
void separarCaracteres(LDE &lista, const string &entrada) {
	for (char c : entrada) {
		inserirFinalLDE(lista, string(1, c));  //Converte char para string
	}
}

//Coleta a entrada do usuário e adiciona na lista
void coletarEntrada(LDE &lista) {
	string entrada;
	cin >> entrada;

	if (entrada.length() != 5) {
		limparLinha();
		cout << "Entrada inválida! A palavra deve ter 5 letras." << endl;
		coletarEntrada(lista);
		limparLinha();
	} else {
		separarCaracteres(lista, entrada);
	}
}



//Compara duas listas e imprime os resultados formatados
bool compararListas(LDE &listaPalavra, LDE &listaEntrada) {
	No *auxPalavra = listaPalavra.comeco;
	No *auxEntrada = listaEntrada.comeco;

    //Inicializa arrays de bool para controle de cada letra
	bool letrasUsadas[5] = {false, false, false, false, false};
	bool letrasVerdes[5] = {false, false, false, false, false};
	bool acertouTudo = true;

	int i = 0;
	//Percorre a primeira vez, buscando as letras certas
	while (auxPalavra != nullptr && auxEntrada != nullptr) {
		if (auxPalavra->info == auxEntrada->info) {
			letrasUsadas[i] = true;
			letrasVerdes[i] = true;
		} else {
			acertouTudo = false;  //Se alguma letra estiver errada, o jogador ainda não acertou tudo
		}
		auxPalavra = auxPalavra->eloP;
		auxEntrada = auxEntrada->eloP;
		i++;
	}

	//Reseta os ponteiros e o indice.
	auxPalavra = listaPalavra.comeco;
	auxEntrada = listaEntrada.comeco;
	i = 0;

	//Percorre a segunda vez, letras amarelas e erradas
	while (auxPalavra != nullptr && auxEntrada != nullptr) {
	    //Se entrou aqui, essa letra não será mais testada
		if (letrasVerdes[i]) {
			cout << VERDE << auxEntrada->info << RESETAR_COR;  //Verde
		} else {
			No *auxTemp = listaPalavra.comeco;
			bool achouLetra = false;
			int j = 0;

			while (auxTemp != nullptr) {
				if (auxEntrada->info == auxTemp->info && letrasUsadas[j] == false) {
					cout << AMARELO << auxEntrada->info << RESETAR_COR; //Amarelo
					letrasUsadas[j] = true;
					achouLetra = true;
					break;
				}
				auxTemp = auxTemp->eloP;
				j++;
			}
			if (!achouLetra) {
				cout << CINZA << auxEntrada->info << RESETAR_COR;
			}
		}
		auxPalavra = auxPalavra->eloP;
		auxEntrada = auxEntrada->eloP;
		i++;
	}
	return acertouTudo;
}
string selecionarPalavraDiferente(const LDE &palavrasEscolhidas) {
	string novaPalavra;
	bool palavraUnica;

	do {
		novaPalavra = selecionarPalavra();  //Seleciona uma palavra aleatória
		palavraUnica = true;

		//Verifica se a nova palavra já foi escolhida
		No *aux = palavrasEscolhidas.comeco;
		while (aux != nullptr) {
			if (aux->info == novaPalavra) {
				palavraUnica = false;
				break;
			}
			aux = aux->eloP;
		}
	} while (!palavraUnica);

	return novaPalavra;
}

//Função para mostrar a palavra toda verde (quando já foi acertada)
void mostrarPalavraVerde(LDE &listaPalavra) {
	No *aux = listaPalavra.comeco;
	while (aux != nullptr) {
		cout << VERDE << aux->info << RESETAR_COR;
		aux = aux->eloP;
	}
}
void inserirPalavra() {
    string novaPalavra;
    cout << "Digite uma palavra de 5 letras: ";
    cin >> novaPalavra;
    
    LDE listaPalavras;
    inicializarLDE(listaPalavras);

    //Verifica se a palavra tem exatamente 5 letras
    if (novaPalavra.length() == 5) {
        //Adiciona a palavra à lista
        inserirFinalLDE(listaPalavras, novaPalavra);
        cout << "Palavra inserida com sucesso!" << endl;

        //Adiciona a palavra ao arquivo
        ofstream arquivo("palavras.txt", ios::app);
        if (arquivo.is_open()) {
            arquivo << novaPalavra << "\n";
            arquivo.close();
        } else {
            cout << "Erro ao abrir o arquivo para escrita." << endl;
        }
    } else {
        clear();
        cout << "A palavra deve ter exatamente 5 letras!" << endl;
        inserirPalavra();
    }
    liberarLDE(listaPalavras);
}


//Função para imprimir todas as palavras com índices
void listarPalavrasComIndices() {
    ifstream arquivo("palavras.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    LDE listaPalavras;
    inicializarLDE(listaPalavras);

    string linha;
    int indice = 1;
    while (getline(arquivo, linha)) {
        inserirFinalLDE(listaPalavras, linha);
    }
    arquivo.close();

    No* aux = listaPalavras.comeco;
    while (aux != nullptr) {
        cout << indice << ". " << aux->info << endl;
        aux = aux->eloP;
        indice++;
    }

    liberarLDE(listaPalavras);
}

//Função para remover uma palavra por índice
void removerPalavra() {
    listarPalavrasComIndices();

    int indiceParaRemover;
    cout << "Digite o índice da palavra que deseja remover: ";
    cin >> indiceParaRemover;

    if (indiceParaRemover <= 0) {
        cout << "Índice inválido!" << endl;
        return;
    }

    //Leitura do arquivo
    ifstream arquivo("palavras.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    LDE listaPalavras;
    inicializarLDE(listaPalavras);

    string linha;
    while (getline(arquivo, linha)) {
        inserirFinalLDE(listaPalavras, linha);
    }
    arquivo.close();

    //Encontrar e remover o nó com o índice especificado
    No* noParaRemover = elementoPosicaoLDE(listaPalavras, indiceParaRemover);
    if (noParaRemover == nullptr) {
        cout << "Índice fora do intervalo!" << endl;
        liberarLDE(listaPalavras);
        return;
    }

    //Remove o nó da lista
    retirarLDE(listaPalavras, noParaRemover->info);

    //Reescrever o arquivo sem a palavra removida
    ofstream arquivoSaida("palavras.txt");
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        liberarLDE(listaPalavras);
        return;
    }

    No* aux = listaPalavras.comeco;
    while (aux != nullptr) {
        arquivoSaida << aux->info << '\n';
        aux = aux->eloP;
    }
    arquivoSaida.close();

    liberarLDE(listaPalavras);

    cout << "Palavra removida com sucesso!" << endl;
}

//Pergunta se o jogador deseja jogar novamente
void jogarNovamente() {

	char resposta;
	cout << "Deseja jogar novamente? (S/N): ";
	cin >> resposta;
	clear();

	if (resposta == 'S' || resposta == 's') {
		menuJogar();
	} else {
		clear();
		cout << "Obrigado por jogar!" << endl;
		exit(0);
	}
}

//Função para exibir o menu
void menu() {
	int escolha;
    do {
        cout << "=-=-=-=-=-=-= MENU PRINCIPAL =-=-=-=-=-=-=" << endl;
        cout << "1. Jogar" << endl;
        cout << "2. Inserir palavra" << endl;
        cout << "3. Remover palavra" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolha;
        clear();

        switch (escolha) {
            case 1:
                menuJogar();
                break;
            case 2:
                inserirPalavra();
                break;
            case 3:
                removerPalavra();
                break;
            case 4:
                cout << "Saindo do jogo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    } while (escolha != 4);
}

//Para o menu dos modos de jogo.
void menuJogar() {
	int escolha;
	do {
		cout << "=-=-=-=-=- MODO DE JOGO -=-=-=-=-=-" << endl;
		cout << "1. Termo" << endl;
		cout << "2. Dueto" << endl;
		cout << "3. Terceto" << endl;
		cout << "4. Quarteto" << endl;
		cout << "5. Voltar ao menu" << endl;
		cout << "Escolha: ";
		cin >> escolha;
		clear();

    if(escolha >= 1 && escolha <= 4){
        jogarModo(escolha);
    }
    else if (escolha == 5){
        break;
    }
    else {
        cout << "Opção inválida! Tente novamente." << endl;
    }
	} while (escolha != 5);
}

void jogarModo(int modo) {
    int tentativas;
    string titulo;

    //Inicializa o número de tentativas e o título do jogo baseado no modo
    switch (modo) {
        case 1: 
            tentativas = 6;
            titulo = "=-=-=-=-=- TERMO -=-=-=-=-=-";
            break;
        case 2:
            tentativas = 8;
            titulo = "=-=-=-=-=- DUETO -=-=-=-=-=-";
            break;
        case 3:
            tentativas = 10;
            titulo = "=-=-=-=-=- TERCETO -=-=-=-=-=-";
            break;
        case 4:
            tentativas = 12;
            titulo = "=-=-=-=-=- QUARTETO -=-=-=-=-=-";
            break;
        default:
            cout << "Modo inválido!" << endl;
            return;
    }

    LDE palavrasEscolhidas;
    inicializarLDE(palavrasEscolhidas);

    //Cria arrays dinâmicos para armazenar as palavras e as listas associadas
    string* palavras = new string[modo];       //Armazena as palavras selecionadas
    LDE* listaPalavras = new LDE[modo];        //Armazena as LDE para cada palavra
    bool* acertou = new bool[modo];            //Armazena o estado de cada palavra (acertada ou não)

    //Inicializa as listas e os estados
    for (int i = 0; i < modo; i++) {
        palavras[i] = selecionarPalavraDiferente(palavrasEscolhidas);
        inserirFinalLDE(palavrasEscolhidas, palavras[i]);

        inicializarLDE(listaPalavras[i]);
        separarCaracteres(listaPalavras[i], palavras[i]);

        acertou[i] = false; //Nenhuma palavra foi acertada inicialmente
    }

    // Exibe as palavras selecionadas para testar
    // cout << "Palavras selecionadas: ";
    // for (int i = 0; i < modo; i++) {
    //     cout << palavras[i];
    //     if (i < modo - 1) {
    //         cout << " / ";
    //     }
    // }
    // cout << endl;

    cout << titulo << endl;

    LDE listaEntrada;
    inicializarLDE(listaEntrada);

    //Loop de tentativas
    while (tentativas > 0) {
        coletarEntrada(listaEntrada);
        limparLinha();
        
        //Começa com todas certas, conforme entrada (errada) vai atualizando o estado para false.
        bool todasAcertadas = true;

        for (int i = 0; i < modo; i++) {
            if (!acertou[i]) {
                //Retorna true ou false, atribuindo ao indice acertou.
                acertou[i] = compararListas(listaPalavras[i], listaEntrada);
            } else {
                mostrarPalavraVerde(listaPalavras[i]);
            }

            //Verifica se todas as palavras foram acertadas
            todasAcertadas &= acertou[i];
            
            //Imprimir o separador, entre o dueto e o quarteto.
            if (i < modo - 1) {
                cout << " / ";
            }
        }
        cout << endl;

        if (todasAcertadas) {
            cout << "Parabéns! Você acertou todas as palavras!" << endl;
            break;
        } else {
            tentativas--;
            if (tentativas == 0) {
                cout << "Você perdeu! As palavras eram: ";
                for (int i = 0; i < modo; i++) {
                    cout << palavras[i];
                    if (i < modo - 1) {
                        cout << " / ";
                    }
                }
                cout << endl;
            }
        }

        liberarLDE(listaEntrada);
        inicializarLDE(listaEntrada);
    }

    //Libera memória e recursos
    for (int i = 0; i < modo; i++) {
        liberarLDE(listaPalavras[i]);
    }

    liberarLDE(palavrasEscolhidas);
    delete[] palavras;
    delete[] listaPalavras;
    delete[] acertou;

    liberarLDE(listaEntrada);

    jogarNovamente(); //Função para jogar novamente
}
