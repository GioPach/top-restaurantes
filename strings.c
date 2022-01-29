
#include "restaurante.h"


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-= FORMATA��O DE DADOS =-=-=-=-=-=-=--=-=-=-=-=-=-=-= */



/***********************************************************************************
*	Capitaliza as letras para evitar case-sensitivity dos dados 
*	digitados pelo usu�rio. 
*	Procedimento utilizado durante a verifica��o da exist�ncia
*	de um restaurante, a partir de seu nome capitalizado, bem como de um tipo 
*	de comida digitado pelo usu�rio. 
*	Chamado nos procedimentos verificaExisteNome e verificaExisteTipo no 
*	m�dulo "lista.c". Al�m disso, � utilizado ao inserir dados de um restaurante, 
*	do tipo string, na lista e base de dados para manter os registros padronizados. 
*	ENTRADA: string digitada pelo usu�rio.
***********************************************************************************/
void capitalizarLetras(char *string) {
	
	int len = strlen(string);
		
	for(int i = 0; i < len; i++) {
		string[i] = toupper(string[i]);
	}
	
}



/*****************************************************************************
*	Substitue os espa�os em branco (" ") dos dados do tipo string de um 
*	restaurante, a ser inserido na lista e base de dados, por "_" (underline) 
*	para manter os registros padronizados.
*	ENTRADA: string auxiliar digitada pelo usu�rio.
****************************************************************************/
void removerEspacos(char *string) {
	
	int len = strlen(string); 
    
    for (int i = 0, posicao = 0; i < len; i++, posicao++) {
        if(string[posicao] == ' ') {
        	string[posicao] = '_';
		}
    
    }
   	
}


/*********************************************************************
*	Formata os dados a serem inseridos na lista e base de dados, 
*	mantendo as strings com letras capitalizadas e as suas separa��es 
*	representadas por "_".
*********************************************************************/
void formatarDadoRegistro(char *string) {
	
	capitalizarLetras(string);	// evitar case-sensitivity
	removerEspacos(string);
	
}


/*********************************************************************************
*	Substitue os "_" (underlines), adicionados aos dados do tipo string
*	formatados durante a inser��o de um restaurante, por espa�os em branco (" ") 
*	apresentar os dados ao usu�rio.
*	Procedimento utilizado nas tarefas de listagem.
*	ENTRADA: string registrada.
*****************************************************************************/
void formatarSaida(char *string) {
	
	int len = strlen(string); 
    
    for (int i = 0; i < len; i++) {
        if(string[i] == '_') {
        	string[i] = ' ';
		}
    
    }
   	
}

