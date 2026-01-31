// ESSE ARQUIVO CONTÉM TODAS AS FUNÇÕES USADAS NO PROGRAMA 'MAIN' DO PROJETO 'SODUKU C++'

#include <iostream>
#include <random>
#include <vector>
#include "variaveis_sudoku_web.h"
using namespace std;
random_device rd;
mt19937 mt(rd());

/* | ------------------------|
   | PROT�TIPOS DAS FUN��ES |
   |------------------------|
*/

// ========================
// | GERADOR DO TABULEIRO |
// ========================

// Gera um tabuleiro 
bool gerar_tabuleiro();

// Percorre o tabuleiro gerado para validar um numero gerado
bool percorrer_tabuleiro(int, int, int);

// Apaga numeros de acordo com a dificuldade escolhida pelo jogador
bool apagar_numero(int);

// Copia o tabuleiro original para o tabuleiro do jogador
bool copiar_tabuleiro();

// ===========
// | JOGADAS |
// ===========

// Mostra o tabuleiro original e o do jogador assim que ele avan�a nas jogadas
void mostrar_tabuleiro();

// Valida a jogada de inserir um numero feita pelo jogador
bool valida_inserir_numero(int, int, int);

// Insere o numero informado no tabuleiro
void insere_numero(int, int, int);

// Valida a jogada de deletar um numero feita pelo jogador
bool valida_deletar_numero(int, int);

// Deleta o numero informado do tabuleiro
void deleta_numero(int, int, int);

// Verifica se o jogador concluiu o jogo
bool fim_jogo_verifica();

/* |----------------------------|
   | IMPLEMENTA��ES DAS FUN��ES |
   |----------------------------|
*/

bool gerar_tabuleiro() {

	// 1. Usamos dois la�os FOR para percorrer o tabuleiro bidemensionalmente.
	// 2. Ao encontrar uma posi��o [linha][coluna] com valor 0, podemos tentar inserir um n�mero nessa posi��o.
	// 3. Criamos um vetor din�mico para armazenar os n�meros poss�veis para usar no Sudoku, 1 a 9.
	// 4. Usamos a fun��o 'shuffle()' para embaralhar esse vetor.
	// 5. Percorremos o vetor embaralhado usando um la�o FOR
	// 6. Para cada indice do vetor, criamos um numero.
	// 7. Passamos o indice duplo [linha][coluna] e mais o numero gerado para a fun��o 'percorrer_tabuleiro()',
	//	  que valida se o numero gerado pode ser inserido na posi��o informada.
	// 8. Se a posi��o for v�lida, ent�o insere o n�mero.
	// 9. Chama recursivamente a fun��o 'gerar_tabuleiro()' para colocar em pr�tica o 'backtracking' a respeito
	//	  do sudoku. Sempre que um n�mero n�o for v�lido para ser inserido, a fun��o zera a posi��o atual e 
	//    tenta outro n�mero.
	// 10. A fun��o retorna true quando finalmente todo o tabuleiro for preenchido com n�mero de forma v�lida.

	int numero;
	for (int linha = 0; linha < tamanho; linha++) {
		for (int coluna = 0; coluna < tamanho; coluna++) {
			if (tabuleiro_original[linha][coluna] == 0) {
				vector<int>numeros_sudoku = { 1,2,3,4,5,6,7,8,9 };
				shuffle(numeros_sudoku.begin(), numeros_sudoku.end(), mt);
				for (int indice = 0; indice < numeros_sudoku.size(); indice++) {
					numero = numeros_sudoku[indice];
					if (percorrer_tabuleiro(linha, coluna, numero)) {
						tabuleiro_original[linha][coluna] = numero;
						if (gerar_tabuleiro()) {
							return true;
						}
					}
				}
				tabuleiro_original[linha][coluna] = 0;
				return false;
			}
		}
	}
	return true;
}

