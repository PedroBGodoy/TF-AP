#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <locale.h>

//UTILIZAR COR SOMENTE SE A PLATAFORMA SUPORTAR, CASO CONTRARIO, COMENTE AS TRÊS LINHAS E TIRE O COMENTARIO DAS OUTRAS TRÊS
#define VERMELHO "\033[0;31m"
#define VERDE "\033[0;32m"
#define RESET "\033[0m"

//TIRAR COMENTÁRIO CASO NÃO SEJA SUPORTADO AS CORES NA PLATAFORMA
//#define VERMELHO ""
//#define VERDE ""
//#define RESET ""

void mostrarLinha(char letras[]);
void mostrarForca(int vida, char mensagem[], char tema[]);
void mostrarResultado(int countTotalRodadas, int countPartidas, int vitoriasJogador1, int vitoriasJogador2);
void maiusculo(char palavra[]);
void mensagemResultado(char mensagem[], int vitoria);
void verificaVitoriaJogador(int *jogador, int vitoria, int *vitoriasJogador1, int *vitoriasJogador2);
void mostrarResultadoRodada(int vida, char mensagem[], char tema[], char palavra[], char letras[], int vitoria);
void verificaContinuarRodada(int *countRodada, int *countPartidas, char *continuar);

int loopRodada(int vida, char mensagem[], char tema[], char palavra[], char letras[]);
int leVerificarLetra(char palavra[], char letras[]);
int verificarTentativa(char palavra[]);
int leValidaTema(char tema[]);
int leValidaPalavra(char palavra[]);

char verificaContinuar();

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
	
	int countRodada   	  = 0;
	int countTotalRodadas = 0;
	int countPartidas 	  = 0;
	
	//LOOP PARA CONTINUAR O JOGO
	do{
		system("cls");
		
		printf("Vez do jogador %d!\n\n", jogador);
		
		//LE E VALIDA OS INPUTS INICINAIS
		leValidaTema(tema);
		leValidaPalavra(palavra);
		
		//PEGAR CADA CARACTER E TRANSFORMAR EM UNDERLINE
		for(i=0;i<strlen(palavra);i++){
			letras[i] = '_';
		}
		
		//LOOP DAS RODADAS
		vitoria = loopRodada(vida, mensagem, tema, palavra, letras);
	
		//MOSTRA O RESULTADO FINAL DA RODADA
		mensagemResultado(mensagem, vitoria);
	
		//VERIFICA O JOGADOR E ADICIONA O PONTO CASO TENHA VENCIDO
		verificaVitoriaJogador(&jogador, vitoria, &vitoriasJogador1, &vitoriasJogador2);
	
		//MOSTRA RESULTADO DA RODADA
		mostrarResultadoRodada(vida, mensagem, tema, palavra, letras, vitoria);
		
		printf("\n\n\n");
				
		countRodada++;
		countTotalRodadas++;
		
		//VERIFICA SE QUER CONTINUAR A CADA 2 RODADAS(1 PARTIDA)
		verificaContinuarRodada(&countRodada, &countPartidas, &continuar);
		
		//RESETA AS VARIAVEIS
		memset(palavra, 0, sizeof(palavra));
		memset(letras, 0, sizeof(letras));
		memset(mensagem, 0, sizeof(mensagem));
		memset(tema, 0, sizeof(tema));
		
		vitoria = 0;
		vida 	= 6;
		i 		= 0;
	}while(continuar == 'S');

	//MOSTRA O RESULTADO FINAL DA PARTIDA
	mostrarResultado(countTotalRodadas, countPartidas, vitoriasJogador1, vitoriasJogador2);
	
	getch();

	return 0;
}

int loopRodada(int vida, char mensagem[], char tema[], char palavra[], char letras[]){
	int vitoria = 0;
	
	//LOOP PARA CONTINUAR A RODADA ATÉ O JOGADOR GANHAR OU PERDER
	do {
		mostrarForca(vida, mensagem, tema);
		mostrarLinha(letras);
		
		int retorno = leVerificarLetra(palavra, letras);
		
		if(retorno == -1){
			int tentativa = verificarTentativa(palavra);
			if(tentativa == 1){
				vitoria = 1;
				strncpy(letras, palavra, 50);
			}else{
				vida = 0;
			}
			break;
		}else{
			vida = retorno == 1 ? vida-1 : vida;
		}

		vitoria = strcmp(palavra, letras) == 0 ? 1 : 0;
	}while (vida > 0 && vitoria == 0);
	
	return vitoria;
}

void mensagemResultado(char mensagem[], int vitoria){
	if(vitoria == 1){
		strncpy(mensagem, VERDE"PARABÉNS! VOCÊ VENCEU."RESET, 50);
	}else{
		strncpy(mensagem, VERMELHO"VOCÊ PERDEU! TENTE NOVAMENTE."RESET, 50);
	}
}

void verificaVitoriaJogador(int *jogador, int vitoria, int *vitoriasJogador1, int *vitoriasJogador2){
	if(*jogador == 1){
		*vitoriasJogador1 += vitoria == 1 ? 1 : 0;
		*jogador = 2;
	}else{
		*vitoriasJogador2 += vitoria == 1 ? 1 : 0;
		*jogador = 1;
	}
}

void verificaContinuarRodada(int *countRodada, int *countPartidas, char *continuar){
	if(*countRodada >= 2){
		*countPartidas += 1;
		
		*continuar = verificaContinuar();
		
		*countRodada = 0;
	}else{
		printf("Precione qualquer tecla para continuar!");
		getch();
		*continuar = 'S';
	}
}

