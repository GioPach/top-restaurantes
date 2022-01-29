
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-= INTERAÇÃO COM O USUÁRIO NO MÓDULO "MENU.C" =-=-=-=-=-=-=-=-= */



// Procedimento padrão caso não haja registros na base de dados.
void msgListaVazia() {
	
	printf("\n Nenhum restaurante foi inserido na lista ainda...");
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padrão caso o número máximo de registros na base de dados tenha sido alcançado.
void msgListaCheia() {
	
	printf("\n A lista está cheia...");					
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padrão caso o usuário solicite expandir o restaurante após já ter atingido o limite máximo de expansão (30).
void msgLimiteAtingido() {
	
	printf("\n Limite de restaurantes a serem registrados já foi atingido!");
	Sleep(WAIT);
	system("cls");
	
}


// Procedimento padrão caso o usuário solicite uma tarefa incorretamente.
void erroToken() {
	
	system("cls");
	printf("\n Tarefa solicitada incorretamente...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	system("cls");
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-= INTERAÇÃO COM O USUÁRIO NO MÓDULO "TAREFAS.C" -=-=-=-=-=-=-=-= */



/*************************************************************************
*	Procedimento padrão utilizado caso:
*		1. Usuário solicite a inserção de um restaurante que já 
*		está na lista (controle a partir do nome).
*		2. Usuário solicite deletar um restaurante que não está na 
*		lista, recuse uma deleção ou a confirme incorretamente.	
*		3. Usuário solicite expandir a lista e a base de dados para
*		um valor menor ou igual ao limite atual de registros, bem como
*		ao solicitar a expansão da lista após já ter alcançado o limite.
*		4. Não haja espaço suficiente, na memória da máquina do usuário,
*		para executar uma tarefa adequadamente. 
************************************************************************/
void cancelarTarefa() {	
	
	system("cls");
	printf("\n Tarefa cancelada...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	system("cls");
		
}


// Procedimento padrão para informar o usuário que a tarefa solicitada foi finalizada.
void msgSucesso() {
	
	printf("\n\n Tarefa executada com sucesso!\n");
	Sleep(WAIT);	
	system("cls");	
	
}


// Procedimento padrão caso um ponteiro não seja inicializado adequadamente (memória insuficiente).
void msgErroAloc() {
	
	printf("\n Memória insuficiente para executar tarefa!");
	Sleep(WAIT);
	cancelarTarefa();
	
}


/************************************************************************
*	Procedimento padrão que aguarda o usuário pressionar uma 
*	tecla, durante a visualização de uma tarefa de listagem, para sair.
************************************************************************/
void esperarSaida() {
	
	char ch;
	
	printf("\n\n => Pressione qualquer tecla para sair...");
	ch = getch();
	
	system("cls");
}

