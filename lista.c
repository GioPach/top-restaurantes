
#include "arquivos.c"
#include "strings.c"
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-=-= CONTROLE DE POSIÇÕES VAZIAS -=-=-=-=-=-=-=-=-=-=-=-= */



/***************************************************************************
*	Procedimento padrão utilizado ao inicializar as posições do vetor de 
*	restaurantes *lista ou ao deletar um restaurante.
*	ENTRADA: lista de restaurantes e a posição nela a ser inicializada ou 
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
*	Inicialização do vetor de restaurantes *lista com os 
*	valores padrão definidos pelo programador. 
*	Optei por definir uma posição vazia através do ID para o controle 
*	das tarefas a serem realizadas ou não. É iniciado com o valor -1
*	(POS_VAZIA), pois a lista de restaurantes e a base de dados são 
*	processadas	de modo a manter os registros em ordem crescente por ID, 
*	começando do valor 0.
*	As strings são "underlines" para facilitar a leitura da base de dados,
*	caso o programador desejar abrir o arquivo "restaurantes.txt".
*	Procedimento utilizado após o alocamento da lista.
*************************************************************************/
void inicializarLista(Restaurante *lista, int tamLista) {
	
	for(int i = 0; i < tamLista; i++) {
		zerarPosicao(lista, i);
	}
	
}


/*********************************************************************************
*	Remove um restaurante da lista ao reinicializar os seus dados. Controle 
*	do restaurante a ser deletado a partir do ID digitado pelo usuário na 
*	tarefa deletar.
*	ENTRADA: lista de restaurantes, o tamanho da lista a percorrer (para o caso 
*	do usuário ter alterado) e o ID do restaurante a ser removido.
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
*	Procedimento padrão para manter a lista por ordem crescente de IDs.
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
*	Procedimento padrão para manter as posições vazias ao fim da lista.
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
*	Procedimento padrão para manter IDs correspondentes ao índice que
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
*	Procedimento padrão para ordenar a lista de restaurantes de modo
*	a mantê-la em ordem crescente por ID com todas as posições vazias
*	localizadas ao seu fim.
*	Utilizado após a inserção ou deleção de um restaurante do vetor
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
*	Procedimento padrão para obter a primeira posição vazia no vetor 
*	de restaurantes *lista.
*	Utilizado para o controle de posição disponível para registro.
*	ENTRADA: lista de restaurantes e o seu tamanho (para o caso do usuário 
*	ter alterado).
*	RETORNO: primeira posição vazia ou o tamanho atual da lista, caso esteja
*	cheia.
***************************************************************************/
int posicaoVazia(Restaurante *lista, int tamLista) {
	
	for(int i = 0; i < tamLista; i++) {
		if(lista[i].id == POS_VAZIA) {
			return i; // primeira posição vazia
		}
	}
	
	return tamLista; // caso não haja nenhuma posição vazia
	
}


/************************************************************************
*	Verifica se existe um restaurante, no vetor de restaurantes *lista,
*	com nota superior à nota-filtro digitada na tarefa listarPorNota.	
*	ENTRADA: lista de restaurantes, seu tamanho e a nota digitada na
*	tarefa listarPorNota.
*	SAÍDA: true caso encontre, false caso contrário.
************************************************************************/
bool verificaNota(Restaurante *lista, int tamLista, int nota) {

	for(int i = 0; i < tamLista; i++) {		
		if(lista[i].nota > nota) {		
			return true; // caso encontre um restaurante com nota superior 
		}
	}
	
	return false; // caso percorra a lista inteira e não encontre
	
}


/****************************************************************************
*	Verifica se existe um restaurante, no vetor de restaurantes *lista,
*	com o tipo de comida solicitado na tarefa listarPorComida.	
*	ENTRADA: lista de restaurantes, seu tamanho e o tipo de comida digitado 
*	na tarefa listarPorComida.
*	SAÍDA: true caso valide a busca, false caso contrário.
****************************************************************************/
bool verificaExisteTipo(Restaurante *lista, int tamLista, char *tipo) {
	
	capitalizarLetras(tipo); // strings.c --> evitar case-sensitivity.
	
	for(int i = 0; i < tamLista; i++) {		
		if((strcmp(lista[i].tipoComida, tipo)) == 0) {		
			return true; // caso encontre um restaurante com o tipo de comida
		}
	}
	
	return false; // caso percorra a lista inteira e não encontre
	
}


/************************************************************************
*	Verifica se o restaurante já foi inserido na lista através do nome 
*	digitado pelo usuário na tarefa inserir.
*	ENTRADA: lista de restaurantes, seu tamanho e o nome do restaurante 
*	digitado na tarefa inserir.
*	SAÍDA: true caso valide a busca, false caso contrário.
************************************************************************/
bool verificaExisteNome(Restaurante *lista, int tamLista, char *nome) {
	
	capitalizarLetras(nome);
	
	for(int i = 0; i < tamLista; i++) {
		if((strcmp(lista[i].nome, nome)) == 0) {
			return true;
		}
	}
	
	return false; // caso percorra a lista inteira e não encontre.	
	
}


/****************************************************************************
*	Verifica se existe um restaurante com o ID digitado na tarefa deletar.
*	Caso sim, copia seu nome para a string global auxiliar *nomeAux.
*	ENTRADA: lista de restaurantes, seu tamanho e o ID do restaurante 
*	digitado na tarefa. Além disso, o ponteiro para string *nomeAux, criado na 
*	tarefa deletar, carrega o nome do restaurante para confirmar sua deleção.
*	SAÍDA: true caso o restaurante exista na lista, false caso contrário.
****************************************************************************/
bool verificaExisteId(Restaurante *lista, int tamLista, int id, char *nomeAux) {
	
	for(int i = 0; i < tamLista; i++) {		
		// garantir que o restaurante com ID digitado existe
		if(lista[i].id == id) {	
			// copiar nome do restaurante para string auxiliar para confirmar deleção
			strcpy(nomeAux, lista[i].nome);	
			formatarSaida(nomeAux); // strings.c 
			return true; // restaurante com o ID digitado existe
		} 				
	}	

	return false; // caso percorra a lista inteira e não encontre.
	
}

