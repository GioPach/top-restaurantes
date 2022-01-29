
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-= INTERA��O COM O USU�RIO NO M�DULO "MENU.C" =-=-=-=-=-=-=-=-= */



// Procedimento padr�o caso n�o haja registros na base de dados.
void msgListaVazia() {
	
	printf("\n Nenhum restaurante foi inserido na lista ainda...");
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padr�o caso o n�mero m�ximo de registros na base de dados tenha sido alcan�ado.
void msgListaCheia() {
	
	printf("\n A lista est� cheia...");					
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padr�o caso o usu�rio solicite expandir o restaurante ap�s j� ter atingido o limite m�ximo de expans�o (30).
void msgLimiteAtingido() {
	
	printf("\n Limite de restaurantes a serem registrados j� foi atingido!");
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padr�o caso o usu�rio solicite uma tarefa incorretamente.
void erroToken() {
	
	system("cls");
	printf("\n Tarefa solicitada incorretamente...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	system("cls");
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-= INTERA��O COM O USU�RIO NO M�DULO "TAREFAS.C" -=-=-=-=-=-=-=-= */



/*************************************************************************
*	Procedimento padr�o utilizado caso:
*		1. Usu�rio solicite a inser��o de um restaurante que j� 
*		est� na lista (controle a partir do nome).
*		2. Usu�rio solicite deletar um restaurante que n�o est� na 
*		lista, recuse uma dele��o ou a confirme incorretamente.	
*		3. Usu�rio solicite expandir a lista e a base de dados para
*		um valor menor ou igual ao limite atual de registros, bem como
*		ao solicitar a expans�o da lista ap�s j� ter alcan�ado o limite.
*		4. N�o haja espa�o suficiente, na mem�ria da m�quina do usu�rio,
*		para executar uma tarefa adequadamente. 
************************************************************************/
void cancelarTarefa() {	
	
	system("cls");
	printf("\n Tarefa cancelada...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	system("cls");
		
}


// Procedimento padr�o para informar o usu�rio que a tarefa solicitada foi finalizada.
void msgSucesso() {
	
	printf("\n\n Tarefa executada com sucesso!\n");
	Sleep(WAIT);	
	system("cls");	
	
}


// Procedimento padr�o caso um ponteiro n�o seja inicializado adequadamente (mem�ria insuficiente).
void msgErroAloc() {
	
	printf("\n Mem�ria insuficiente para executar tarefa!");
	Sleep(WAIT);
	cancelarTarefa();
	
}


/************************************************************************
*	Procedimento padr�o que aguarda o usu�rio pressionar uma 
*	tecla, durante a visualiza��o de uma tarefa de listagem, para sair.
************************************************************************/
void esperarSaida() {
	
	char ch;
	
	printf("\n\n => Pressione qualquer tecla para sair...");
	ch = getch();
	
	system("cls");
}

