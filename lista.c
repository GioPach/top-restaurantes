
#include "arquivos.c"
#include "strings.c"
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-=-= CONTROLE DE POSI��ES VAZIAS -=-=-=-=-=-=-=-=-=-=-=-= */



/***************************************************************************
*	Procedimento padr�o utilizado ao inicializar as posi��es do vetor de 
*	restaurantes *lista ou ao deletar um restaurante.
*	ENTRADA: lista de restaurantes e a posi��o nela a ser inicializada ou 
*	deletada.
***************************************************************************/
void zerarPosicao(Restaurante *lista, int posicao) {
	
	lista[posicao].id = POS_VAZIA; 
	strcpy(lista[posicao].nome, "_");
	strcpy(lista[posicao].bairro, "_");
	strcpy(lista[posicao].cidade, "_");			
	strcpy(lista[posicao].tipoComida, "_");
	lista[posicao].nota = 0;	
		
}


/*************************************************************************
*	Inicializa��o do vetor de restaurantes *lista com os 
*	valores padr�o definidos pelo programador. 
*	Optei por definir uma posi��o vazia atrav�s do ID para o controle 
*	das tarefas a serem realizadas ou n�o. � iniciado com o valor -1
*	(POS_VAZIA), pois a lista de restaurantes e a base de dados s�o 
*	processadas	de modo a manter os registros em ordem crescente por ID, 
*	come�ando do valor 0.
*	As strings s�o "underlines" para facilitar a leitura da base de dados,
*	caso o programador desejar abrir o arquivo "restaurantes.txt".
*	Procedimento utilizado ap�s o alocamento da lista.
*************************************************************************/
void inicializarLista(Restaurante *lista, int tamLista) {
	
	for(int i = 0; i < tamLista; i++) {
		zerarPosicao(lista, i);
	}
	
}


