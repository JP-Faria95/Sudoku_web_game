#include <emscripten.h>
#include "funcoes_sudoku_web.h"
#include "variaveis_sudoku_web.h"
using namespace std;

bool gerar_tabuleiro();
bool percorrer_tabuleiro(int, int, int);
bool apagar_numero(int);
bool copiar_tabuleiro();
void mostrar_tabuleiro();
bool valida_inserir_numero(int, int, int);
void insere_numero(int, int, int);
bool valida_deletar_numero(int, int);
void deleta_numero(int, int, int);
bool fim_jogo_verifica();

extern "C" {

	EMSCRIPTEN_KEEPALIVE
	void iniciar_jogo(int dificuldade) {

		// Limpamos os dois tabuleiros antes de iniciar um jogo novo
		for (int linha = 0; linha < tamanho; linha++) {
			for (int coluna = 0; coluna < tamanho; coluna++) {
				tabuleiro_original[linha][coluna] = 0;
				tabuleiro_jogador[linha][coluna] = 0;
			}
		}

		// Chama as funções da sessão 'gerador de tabuleiro'
		gerar_tabuleiro();
		apagar_numero(dificuldade);
		copiar_tabuleiro();
	}

	EMSCRIPTEN_KEEPALIVE
	int celula_jogada(int linha, int coluna) {
		return tabuleiro_jogador[linha][coluna];
	}

	EMSCRIPTEN_KEEPALIVE
	int valida_numero_original(int linha, int coluna) {
		return tabuleiro_original[linha][coluna] != 0 ? 1 : 0;
	}

	EMSCRIPTEN_KEEPALIVE
	int jogar(int linha, int coluna, int numero) {
		if (valida_inserir_numero(linha, coluna, numero)) {
			insere_numero(linha, coluna, numero);
			return 1; // jogada válida
		}
		return 0; // jogada inválida
	}

	EMSCRIPTEN_KEEPALIVE
	int apagar(int linha, int coluna) {
		if (valida_deletar_numero(linha, coluna)) {
			int numero = tabuleiro_jogador[linha][coluna];
			deleta_numero(linha, coluna, numero);
			return 1; // apagado com sucesso
		}
		return 0; // não pode apagar
	}

	EMSCRIPTEN_KEEPALIVE
	int jogo_finalizado() {
		return fim_jogo_verifica() ? 1 : 0;
	}

}