bool percorrer_tabuleiro(int linha, int coluna, int numero) {

	// 1. Para validar a inser��o de um n�mero no tabuleiro original, utilizamos a seguinte regra do Sudoku:
	//    "O n�mero inserido n�o pode aparecer duas ou mais vezes na mesma linh, ou na mesma coluna ou no
	//     mesmo quadrante 3x3".
	// 2. Dessa forma, para validar a exist�ncia do n�mero no quadrante 3x3 definimos a primeira linha e a 
	//    primeira coluna para percorrer exatamente o quadrante que vamos validar.
	// 3. O inicio da linha e do bloco s�o definidos por meio da DIVIS�O INTEIRA do valor da linha e coluna
	//    informados atrav�s dos par�metros. O resultado � multiplicado por 3 uma vez que cada quadrante inicia 
	//    a cada 3 linhas ou 3 colunas. Por exemplo: 'linha = 4' e 'coluna = 7'. Inicio do bloco da linha ser�
	//    3 uma vez que 4/3 = 1 * 3 = 3. Inicio do bloco da coluna ser� 6 uma vez que 7/3 = 2 * 3 = 6.
	// 4. O la�o For para percorrer o quadrante deve ser iterado 3 vezes j� que o quadrante tem tamanho 3x3.
	// 5. Neste la�o, validamos se o n�mero informado existe no quadrante atrav�s da compara��o do indice atual 
	//    do tabuleiro original com o valor a ser inserido. O indice funciona atrav�s da soma do valor da
	//    itera��o de 'linha' ou 'coluna' com o valor de 'inicio_bloco_linha' ou 'inicio_bloco_coluna'. 
	//    Por exemplo: Usando os valores do item 3 para o inicio da linha e da coluna, 3 e 6, os valores que
	//    seriam poss�veis para os indices seriam '3,4,5' para linha e '6,7,8' para coluna.
	// 6. Se em algum momento o n�mero informado for encontrado no tabuleiro original, ent�o a fun��o retorna
	//    false e a fun��o � encerrada.
	// 7. Para percorrer a linha e a coluna, usamos um la�o For para cada um separadamente. A linha percorre
	//    os indices da coluna, e a coluna percorre os indices da linha. Se em algum momento o numero for 
	//    encontrado, a fun��o retorna false.
	// 8. Se nenhuma condi��o If for validada, ent�o a fun��o retorna true, indicando que o n�mero informado
	//    � valido para ser inserido na posi��o indicada do tabuleiro original.

	int inicio_bloco_linha, inicio_bloco_coluna;
	inicio_bloco_linha = (linha / 3) * 3;
	inicio_bloco_coluna = (coluna / 3) * 3;

	for (int indice_linha = 0; indice_linha < 3; indice_linha++) {
		for (int indice_coluna = 0; indice_coluna < 3; indice_coluna++) {
			if (tabuleiro_original[indice_linha + inicio_bloco_linha][indice_coluna + inicio_bloco_coluna] == numero) {
				return false;
			}
		}
	}

	for (int indice_coluna = 0; indice_coluna < tamanho; indice_coluna++) {
		if (tabuleiro_original[linha][indice_coluna] == numero) {
			return false;
		}
	}

	for (int indice_linha = 0; indice_linha < tamanho; indice_linha++) {
		if (tabuleiro_original[indice_linha][coluna] == numero) {
			return false;
		}
	}

	return true;
}

bool apagar_numero(int dificuldade) {

	// 1. De acordo com a dificuldade do jogo escolhida pelo jogador, definimos a quantidade de n�meros
	//    que ser� apagados do tabuleiro original.
	// 2. Ser� necess�rio gerar dois n�meros que representem a linha e a coluna que ter�o o n�mero apagado.
	//    Para isso usamos o gerador de numeros pseudo-aleat�rios 'Mersenne Twister' para gerar n�meros
	//    no intervalor entre 0 e 8 j� que s�o os indices poss�veis para linha ou coluna no tabuleiro.
	// 3. Criamos um vetor din�mico bidimensional 'indices_removidos' que guarda os indices que j� tiveram
	//    o n�mero apagado para evitar que o mesmo indice seja escolhido e haja um falso positivo em rela��o
	//    � quantidade de n�meros removidos de acordo com a dificuldade. Por exemplo, o jogador escolhe dificuldade
	//    2, portanto, 50 n�meros precisam ser apagados. Se n�o houver valida��o dos indices j� apagados, a
	//    fun��o pode apagar o n�mero mais de uma vez no mesmo indice, e assim o tabuleiro teria um valor n�o
	//    condizente com a dificuldade.
	// 4. Criamos uma vari�vel booleana para guarda true ou false em rela��o � presen�a de um determinado
	//    indice no vetor din�mico 'indices_removidos'.
	// 5. Para fazer a remo��o da quantidade certa de n�meros, usamos um loop while que itera at� o vetor
	//    dinamico 'indices_removidos' atinja o tamanho da variavel 'remover', ou seja, at� que a quantidade
	//    de numeros removidos seja alcan�ada.
	// 6. Geramos aleat�riamente os indices para linha e coluna no intervalo de 0 a 8.
	// 7. A primeira remo��o � sempre poss�vel visto que o vetor din�mico est� vazio, portanto o primeiro If
	//    ser� atendido e o primeiro n�mero ser� removido.
	// 8. Ap�s, usamos um la�o For que itera em rela��o ao tamanho atual do vetor din�mico. Nesse For, comparamos
	//    os valores de linha e coluna gerados anteriormente com as posi��es bidimensionais do vetor din�mico.
	// 9. Se encontrada a posi��o, ent�o significa que o n�mero daquela posi��o j� foi removido e a variavel flag
	//    assume o valor true.
	// 10. Ap�s a itera��o finalizar, se a variavel flag estiver como false, ent�o adicionamos o indice linha e coluna
	//    no vetor din�mico e removemos o n�mero dela.
	// 11. A fun��o retorna true ap�s o vetor din�mico ser preenchido com as quantidades equivalentes � variavel remover.

	int remover, linha, coluna;
	if (dificuldade == 1) remover = 35;
	if (dificuldade == 2) remover = 50;
	if (dificuldade == 3) remover = 65;
	uniform_int_distribution<int> indices(0, 8);
	vector<pair<int, int>> indices_removidos;
	bool flag;

	while (indices_removidos.size() < remover) {
		linha = indices(mt);
		coluna = indices(mt);
		flag = false;

		if (indices_removidos.size() == 0) {
			indices_removidos.push_back({ linha,coluna });
			tabuleiro_original[linha][coluna] = 0;
		}

		for (int indice = 0; indice < indices_removidos.size(); indice++) {
			if (linha == indices_removidos[indice].first && coluna == indices_removidos[indice].second) {
				flag = true;
			}
		}

		if (flag == false) {
			indices_removidos.push_back({ linha,coluna });
			tabuleiro_original[linha][coluna] = 0;
		}
	}
	return true;
}

