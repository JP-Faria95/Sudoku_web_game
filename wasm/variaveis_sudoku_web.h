// NESSE AQUI ESTÃO DECLARADAS AS VARIÁVEIS GLOBAIS DO PROJETO
// Elas serão usadas pelo arquivo de funções 'funcoes.h'
#pragma once
/*
	===========
	| GLOBAIS |
	===========
*/

// O Tamanho do tabuleiro, com valor constante.
const int tamanho = 9;

// O tabuleiro original que vai guardar os numeros originais criados pelo sistema
// Esse tabuleiro vai servir de modelo para criar o tabuleiro usado pelo jogador
// Também serve para comparação na hora de deletar números, caso o jogador escolha.
extern int tabuleiro_original[tamanho][tamanho] =
{
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0}
};

// O tabuleiro do jogador vai servir para que o jogador execute suas jogadas
// Ele será inicialmente um espelho do tabuleiro original e será alterado ao longo
// do jogo, podendo ter números inseridos ou deletados.
extern int tabuleiro_jogador[tamanho][tamanho] =
{
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0}
};
