
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*=-=-=-=-=-=-=-=-=-=-=- PROCEDIMENTOS BÁSICOS DO MÓDULO =-=-=-=-=-=-=-=-=-=-=-=-=-*/



// Procedimento padrão caso não consiga abrir o arquivo "restaurantes.txt".
void erroArquivo() {
	
	system("cls");
	printf("\n Erro ao abrir o arquivo!");
	printf("\n Programa encerrado...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	exit(1); // força encerramento -> código 1 informa que o programa encerrou por uma exceção
	
}


/*****************************************************************************
*	Verifica se foi possível encontrar o arquivo.
*	ENTRADA: stream de conexão *fp com o arquivo "restaurantes.txt".
*	SAÍDA: true caso abra o arquivo com sucesso, false caso não. 
******************************************************************************/
bool validarArquivo(FILE *fp) {	
		
	if(fp == NULL) {
		return false;
	}	
	
	return true; // Caso encontre o arquivo
	
}


/***************************************************************************
*	Verifica se o arquivo "restaurantes.txt" já existe no diretório atual.
*	SAÍDA: true se já existe, false caso contrário.
***************************************************************************/
bool verificaArqExiste() {
	
	FILE *fp;
	fp = fopen(FNOME, "r");
	
	bool validar = validarArquivo(fp);
	if(validar) {
		return true;
	}
	
	return false; // Caso não encontre o arquivo
	
}


/*************************************************************************************
*	Função para calcular número de restaurantes registrados na base de dados 
*	previamente. É chamada caso o arquivo "restaurantes.txt" já exista no diretório
*	atual do usuário.
*	Importante para verificar se o tamanho da lista de restaurantes foi 
*	realocado para um valor maior em uma execução anterior do programa.
*	Utilizada antes do carregamento de dados na lista, pois ela será realocada caso 
*	o número de registros retornado for maior que o tamanho padrão de 10 posições.
*	RETORNO: número de registros disponíveis na base de dados "restaurantes.txt".
************************************************************************************/
int tamBaseRegistros() {
	
	int i = 0;
	
	/* Variáveis temporárias para contar registros efetuados previamente na base */
	int tmp1;
	char tmp2[TAM_STRING];
	
	FILE *fp;
	
	fp = fopen(FNOME, "r");
	bool abrir = validarArquivo(fp);
	
	if(abrir) {		
		while(fscanf(fp, "%d %s %s %s %s %d", &tmp1, &tmp2, &tmp2, &tmp2, &tmp2, &tmp1) != EOF ) {
			i++;
		}
		fclose(fp);						
	}	
	else {
		fclose(fp);
		erroArquivo();		
	}	
	
	return i;
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*=-=-=-=-=-=- CRIAÇÃO, CARREGAMENTO E ATUALIZAÇÃO DA BASE DE DADOS =-=--=-=-=-=-=-*/



// Procedimento padrão para criar a base de dados "restaurantes.txt".
void criarArquivo() {
	
	FILE *fp;
	fp = fopen(FNOME, "w");	
	fclose(fp);
	
	printf("\n Arquivo criado com sucesso...");
	Sleep(WAIT);		
			
	system("cls");
	
}


/*****************************************************************************
*	Carrega os restaurantes, registrados na base de dados "restaurantes.txt",
*	no vetor de restaurantas *lista.
*	ENTRADA: lista de restaurantes já alocada para tamanho correspondente à
*	base de dados.
*****************************************************************************/
void carregarDados(Restaurante *lista) {
	
	int i = 0;
	
	FILE *fp; 
	
	fp = fopen(FNOME, "r");
	bool abrir = validarArquivo(fp);
	
	if(abrir) {		
		while(fscanf(fp, "%d %s %s %s %s %d", &lista[i].id, lista[i].nome, lista[i].bairro, lista[i].cidade, lista[i].tipoComida, &lista[i].nota) != EOF ) {
			i++;
		}
		fclose(fp);						
	}	
	else {
		fclose(fp);
		erroArquivo();		
	}	
	
}


/**************************************************************************************
*	Abre a base de dados "restaurantes.txt" e reescreve a lista de restaurantes
*	após a deleção ou inserção de um restaurante na lista. 
*	Optei, também, por esta abordagem na tarefa inserir, pelo vetor de restaurantes 
*	iniciar com dez posições vazias já inscritas na base de dados, tornando descartável 
*	a implementação de um procedimento para escrever apenas um restaurante, por execução 
*	da tarefa inserir, no modo "append".
*	ENTRADA: lista de restaurantes e o número de registros presentes nela, importante
*	caso o usuário tenha redefinido seu tamanho para um valor maior.
*************************************************************************************/
void atualizarRegistros(Restaurante *lista, int tamLista) {
	
	FILE *fp;
		
	fp = fopen(FNOME, "w");
	bool abrir = validarArquivo(fp);
	
	if(abrir) {
		
		for(int i = 0; i < tamLista; i++) {			
			fprintf(fp, "%d %s %s %s %s %d\n", lista[i].id, lista[i].nome, lista[i].bairro, lista[i].cidade, lista[i].tipoComida, lista[i].nota);			
		}
		
		fclose(fp);
				
	} else {
		erroArquivo();
	}
			
}