bool copiar_tabuleiro() {

	// 1. A fun��o realiza apenas a c�pia dos valores de cada indice bidimenional do tabuleiro original
	//    para o tabuleiro do jogador. Assim o tabuleiro original permance igual o jogo todo, apenas o
	//    tabuleiro do jogador vai sendo alterado ao longo das jogadas.
	// 2. Usamos o la�o for duplo para percorrer os indices de forma bidimensional.

	for (int linha = 0; linha < tamanho; linha++) {
		for (int coluna = 0; coluna < tamanho; coluna++) {
			tabuleiro_jogador[linha][coluna] = tabuleiro_original[linha][coluna];
		}
	}
	return true;
}

void mostrar_tabuleiro() {

	// 1. Definimos uma variavel string que muda a cor da fonte exibida para os n�meros que vieram
	//    do tabuleiro original. Essa mudan�a ajuda o jogador a diferenciar os n�meros que ele inseriu
	//    dos n�meros que vieram do tabuleiro original.
	// 2. Exibimos a numeracao das colunas de 0 a 8.
	// 3. Usamos um la�o For para percorrer as linhas.
	// 4. Para dividir o tabuleiro a cada 3 linhas, usamos a verifica��o se acaso o m�dulo da divis�o
	//    do valor da linha por 3 resulta em 0, ou seja, um n�mero inteiro, adicionamos a divis�o do tabuleiro.
	// 5. Fazemos a impress�o da 'linha' com um divior '|' para melhorar a est�tica do tabuleiro.
	// 6. Usamos um la�o For para percorrer as colunas.
	// 7. Verificamos se no indice [linha][coluna] atual o n�mero � 0, se sim, substituimos por '.' para melhorar
	//    a exibi��o do tabuleiro.
	// 8. Se o n�mero for diferente de 0, ent�o continuamos para outra verifica��o, se no tabuleiro original
	//    aquele indice � diferente de zero, o que significa que � um n�mero do tabuleiro original e n�o um
	//    n�mero inserido pelo jogador. Se for um n�mero do tabuleiro original, ent�o o imprimimos na cor
	//    vermelha. Se n�o, � impresso na cor original.
	// 9. Sempre que o m�dulo da divis�o do indice da coluna acrescido de +1, for igual a zero, ent�o
	//    imprimimos uma divis�o de colunas, para fazer a estrutura do quadrante 3x3 no tabuleiro.
	// 10. Por fim, imprimimos a ultima linha tracejada para finalizar a estrutura do tabuleiro.

	string cor_fonte = "\033[31m", cor_original = "\033[0m";

	cout << "     0 1 2   3 4 5   6 7 8 ";
	for (int linha = 0; linha < tamanho; linha++) {
		if (linha % 3 == 0) {
			cout << "\n   -------------------------";
		}
		cout << "\n" << linha << "  | ";

		for (int coluna = 0; coluna < tamanho; coluna++) {
			if (tabuleiro_jogador[linha][coluna] == 0) {
				cout << ". ";
			}
			else {
				if (tabuleiro_original[linha][coluna] != 0) {
					cout << "" << cor_fonte << "" << tabuleiro_jogador[linha][coluna] << " " << cor_original << "";
				}
				else {
					cout << "" << tabuleiro_jogador[linha][coluna] << " ";
				}
			}

			if ((coluna + 1) % 3 == 0) {
				cout << "| ";
			}

		}
	}
	cout << "\n   -------------------------";
}