/*********************************************************************************
*	Remove um restaurante da lista ao reinicializar os seus dados. Controle 
*	do restaurante a ser deletado a partir do ID digitado pelo usu�rio na 
*	tarefa deletar.
*	ENTRADA: lista de restaurantes, o tamanho da lista a percorrer (para o caso 
*	do usu�rio ter alterado) e o ID do restaurante a ser removido.
********************************************************************************/
void removerDaLista(Restaurante *lista, int tamLista, int id) {
	
	for(int i = 0; i < tamLista; i++) {
		
		if(lista[i].id == id) {
			zerarPosicao(lista, i);
			break;		
		}
		
	}
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ORDENAR LISTA -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */



/************************************************************************
*	Procedimento padr�o para manter a lista por ordem crescente de IDs.
*	ENTRADA: lista de restaurantes e seu tamanho.
************************************************************************/
void bubbleSortId(Restaurante *lista, int tamLista) {
	
	Restaurante aux; // para reposicionar restaurantes 
	
	for(int i = 1; i < tamLista; i++) {
       
        for(int j = 0; j < tamLista - 1; j++) {
            
            if(lista[j].id > lista[j + 1].id) {
            	
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
                
            }
        }
    }	
	
}


/***********************************************************************
*	Procedimento padr�o para manter as posi��es vazias ao fim da lista.
*	ENTRADA: lista de restaurantes e seu tamanho.
***********************************************************************/
void bubbleSortPos(Restaurante *lista, int tamLista) {
	
	Restaurante aux;
	
    for(int i = 1; i < tamLista; i++) {
       
        for(int j = 0; j < tamLista - 1; j++) {
            
            if(lista[j].id == POS_VAZIA) {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }	
	
}


/*********************************************************************
*	Procedimento padr�o para manter IDs correspondentes ao �ndice que
*	o restaurante ocupa no vetor de restaurantes *lista.
*	ENTRADA: lista de restaurantes e seu tamanho.
*********************************************************************/
void atualizarIds(Restaurante *lista, int tamLista) {
		
	for(int i = 0; i < tamLista; i++) {
		
		if(lista[i].id != POS_VAZIA) {
			lista[i].id = i;
		}	
		
	}
	
}


/*******************************************************************
*	Procedimento padr�o para ordenar a lista de restaurantes de modo
*	a mant�-la em ordem crescente por ID com todas as posi��es vazias
*	localizadas ao seu fim.
*	Utilizado ap�s a inser��o ou dele��o de um restaurante do vetor
*	de restaurantes *lista e da base de dados.
*	ENTRADA: lista de restaurantes e seu tamanho.
*******************************************************************/
void ordenarLista(Restaurante *lista, int tamLista) {

    bubbleSortId(lista, tamLista);	 
	bubbleSortPos(lista, tamLista);	
	atualizarIds(lista, tamLista);
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-=-= VERIFICAR VALORES NA LISTA -=-=-=-=--=-=-=-=-=-=-=-= */



/****************************************************************************
*	Procedimento padr�o para obter a primeira posi��o vazia no vetor 
*	de restaurantes *lista.
*	Utilizado para o controle de posi��o dispon�vel para registro.
*	ENTRADA: lista de restaurantes e o seu tamanho (para o caso do usu�rio 
*	ter alterado).
*	RETORNO: primeira posi��o vazia ou o tamanho atual da lista, caso esteja
*	cheia.
***************************************************************************/
int posicaoVazia(Restaurante *lista, int tamLista) {
	
	for(int i = 0; i < tamLista; i++) {
		if(lista[i].id == POS_VAZIA) {
			return i; // primeira posi��o vazia
		}
	}
	
	return tamLista; // caso n�o haja nenhuma posi��o vazia
	
}


/************************************************************************
*	Verifica se existe um restaurante, no vetor de restaurantes *lista,
*	com nota superior � nota-filtro digitada na tarefa listarPorNota.	
*	ENTRADA: lista de restaurantes, seu tamanho e a nota digitada na
*	tarefa listarPorNota.
*	SA�DA: true caso encontre, false caso contr�rio.
************************************************************************/
bool verificaNota(Restaurante *lista, int tamLista, int nota) {

	for(int i = 0; i < tamLista; i++) {		
		if(lista[i].nota > nota) {		
			return true; // caso encontre um restaurante com nota superior 
		}
	}
	
	return false; // caso percorra a lista inteira e n�o encontre
	
}


/****************************************************************************
*	Verifica se existe um restaurante, no vetor de restaurantes *lista,
*	com o tipo de comida solicitado na tarefa listarPorComida.	
*	ENTRADA: lista de restaurantes, seu tamanho e o tipo de comida digitado 
*	na tarefa listarPorComida.
*	SA�DA: true caso valide a busca, false caso contr�rio.
****************************************************************************/
bool verificaExisteTipo(Restaurante *lista, int tamLista, char *tipo) {
	
	capitalizarLetras(tipo); // strings.c --> evitar case-sensitivity.
	
	for(int i = 0; i < tamLista; i++) {		
		if((strcmp(lista[i].tipoComida, tipo)) == 0) {		
			return true; // caso encontre um restaurante com o tipo de comida
		}
	}
	
	return false; // caso percorra a lista inteira e n�o encontre
	
}


/************************************************************************
*	Verifica se o restaurante j� foi inserido na lista atrav�s do nome 
*	digitado pelo usu�rio na tarefa inserir.
*	ENTRADA: lista de restaurantes, seu tamanho e o nome do restaurante 
*	digitado na tarefa inserir.
*	SA�DA: true caso valide a busca, false caso contr�rio.
************************************************************************/
bool verificaExisteNome(Restaurante *lista, int tamLista, char *nome) {
	
	capitalizarLetras(nome);
	
	for(int i = 0; i < tamLista; i++) {
		if((strcmp(lista[i].nome, nome)) == 0) {
			return true;
		}
	}
	
	return false; // caso percorra a lista inteira e n�o encontre.	
	
}


/****************************************************************************
*	Verifica se existe um restaurante com o ID digitado na tarefa deletar.
*	Caso sim, copia seu nome para a string global auxiliar *nomeAux.
*	ENTRADA: lista de restaurantes, seu tamanho e o ID do restaurante 
*	digitado na tarefa. Al�m disso, o ponteiro para string *nomeAux, criado na 
*	tarefa deletar, carrega o nome do restaurante para confirmar sua dele��o.
*	SA�DA: true caso o restaurante exista na lista, false caso contr�rio.
****************************************************************************/
bool verificaExisteId(Restaurante *lista, int tamLista, int id, char *nomeAux) {
	
	for(int i = 0; i < tamLista; i++) {		
		// garantir que o restaurante com ID digitado existe
		if(lista[i].id == id) {	
			// copiar nome do restaurante para string auxiliar para confirmar dele��o
			strcpy(nomeAux, lista[i].nome);	
			formatarSaida(nomeAux); // strings.c 
			return true; // restaurante com o ID digitado existe
		} 				
	}	

	return false; // caso percorra a lista inteira e n�o encontre.
	
}