//TRANSFORMA A PALAVRA EM MAIUSCULA
void maiusculo(char palavra[]){
	int i = 0;
	for(i=0;i < strlen(palavra);i++){
		palavra[i] = toupper(palavra[i]);
	}
}

//FUNCAO PARA LER E VERIFICAR A LETRA INSERIDA
int leVerificarLetra(char palavra[], char letras[]) {
	char letra;
	int i = 0;
	int count = 0;

	printf("\nPara chutar Digite '='\n\n");

	printf("Digite uma letra: ");
	scanf("%c", &letra);
	fflush(stdin);

	letra = toupper(letra);

	if(letra == '='){
		return -1;
	}

	//LOOP ENTRE AS LETRAS DA PALAVRA COMPARANDO AO INPUT
	for (i = 0; i < strlen(palavra); i++) {
		if (letra == palavra[i]) {
			letras[i] = letra;
			count++;
		}
	}
	
	//SE O INPUT NAO ESTIVER NA PALAVRA RETORNA 1
	if(count == 0){
		return 1;
	}else{
		return 0;
	}
}

//VERIFICA TENTATIVA DO JOGADOR
int verificarTentativa(char palavra[]){
	char tentativa[50];
	
	printf("Qual é a palavra? ");
	gets(tentativa);
	
	maiusculo(tentativa);
	
	return strcmp(palavra, tentativa) == 0 ? 1 : 0;
}

//VERIFICA SE O INPUT DO TEMA ESTA CORRETO
int leValidaTema(char tema[]){
	do{
		printf("Insira um TEMA: ");
		gets(tema);
		fflush(stdin);
			
		if(strlen(tema) < 3){
			printf("O TEMA deve conter no mínimo 3 caracteres!\n\n");
		}
	}while(strlen(tema) < 3);
	
	return 0;
}

//VERIFICA SE O INPUT DA PALAVRA ESTA CORRETA
int leValidaPalavra(char palavra[]){
	do{
		printf("Insira uma PALAVRA: ");
		gets(palavra);
		fflush(stdin);
		
		if(strlen(palavra) < 3){
			printf("A PALAVRA deve conter no mínimo 3 caracteres!\n\n");
		}
	}while(strlen(palavra) < 3);

	maiusculo(palavra);
	
	return 0;
}

//VERIFICA SE O JOGADOR DESEJA CONTINUAR JOGANDO
char verificaContinuar(){
	char continuar;
	
	printf("Deseja continuar jogando (S - Sim, N - Não)? ");
	scanf("%c", &continuar);
	fflush(stdin);
	
	continuar = toupper(continuar);
	
	return continuar;
}

//FUNCAO PARA MOSTRAR A LINHA COM AS CASAS PARA VAZIAS OU COM LETRAS
void mostrarLinha(char letras[]) {
	int i;
	
	for (i = 0; i < strlen(letras); i++) {
		printf("%c  ", letras[i]);
	}
	
	printf("\n");
}

//FUNCAO PARA MOSTRAR FORCA COM BASE NA VIDA E MENSAGEM
void mostrarForca(int vida, char mensagem[], char tema[]) {
	//LIMPA A TELA
	system("cls");

	switch (vida) {
		case 0:
			printf("_______	\n");
			printf("|      |       Tema: %s\n", tema);
			printf("|"VERMELHO"      o		"RESET"\n");
			printf("|"VERMELHO"     /|\\   "RESET"  %s\n", mensagem);
			printf("|"VERMELHO"     / \\ 	"RESET"\n");
			printf("|       \n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 1:
			printf("_______    \n");
			printf("|      |       Tema: %s\n", tema);
			printf("|      o   \n");
			printf("|     /|\\ 	%s\n", mensagem);
			printf("|     /    \n");
			printf("|       \n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 2:
			printf("_______    \n");
			printf("|      |       Tema: %s\n", tema);
			printf("|      o	\n");
			printf("|     /|\\		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 3:
			printf("_______	\n");
			printf("|      |       Tema: %s\n", tema);
			printf("|      o	\n");
			printf("|     /|		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 4:
			printf("_______	\n");
			printf("|      |       Tema: %s\n", tema);
			printf("|      o	\n");
			printf("|      |		%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 5:
			printf("_______	\n");
			printf("|      |       Tema: %s\n", tema);
			printf("|      o	\n");
			printf("|			%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;
		case 6:
			printf("_______	\n");
			printf("|      |       Tema: %s\n", tema);
			printf("|		\n");
			printf("|			%s\n", mensagem);
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("|		\n");
			printf("| ");
			break;

	}
}

//FUNÇÃO PARA MOSTRAR FORCA E LINHA COM BASE NA VITORIA
void mostrarResultadoRodada(int vida, char mensagem[], char tema[], char palavra[], char letras[], int vitoria){
	mostrarForca(vida, mensagem, tema);
	if(vitoria == 1)
		printf(VERDE);
	mostrarLinha(letras);
	printf(RESET);
}

void mostrarResultado(int countTotalRodadas, int countPartidas, int vitoriasJogador1, int vitoriasJogador2){
	system("cls");
	
	printf("Quantidade de Partidas: %d\n", countPartidas);
	printf("Quantidade de Rodadas: %d\n", countTotalRodadas);
	
	printf("\n");

	printf("========= PLACAR =========\n");
	printf("Acertos\n");
	printf("Jogador 1: %d\n", vitoriasJogador1);
	printf("Jogador 2: %d\n", vitoriasJogador2);
	printf("==========================");
}