bool valida_inserir_numero(int linha, int coluna, int numero) {

	// 1. Definimos as variaveis que guardar�o os valores do inicio dos blocos quadrantes 3x3 da linha e coluna.
	// 2. Percorremos um la�o For duplo representando os indices da linha e da coluna respectivamente e verificamos
	//    se no indice atual da linha ou da coluna, o n�mero informado � encontrado. Se for encontrado, ent�o
	//    a jogada � invalidada e a fun��o retorna false.
	// 4. Finalizando a itera��o dos la�os For, ent�o iniciamos um terceiro para percorrer o tamanho do quadrante,
	//    isto �, 3 linhas e 3 colunas. Validamos se no tabuleiro o n�mero informado existe em qualquer posi��o do
	//    quadrante. Se existir, ent�o a jogada � invalidada e a fun��o retorna false.
	// 5. Verificamos tamb�m se naquela posi��o informada pelo jogador, j� existe um n�mero, para evitar que 
	//    n�meros sejam substituidos.
	// 6. Por fim, se nenhuma valida��o for disparada, ent�o a fun��o retorna true.

	int inicio_bloco_linha = (linha / 3) * 3;
	int inicio_bloco_coluna = (coluna / 3) * 3;

	for (int indice_linha = 0; indice_linha < tamanho; indice_linha++) {
		if (tabuleiro_jogador[indice_linha][coluna] == numero) {
			cout << "O numero " << numero << " ja esta na coluna informada.\n\n";
			return false;
		}
		for (int indice_coluna = 0; indice_coluna < tamanho; indice_coluna++) {
			if (tabuleiro_jogador[linha][indice_coluna] == numero) {
				cout << "O numero " << numero << " ja esta na linha informada.\n\n";
				return false;
			}
		}
	}

	for (int indice_linha = 0; indice_linha < 3; indice_linha++) {
		for (int indice_coluna = 0; indice_coluna < 3; indice_coluna++) {
			if (tabuleiro_jogador[indice_linha + inicio_bloco_linha][indice_coluna + inicio_bloco_coluna] == numero) {
				cout << "O numero " << numero << " ja esta no quadrante informado.\n\n";
				return false;
			}
		}
	}

	if (tabuleiro_jogador[linha][coluna] != 0) {
		cout << "Ja existe um numero na posicao informada.\n\n";
		return false;
	}

	return true;
}

void insere_numero(int linha, int coluna, int numero) {

	// 1. Fazemos uma opera��o de atribui��o do n�mero na posi��o bidimensional do tabuleiro do jogador.

	tabuleiro_jogador[linha][coluna] = numero;
	cout << "O numero " << numero << " foi inserido no tabuleiro.\n\n";
}

bool valida_deletar_numero(int linha, int coluna) {

	// 1. Validamos se no tabuleiro original, aquela posi��o cont�m um valor zero ou diferente de zero.
	// 2. Se diferente de zero, significa que o n�mero que est� ali � do pr�prio tabuleiro original e
	//    dessa forma n�o pode ser apagado, pois assim o jogador poderia trapacear. Nesse caso a fun��o
	//    retorna false.
	// 3. Se for igual a zero, significa que o n�mero pode ser apagado, pois foi inserido pelo pr�prio
	//    jogador.
	// 4. Ainda, verificamos se na posi��o informada do tabuleiro do jogador, existe um valor igual ou
	//    diferente de zero. Se igual a zero, invalidamos a opera��o pois n�o faria sentido apagar um
	//    n�mero zero. Assim a fun��o retorna false.
	// 5. Se o n�mero for diferente de zero, ent�o o pr�prio jogador o inseriu e pode ser apagado. Assim
	//    a fun��o retorna true.

	if (tabuleiro_original[linha][coluna] != 0) {
		cout << "Posicao invalida para deletar um numero.\n\n";
		return false;
	}
	else {
		if (tabuleiro_jogador[linha][coluna] == 0) {
			cout << "Posicao invalida para deletar um numero.\n\n";
			return false;
		}
		else {
			return true;
		}
	}
}

void deleta_numero(int linha, int coluna, int numero) {

	// 1. Fazemos uma opera��o de atribui��o na posi��o bidimensional do tabuleiro do jogador, zerando o valor
	//    que estava ali.

	tabuleiro_jogador[linha][coluna] = 0;
	cout << "O numero " << numero << " foi apagado do tabuleiro.\n\n";
}

bool fim_jogo_verifica() {
	for (int linha = 0; linha < tamanho; linha++) {
		for (int coluna = 0; coluna < tamanho; coluna++) {
			if (tabuleiro_jogador[linha][coluna] == 0) {
				return false;
			}
		}
	}
	cout << "\n\nJogo Finalizado! Parabens!\n\n";
	return true;
}