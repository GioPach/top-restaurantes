
#include "tarefas.c" 
#include "restaurante.h" 



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* =-=-= PROCEDIMENTO DE CRIAÇÃO DA LISTA E BASE DE DADOS (SISTEMA-USUÁRIO) -=-=-= */



/**********************************************************************************************
*	Solicita, ao usuário, confirmação para criar o arquivo "restaurantes.txt"
*	caso não exista no diretório atual. Após isso, inicializa a lista com os
*	valores padrão e os registra na base de dados. Caso recuse, o programa é encerrado.
*	Se o arquivo "restaurantes.txt" já existir, o número de registros efetuados nele 
*	será calculado para uma possível realocação do tamanho do vetor de restaurantes, pois
*	o usuário pode ter expandido em uma execução anterior. Após isso, inicializa a lista 
*	com os valores padrão e carrega os dados da base nela.
*	ENTRADA: vetor de restaurantes *lista alocado inicialmente com o tamanho
*	padrão, definido pelo programador. Além disso, o ponteiro que carrega o tamanho da lista
*	para ser passado às chamadas de tarefa no laço de execução em iniciar().
*	RETORNO: retorna a lista devidamente alocada e possivelmente já carregada de registros.
**********************************************************************************************/
Restaurante *usrCriarBase(Restaurante *lista, int *tamLista) {
	
	char ask;
	bool arqExiste = verificaArqExiste(); // arquivos.c --> verificar se a base de registros existe no diretório atual
	
	if(arqExiste == false) {
		// Primeira execução --> nenhum registro
		
		printf("\n%s SISTEMA TOP RESTAURANTES %s\n\n", BAR, BAR);
		printf(" Desejas criar o arquivo 'restaurantes.txt' para executar o programa (s/n)? ");
		scanf(" %c", &ask);
		ask = toupper(ask);
		
		if(ask == 'S') {
			
			criarArquivo();	// arquivos.c --> criar arquivo caso não exista no diretório atual
			inicializarLista(lista, *tamLista); // lista.c --> iniciar com valores padrão para controlar posições vazias
			atualizarRegistros(lista, *tamLista); // arquivos.c --> carrega os dados já registrados na base
									
		} else {
			encerrar(0, lista, tamLista); // tarefas.c
		}	
			
	} 
	else {
		// Já foi executado --> é possível haver registros, bem como o usuário já ter redefinido o tamanho da lista
		
		*tamLista = tamBaseRegistros(); // arquivos.c --> obter tamanho atual da base de registros
		lista = realloc(lista, *tamLista * sizeof(Restaurante));
		inicializarLista(lista, *tamLista); // lista.c
		carregarDados(lista); // arquivos.c 
		
	}
	
	return lista;
	
}


/**************************************************************************************
*	Procedimento padrão para apresentar, ao usuário, o menu de tarefas.
*	ENTRADA: tamanho atual da lista e base de dados carregado no ponteiro *tamLista.
*************************************************************************************/
void displayInicio(int tamLista) {
	
	printf("\n%s SISTEMA TOP RESTAURANTES %s\n", BAR, BAR);
	printf("\n Número máximo de restaurantes a serem inscritos: %d\n\n", tamLista);
	printf(" [1] Inserir novo restaurante\n");
	printf(" [2] Deletar restaurante\n");
	printf(" [3] Listar todos os restaurantes\n");
	printf(" [4] Listar restaurantes por nota\n");
	printf(" [5] Listar restaurantes por tipo de comida\n");
	printf(" [6] Expandir número máximo de restaurantes\n");
	printf(" [0] Sair\n\n");
	printf(" Escolha a tarefa a ser realizada: ");
		
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-= LAÇO DE EXECUÇÃO PRINCIPAL -=-=-=-=-=--=-=-=-=-=-=-=-= */



void iniciar() {	
	
	int tamInicial = TAM_PADRAO; // auxiliar
	
	/* 
		* Iniciar ponteiro para o tamanho da lista com o tamanho padrão definido pelo programador 
		* Utilização de um ponteiro para exportá-lo a diferentes módulos para executar tarefas adequadamente.
	*/
	int *tamLista;	
	tamLista = &tamInicial;
	
	/* Alocar a lista com o tamanho inicial padrão, carregado pelo ponteiro *tamLista */
	Restaurante *lista;
	lista = (Restaurante*) malloc(*tamLista * sizeof(Restaurante));	// alocando vetor de restaurantes dinamicamente
	validarAlocLista(lista, tamLista); // tarefas.c --> verifica se foi possível alocar o espaço em memória necessário
	
	/* 
		* Interação inicial com o usuário caso a base de dados ainda não exista no diretório atual. 
		* Se já existir, a lista será realocada pela função e retornada ao vetor de restaurantes.		
	*/
	lista = usrCriarBase(lista, tamLista); 
	
	int posicao = posicaoVazia(lista, *tamLista); // índice da última posição vazia da lista para controle da execução de tarefas
	
	int token; // interação com o usuário (solicitação de tarefas)
	
	do {	
		
		displayInicio(*tamLista);
		scanf("%d%*c", &token);	
		
		switch(token) {
			
			case 0:
				encerrar(0, lista, tamLista);
				break;
				
			case 1: // Inserir
				
				if(posicao == *tamLista) {		
					msgListaCheia(); // uteis.c
				} 
				else {
					// primeira posição vazia
					posicao = inserir(lista, tamLista, posicao); // tarefas.c 
				}														
				break;
				
			case 2: // Deletar
				
				if(posicao == 0) {
					msgListaVazia(); // uteis.c
				}
				else {
					// primeira posição vazia
					posicao = deletar(lista, tamLista); // tarefas.c			
				}				
				break;
				
			case 3: // Listar todos
				
				if(posicao == 0) {
					msgListaVazia(); // uteis.c			
				}				
				else {
					listarTodos(lista, tamLista); // tarefas.c				
				}			
				break;			
			
			case 4: // Listar por nota atribuída à cozinha
				
				if(posicao == 0) {
					msgListaVazia(); // uteis.c	
				}
				else {
					listarPorNota(lista, tamLista); // tarefas.c
				}
				break;
			
			case 5: // Listar por tipo de comida
				
				if(posicao == 0) {
					msgListaVazia(); // uteis.c			
				}
				else {
					listarPorComida(lista, tamLista); // tarefas.c
				}
				break;
				
			case 6: // Realocar tamanho da lista
			
				if(*tamLista == LIMITE) {
					msgLimiteAtingido();
				} 
				else {
					// lista expandida
					lista = expandirLista(lista, tamLista); // tarefas.c		
				}			
				break;
						
			default:
				erroToken(); // uteis.c
				break;
			
		}
		
	} while(token != 0);	
	
}

