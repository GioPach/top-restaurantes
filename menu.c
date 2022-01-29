
#include "tarefas.c" 
#include "restaurante.h" 



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* =-=-= PROCEDIMENTO DE CRIA��O DA LISTA E BASE DE DADOS (SISTEMA-USU�RIO) -=-=-= */



/**********************************************************************************************
*	Solicita, ao usu�rio, confirma��o para criar o arquivo "restaurantes.txt"
*	caso n�o exista no diret�rio atual. Ap�s isso, inicializa a lista com os
*	valores padr�o e os registra na base de dados. Caso recuse, o programa � encerrado.
*	Se o arquivo "restaurantes.txt" j� existir, o n�mero de registros efetuados nele 
*	ser� calculado para uma poss�vel realoca��o do tamanho do vetor de restaurantes, pois
*	o usu�rio pode ter expandido em uma execu��o anterior. Ap�s isso, inicializa a lista 
*	com os valores padr�o e carrega os dados da base nela.
*	ENTRADA: vetor de restaurantes *lista alocado inicialmente com o tamanho
*	padr�o, definido pelo programador. Al�m disso, o ponteiro que carrega o tamanho da lista
*	para ser passado �s chamadas de tarefa no la�o de execu��o em iniciar().
*	RETORNO: retorna a lista devidamente alocada e possivelmente j� carregada de registros.
**********************************************************************************************/
Restaurante *usrCriarBase(Restaurante *lista, int *tamLista) {
	
	char ask;
	bool arqExiste = verificaArqExiste(); // arquivos.c --> verificar se a base de registros existe no diret�rio atual
	
	if(arqExiste == false) {
		// Primeira execu��o --> nenhum registro
		
		printf("\n%s SISTEMA TOP RESTAURANTES %s\n\n", BAR, BAR);
		printf(" Desejas criar o arquivo 'restaurantes.txt' para executar o programa (s/n)? ");
		scanf(" %c", &ask);
		ask = toupper(ask);
		
		if(ask == 'S') {
			
			criarArquivo();	// arquivos.c --> criar arquivo caso n�o exista no diret�rio atual
			inicializarLista(lista, *tamLista); // lista.c --> iniciar com valores padr�o para controlar posi��es vazias
			atualizarRegistros(lista, *tamLista); // arquivos.c --> carrega os dados j� registrados na base
									
		} else {
			encerrar(0, lista, tamLista); // tarefas.c
		}	
			
	} 
	else {
		// J� foi executado --> � poss�vel haver registros, bem como o usu�rio j� ter redefinido o tamanho da lista
		
		*tamLista = tamBaseRegistros(); // arquivos.c --> obter tamanho atual da base de registros
		lista = realloc(lista, *tamLista * sizeof(Restaurante));
		inicializarLista(lista, *tamLista); // lista.c
		carregarDados(lista); // arquivos.c 
		
	}
	
	return lista;
	
}


/**************************************************************************************
*	Procedimento padr�o para apresentar, ao usu�rio, o menu de tarefas.
*	ENTRADA: tamanho atual da lista e base de dados carregado no ponteiro *tamLista.
*************************************************************************************/
void displayInicio(int tamLista) {
	
	printf("\n%s SISTEMA TOP RESTAURANTES %s\n", BAR, BAR);
	printf("\n N�mero m�ximo de restaurantes a serem inscritos: %d\n\n", tamLista);
	printf(" [1] Inserir novo restaurante\n");
	printf(" [2] Deletar restaurante\n");
	printf(" [3] Listar todos os restaurantes\n");
	printf(" [4] Listar restaurantes por nota\n");
	printf(" [5] Listar restaurantes por tipo de comida\n");
	printf(" [6] Expandir n�mero m�ximo de restaurantes\n");
	printf(" [0] Sair\n\n");
	printf(" Escolha a tarefa a ser realizada: ");
		
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* -=-=-=-=-=-=-=-=-=-=-=-= LA�O DE EXECU��O PRINCIPAL -=-=-=-=-=--=-=-=-=-=-=-=-= */



void iniciar() {	
	
	int tamInicial = TAM_PADRAO; // auxiliar
	
	/* 
		* Iniciar ponteiro para o tamanho da lista com o tamanho padr�o definido pelo programador 
		* Utiliza��o de um ponteiro para export�-lo a diferentes m�dulos para executar tarefas adequadamente.
	*/
	int *tamLista;	
	tamLista = &tamInicial;
	
	/* Alocar a lista com o tamanho inicial padr�o, carregado pelo ponteiro *tamLista */
	Restaurante *lista;
	lista = (Restaurante*) malloc(*tamLista * sizeof(Restaurante));	// alocando vetor de restaurantes dinamicamente
	validarAlocLista(lista, tamLista); // tarefas.c --> verifica se foi poss�vel alocar o espa�o em mem�ria necess�rio
	
	/* 
		* Intera��o inicial com o usu�rio caso a base de dados ainda n�o exista no diret�rio atual. 
		* Se j� existir, a lista ser� realocada pela fun��o e retornada ao vetor de restaurantes.		
	*/
	lista = usrCriarBase(lista, tamLista); 
	
	int posicao = posicaoVazia(lista, *tamLista); // �ndice da �ltima posi��o vazia da lista para controle da execu��o de tarefas
	
	int token; // intera��o com o usu�rio (solicita��o de tarefas)
	
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
					// primeira posi��o vazia
					posicao = inserir(lista, tamLista, posicao); // tarefas.c 
				}														
				break;
				
			case 2: // Deletar
				
				if(posicao == 0) {
					msgListaVazia(); // uteis.c
				}
				else {
					// primeira posi��o vazia
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
			
			case 4: // Listar por nota atribu�da � cozinha
				
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

