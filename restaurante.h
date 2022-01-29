#ifndef RESTAURANTE

#define RESTAURANTE

#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define TAM_PADRAO 10 // Utilizada para setar tamanho inicial da lista de restaurantes
#define TAM_STRING 40 // Utilizada para setar tamanho de strings 
#define LIMITE 30 // Utilizada para setar limite de expansão de registros
#define FNOME "restaurantes.txt" // Nome do arquivo padrão para armazenar dados
#define POS_VAZIA -1 // Utilizada para indicar posição vazia na lista de restaurantes e base de dados

#define WAIT 2000 // Utilizada para manter interação com o usuário --> Sleep(WAIT) --> tempo em milissegundos

// Utilizadas para formatar saídas:
#define DIV "----------------------------------"
#define BAR "=========================="

typedef struct {
	
	int id; 
	char nome[TAM_STRING];
	char bairro[TAM_STRING];
	char cidade[TAM_STRING];
	char tipoComida[TAM_STRING];	
	int nota;
	
} Restaurante;


#endif // RESTAURANTE

