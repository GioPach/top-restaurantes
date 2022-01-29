
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*=-=-=-=-=-=-=-=-=-=-=- PROCEDIMENTOS B�SICOS DO M�DULO =-=-=-=-=-=-=-=-=-=-=-=-=-*/



// Procedimento padr�o caso n�o consiga abrir o arquivo "restaurantes.txt".
void erroArquivo() {
	
	system("cls");
	printf("\n Erro ao abrir o arquivo!");
	printf("\n Programa encerrado...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	exit(1); // for�a encerramento -> c�digo 1 informa que o programa encerrou por uma exce��o
	
}


/*****************************************************************************
*	Verifica se foi poss�vel encontrar o arquivo.
*	ENTRADA: stream de conex�o *fp com o arquivo "restaurantes.txt".
*	SA�DA: true caso abra o arquivo com sucesso, false caso n�o. 
******************************************************************************/
bool validarArquivo(FILE *fp) {	
		
	if(fp == NULL) {
		return false;
	}	
	
	return true; // Caso encontre o arquivo
	
}


/***************************************************************************
*	Verifica se o arquivo "restaurantes.txt" j� existe no diret�rio atual.
*	SA�DA: true se j� existe, false caso contr�rio.
***************************************************************************/
bool verificaArqExiste() {
	
	FILE *fp;
	fp = fopen(FNOME, "r");
	
	bool validar = validarArquivo(fp);
	if(validar) {
		return true;
	}
	
	return false; // Caso n�o encontre o arquivo
	
}


/*************************************************************************************
*	Fun��o para calcular n�mero de restaurantes registrados na base de dados 
*	previamente. � chamada caso o arquivo "restaurantes.txt" j� exista no diret�rio
*	atual do usu�rio.
*	Importante para verificar se o tamanho da lista de restaurantes foi 
*	realocado para um valor maior em uma execu��o anterior do programa.
*	Utilizada antes do carregamento de dados na lista, pois ela ser� realocada caso 
*	o n�mero de registros retornado for maior que o tamanho padr�o de 10 posi��es.
*	RETORNO: n�mero de registros dispon�veis na base de dados "restaurantes.txt".
************************************************************************************/
int tamBaseRegistros() {
	
	int i = 0;
	
	/* Vari�veis tempor�rias para contar registros efetuados previamente na base */
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
/*=-=-=-=-=-=- CRIA��O, CARREGAMENTO E ATUALIZA��O DA BASE DE DADOS =-=--=-=-=-=-=-*/



// Procedimento padr�o para criar a base de dados "restaurantes.txt".
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
*	ENTRADA: lista de restaurantes j� alocada para tamanho correspondente �
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
*	ap�s a dele��o ou inser��o de um restaurante na lista. 
*	Optei, tamb�m, por esta abordagem na tarefa inserir, pelo vetor de restaurantes 
*	iniciar com dez posi��es vazias j� inscritas na base de dados, tornando descart�vel 
*	a implementa��o de um procedimento para escrever apenas um restaurante, por execu��o 
*	da tarefa inserir, no modo "append".
*	ENTRADA: lista de restaurantes e o n�mero de registros presentes nela, importante
*	caso o usu�rio tenha redefinido seu tamanho para um valor maior.
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

