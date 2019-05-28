#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define VERMELHO "\033[0;31m"
#define VERDE "\033[0;32m"
#define RESET "\033[0m"

void mostrarLinha(char letras[]);
void mostrarForca(int *vida, char mensagem[], char tema[]);
void mostrarResultado(int countPartidas, int vitoriasJogador1, int vitoriasJogador2);
void leValidaTema(char tema[]);
void leValidaPalavra(char palavra[]);
void maisculo(char palavra[]);
void toUnderline(char palavra[], int tamanho);

int leVerificarLetra(char palavra[], char letras[]);

int main(){
	setlocale(LC_ALL , "Portuguese");
	
	char continuar = 'N';
	
	char palavra[50]  = "";
	char letras[50]   = "";
	char tema[50]     = "";
	char mensagem[50] = "";
	
	int vitoria = 0;
	int vida 	= 6;
	int i 		= 0;
	
	int jogador = 1;
	
	int vitoriasJogador1 = 0;
	int vitoriasJogador2 = 0;
	
	int countRodada   = 0;
	int countPartidas = 1;
	
	//LOOP PARA CONTINUAR O JOGO
	do{
		printf("Vez do jogador %d!\n\n", jogador);
		
		leValidaTema(tema);
		leValidaPalavra(palavra);

		maisculo(palavra);
	
		toUnderline(letras, strlen(palavra));
	
		//LOOP PARA CONTINUAR A RODADA ATÉ O JOGADOR GANHAR OU PERDER
		do {
			mostrarForca(&vida, mensagem, tema);
			mostrarLinha(letras);
			
			vida = leVerificarLetra(palavra, letras) == 1 ? vida-1 : vida;
			
			vitoria = strcmp(palavra, letras) == 0 ? 1 : 0;
		}while (vida > 0 && vitoria == 0);
	
		//ALTERA A MENSAGEM DE ACORDO COM O RESULTADO DA RODADA
		vitoria == 1 ? strncpy(mensagem, VERDE"PARABÉNS! VOCÊ VENCEU."RESET, 50) : strncpy(mensagem, VERMELHO"VOCÊ PERDEU! TENTE NOVAMENTE."RESET, 50);
	
		//VERIFICA O JOGADOR E ADICIONA O PONTO CASO TENHA VENCIDO A RODADA
		if(jogador == 1)
			vitoriasJogador1 += vitoria == 1 ? 1 : 0;
		else
			vitoriasJogador2 += vitoria == 1 ? 1 : 0;
			
		//TROCA O JOGADOR
		jogador = jogador == 1 ? 2 : 1;
	
		//MOSTRA A FORCA NO FINAL DA RODADA
		mostrarForca(&vida, mensagem, tema);
		if(vitoria == 1)
			printf(VERDE);
		mostrarLinha(letras);
		printf(RESET);
		
		printf("\n\n\n");
		
		countRodada++;
		
		//VERIFICA RODADA PARA CONTINUAR
		if(countRodada >= 2){
			countPartidas += 1;
			
			printf("Deseja continuar jogando (S - Sim, N - Não)? ");
			scanf("%c", &continuar);
			fflush(stdin);
			
			continuar = toupper(continuar);
			
			countRodada = 0;
		}else{
			printf("Precione qualquer tecla para continuar!");
			getch();
			continuar = 'S';
		}
		
		//RESETA AS VARIAVEIS
		memset(palavra, 0, sizeof(palavra));
		memset(letras, 0, sizeof(letras));
		memset(mensagem, 0, sizeof(mensagem));
		memset(tema, 0, sizeof(tema));
		
		vitoria = 0;
		vida 	= 6;
		i 		= 0;
		
		system("cls");
	}while(continuar == 'S');

	//MOSTRA O RESULTADO FINAL DA PARTIDA
	mostrarResultado(countPartidas, vitoriasJogador1, vitoriasJogador2);
	
	getch();

	return 0;
}

void leValidaTema(char tema[]){
	printf("Insira um TEMA: ");
	gets(tema);
	fflush(stdin);
}

void leValidaPalavra(char palavra[]){
	printf("Insira uma PALAVRA: ");
	gets(palavra);
	fflush(stdin);
}

void maisculo(char palavra[]){
	int i;
	for(i=0;i < strlen(palavra);i++){
		palavra[i] = toupper(palavra[i]);
	}
}

void toUnderline(char palavra[], int tamanho){
	int i;
	for(i=0;i<tamanho;i++){
		palavra[i] = '_';
	}
}

int leVerificarLetra(char palavra[], char letras[]) {
	char letra;
	int i = 0;
	int count = 0;

	printf("Digite uma letra: ");
	scanf("%c", &letra);
	fflush(stdin);

	letra = toupper(letra);

	//LOOP ENTRE AS LETRAS DA PALAVRA COMPARANDO AO INPUT
	for (i = 0; i < strlen(palavra); i++) {
		if (letra == palavra[i]) {
			letras[i] = letra;
			count++;
		}
	}
	
	//SE O INPUT NAO ESTIVER NA PALAVRA RETORNA 1
	return count == 0 ? 1 : 0;
}

//FUNCAO PARA MOSTRAR A LINHA COM AS CASAS PARA VAZIAS OU COM LETRAS
void mostrarLinha(char letras[]) {
	int i;

	for (i = 0; i < strlen(letras); i++) {
		printf("%c ", letras[i]);
	}
	
	printf("\n");
}

//FUNCAO PARA MOSTRAR FORCA COM BASE NA VIDA E MENSAGEM
void mostrarForca(int *vida, char mensagem[], char tema[]) {
	system("cls");

	switch (*vida) {
		case 0:
			printf("____	\n");
			printf("|   |   Tema: %s\n", tema);
			printf("|"VERMELHO"   o		"RESET"\n");
			printf("|"VERMELHO"  /|\\   "RESET"  %s\n", mensagem);
			printf("|"VERMELHO"  / \\ 	"RESET"\n");
			printf("|       \n");
			printf("| ");
			break;
		case 1:
			printf("____    \n");
			printf("|   |   Tema: %s\n", tema);
			printf("|   o   \n");
			printf("|  /|\\ 	%s\n", mensagem);
			printf("|  /    \n");
			printf("|       \n");
			printf("| ");
			break;
		case 2:
			printf("____    \n");
			printf("|   |   Tema: %s\n", tema);
			printf("|   o	\n");
			printf("|  /|\\		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 3:
			printf("____	\n");
			printf("|   |   Tema: %s\n", tema);
			printf("|   o	\n");
			printf("|  /|		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 4:
			printf("____	\n");
			printf("|   |   Tema: %s\n", tema);
			printf("|   o	\n");
			printf("|   |		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 5:
			printf("____	\n");
			printf("|   |   Tema: %s\n", tema);
			printf("|   o	\n");
			printf("|			%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 6:
			printf("____	\n");
			printf("|   |   Tema: %s\n", tema);
			printf("|		\n");
			printf("|			%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
	}
}

void mostrarResultado(int countPartidas, int vitoriasJogador1, int vitoriasJogador2){
	system("cls");
	
	printf("Quantidade de Partidas: %d\n\n", countPartidas);

	printf("========= PLACAR =========\n");
	printf("Vitorias\n");
	printf("Jogador 1: %d\n", vitoriasJogador1);
	printf("Jogador 2: %d\n", vitoriasJogador2);
	printf("==========================");
}
