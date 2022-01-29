
#include "lista.c"
#include "uteis.c"
#include "restaurante.h"



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-= VARI�VEIS GLOBAIS DO M�DULO -=-=-=-=-=--=-=-=-=-=-=-=-=-*/



/******************************************************************
*	Strings globais utilizadas para formata��o dos dados nas 
*	tarefas de inser��o, listagem e dele��o.
*	Alocadas dinamicamente.
*	Casos especiais:
*		1. tipoAux --> utilizada, tamb�m, para validar busca
*		por tipo de comida solicitado na tarefa listarPorComida.
*		2. nomeAux --> utilizada, tamb�m, para confirmar a 
*		dele��o de um restaurante da lista e da base de registros.
******************************************************************/
char *nomeAux, *bairroAux, *cidadeAux, *tipoAux; 



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-== ENCERRAR PROGRAMA =-=-=--=-=-=--=-=-=-=-=-=-=-=-=*/



/****************************************************************************************
*	Procedimento padr�o caso o usu�rio solicite encerrar o programa ou ocorra um erro.
*	ENTRADA: c�digo do evento que informa se o programa foi encerrado de acordo 
*	com as escolhas do usu�rio (0) ou (1) em caso de erro durante o la�o de execu��o.
*	Al�m disso, o vetor de restaurantes e o ponteiro para o seu tamanho para liberar a 
*	mem�ria, alocada dinamicamente, para eles.
****************************************************************************************/
void encerrar(int evento, Restaurante *lista, int *tamLista) {
	
	// Intera��o com o usu�rio
	
	system("cls");
	printf("\n Programa encerrado...\n\n");
	printf("%s%s", BAR, BAR);
	Sleep(WAIT);
	
	if(evento != 1) {
		// execu��o normal
		system("cls");
		printf("\n Obrigado por utilizar o programa!\n");
		
	} 
	else {
		// ocorr�ncia de uma exce��o
		system("cls");
		printf("\n Tente reiniciar o programa...");		
	}
	
	// Liberando a mem�ria ocupada pelo vetor de restaurantes e o ponteiro para o seu tamanho ap�s encerrar o programa.
	free(lista);
	lista = NULL;	
	
	free(tamLista);
	tamLista = NULL;
	
	exit(evento);
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-== ALOCA��O DIN�MICA =-=-=--=-=-=--=-=-=-=-=-=-=-=-=*/



/*******************************************************************************
*	Procedimento padr�o para validar a aloca��o din�mica de mem�ria para as 
*	vari�veis globais.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho para serem 
*	desalocados em caso de erro. Al�m disso, a string a ser validada.
*******************************************************************************/
void validarAlocString(Restaurante *lista, int *tamLista, char *string) {
	
	if(string == NULL) {
		msgErroAloc(); // uteis.c
		encerrar(1, lista, tamLista);
	}
		
}


/*******************************************************************************
*	Procedimento padr�o para validar a aloca��o din�mica de mem�ria para o vetor 
*	de restaurantes *lista.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho para serem 
*	desalocados em caso de erro. 
*******************************************************************************/
void validarAlocLista(Restaurante *lista, int *tamLista) {
	
	if(lista == NULL) {
		msgErroAloc(); // uteis.c
		encerrar(1, lista, tamLista);
	}	
	
}


/********************************************************************
*	Procedimento padr�o para liberar mem�ria alocada para as 
*	vari�veis globais utilizadas nas tarefas de inser��o, listagem 
*	e dele��o.
********************************************************************/
void liberarAux() {
	
	free(nomeAux);
	nomeAux = NULL;			
				
	free(bairroAux);
	bairroAux = NULL;	
		
	free(cidadeAux);
	cidadeAux = NULL;
		
	free(tipoAux);
	tipoAux = NULL;	
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- APRESENTA��O DE DADOS =--=-=-=--=-=-=-=-=-=-=-=-=*/



/***************************************************************************
*	Procedimento para imprimir os dados, de apenas um restaurante, durante
*	a leitura da lista realizada no procedimento "apresentarDados()".
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual para serem 
*	desalocados em caso de erro. Al�m disso, restaurante obtido da lista e a 
*	vari�vel booleana de controle "listagem" para variar a sa�da de acordo com a 
*	tarefa em execu��o:
*
*	1. listagem = true: a chamada foi realizada em uma das tarefas
*	de listagem: listarTodos(), listarPorNota(), listarPorComida().
*	Portanto, todos os dados do restaurante ser�o apresentados.
*
*	2. listagem = false: a chamada foi realizada na tarefa deletar.
*	Portanto, apenas o ID e o nome do restaurante ser�o apresentados.		
***************************************************************************/
void displayDados(Restaurante *lista, int *tamLista, Restaurante restaurante, bool listagem) {
	
	/* 
	*	Strings globais auxiliares utilizadas para formatar os dados para apresent�-los 	
	*	*nomeAux --> utilizada quando a tarefa for listarTodos ou deletar
	*	*bairroAux, *cidadeAux, *tipoAux; --> somente ser�o utilizadas caso a tarefa seja de listagem
	*/
	nomeAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, nomeAux);
		 
	bairroAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, bairroAux);
	
	cidadeAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, cidadeAux);
	
	tipoAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, tipoAux);
		
	strcpy(nomeAux, restaurante.nome); // copia o nome do restaurante obtido
	formatarSaida(nomeAux); // strings.c --> apresentar os dados devidamente
				
	/* Apresentar o m�nimo - independente da tarefa sendo executada */
	printf("%s\n ID: %d\n", DIV, restaurante.id);
	printf(" Nome: %s\n%s\n", nomeAux, DIV);
	
	if(listagem) {
		
		strcpy(bairroAux, restaurante.bairro);	
		formatarSaida(bairroAux);
					
		strcpy(cidadeAux, restaurante.cidade);	
		formatarSaida(cidadeAux);
				
		strcpy(tipoAux, restaurante.tipoComida);	
		formatarSaida(tipoAux);		
						
		printf(" Bairro: %s\n", bairroAux);
		printf(" Cidade: %s\n", cidadeAux);
		printf(" Tipo de comida: %s\n", tipoAux);
		printf(" Nota (de 0 a 5): %d\n%s\n\n", restaurante.nota, DIV);	
		
	}
	
	// Liberando mem�ria ocupada pelas vari�veis globais ap�s encerrar a tarefa.
	liberarAux();	
	
} 


/***************************************************************************************************************
*	Procedimento padr�o para apresentar dados nas tarefas de listagem e de dele��o.
*	ENTRADA: 
*	- lista de restaurantes e o ponteiro do seu tamanho atual para serem desalocados em caso de erro.
*	- O c�digo correspondente � tarefa em execu��o para realizar busca na lista:	
*		0 = listarTodos --> todos os dados de todos os restaurantes
*		1 = listarPorNota --> todos os dados dos restaurantes com nota superior � solicitada pelo usu�rio
*		2 = listarPorComida --> todos os dados dos restaurantes com o tipo de comida solicitado pelo usu�rio
*		3 = deletar --> apenas o ID e o nome de todos os restaurantes 
*	- a nota informada pelo usu�rio caso a tarefa seja listarPorNota
*	- o tipo de comida informado pelo usu�rio caso a tarefa seja listarPorComida
***************************************************************************************************************/
void apresentarDados(Restaurante *lista, int *tamLista, int codigoTarefa, int nota, char *tipoComida) {

	printf("\n"); 

	// Percorrer toda a lista
	for(int i = 0; i < *tamLista; i++) {
		
		switch(codigoTarefa) {
			
			case 0:	// listarTodos --> listagem --> true		
				if(lista[i].id != POS_VAZIA) {
					displayDados(lista, tamLista, lista[i], true);						
				}											
			break;
			
			case 1: // listarPorNota --> listagem --> true	
				if(lista[i].nota > nota) {	
					displayDados(lista, tamLista, lista[i], true);
				}							
			break;
			
			case 2: // listarPorComida --> listagem --> true
				if((strcmp(lista[i].tipoComida, tipoComida)) == 0) {			
					displayDados(lista, tamLista, lista[i], true);
				}
			break;
			
			case 3: // deletar --> listagem --> false				
				if(lista[i].id != POS_VAZIA) {
					displayDados(lista, tamLista, lista[i], false);
				}
			break;
			
		}
			
	}		
	
	printf("\n\n%s%s%s", BAR, BAR, BAR);
	
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= TAREFAS DO SISTEMA -==--=-=-=--=-=-=-=-=-=-=-=-=*/



/* -=-=-=-=-=-=-=-=-=-=-=-=-= LISTAGEM -=-=-=-=-=-=-=-=-=-=-=-=-= */



/*********************************************************************
*	Lista todos os restaurantes da lista obtidos da base de dados.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual.
*	# c�digo associado � apresentarDados() = 0
*********************************************************************/
void listarTodos(Restaurante *lista, int *tamLista) {	

	int codigo = 0;
	
	system("cls");
	printf("\n%s LISTAR RESTAURANTES %s\n\n", BAR, BAR);
	
	apresentarDados(lista, tamLista, codigo, 0/*filtro 1*/, ""/*filtro 2*/); 

	esperarSaida(); // uteis.c
	
}


/*********************************************************************
*	Lista todos os restaurantes com nota superior � nota-filtro
*	informada pelo usu�rio.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual.
*	# c�digo associado � apresentarDados() = 1
*********************************************************************/	
void listarPorNota(Restaurante *lista, int *tamLista) {
	
	int codigo = 1;
	
	bool notaSuperior; // verifica se existe restaurante com nota superior ao filtro 1
	int nota;
		
	system("cls");
	printf("\n%s LISTAR RESTAURANTES POR NOTA %s\n\n", BAR, BAR);
	
	printf(" Nota (de 0 e 4) para listar restaurantes com nota superior a ela: ");
	scanf("%d%*c", &nota);	
	
	// Validar nota-filtro digitada.
	while(nota < 0 || nota >= 5) {
		printf("\n Valor da nota digitado incorretamente...\n");
		printf(" Digite a nota (de 0 a 4) novamente: ");
		scanf("%d%*c", &nota);
	}
	
	notaSuperior = verificaNota(lista, *tamLista, nota); // lista.c
	
	if(notaSuperior) {
		apresentarDados(lista, tamLista, codigo, nota/*filtro 1*/, ""/*filtro 2*/);		
		esperarSaida();	// uteis.c
	} 	
	else {
		printf("\n Nenhum restaurante encontrado com nota superior a informada!");
		Sleep(WAIT);
		system("cls");
	}		
			
}


/**********************************************************************
*	Lista todos os restaurantes com base no tipo de comida solicitado 
*	pelo usu�rio.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual.
*	# c�digo associado � apresentarDados() = 2
**********************************************************************/	
void listarPorComida(Restaurante *lista, int *tamLista) {	

	int codigo = 2;

	bool tipoExiste; // verifica se existe restaurante com o tipo de comida informado pelo usu�rio (filtro 2)
	
	tipoAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, tipoAux);
			
	system("cls");
	printf("\n%s LISTAR RESTAURANTES POR TIPO DE COMIDA %s\n\n", BAR, BAR);
	
	printf(" Tipo de comida para listar restaurantes que o oferecem (ex.: francesa): ");
	scanf("%s", tipoAux);	
	
	tipoExiste = verificaExisteTipo(lista, *tamLista, tipoAux); // lista.c
	
	if(tipoExiste) {
		printf("\n Restaurantes com o tipo de comida: %s\n", tipoAux);	
		apresentarDados(lista, tamLista, codigo, 0/*filtro 1*/, tipoAux/*filtro 2*/);
		esperarSaida(); //uteis.c
	} 	
	else {
		printf("\n Nenhum restaurante oferencedo o tipo de comida solicitado!");
		Sleep(WAIT);
		system("cls");
	}		
	
	// Liberando mem�ria alocada para vari�vel global auxiliar tipoAux ap�s encerrar tarefa
	free(tipoAux);
	tipoAux = NULL;
			
}



/* -=-=-=-=-=-=-=-=-=-=-=-=-= INSER��O -=-=-=-=-=-=-=-=-=-=-=-=-= */



/*******************************************************************************
*	Insere um novo restaurante na lista de restaurantes no �ndice "posicao".
*	ENTRADA: lista de restaurantes, o ponteiro do seu tamanho atual e o �ndice 
*	em que o restaurante a ser inserido dever� ser armazenado na lista.
*	RETORNO: primeira posi��o vazia do vetor de restaurantes *lista.
******************************************************************************/
int inserir(Restaurante *lista, int *tamLista, int posicao) {
	
	/* 
	*	Vari�veis globais utilizadas para formatar os dados a serem registrados. 		
	*	*nomeAux,*bairroAux, *cidadeAux, *tipoAux.
	*/
	nomeAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, nomeAux);
		
	bairroAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, bairroAux);
	
	cidadeAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, cidadeAux);
	
	tipoAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, tipoAux);
		
	Restaurante restaurante; // restaurante a ser registrado
	
	int id; // para garantir ID �nico
	int nota;	
	bool restExiste; // validar se o restaurante a ser inserido j� existe (busca baseada no nome)
	
	system("cls");
	printf("\n%s INSERIR NOVO RESTAURANTE %s\n\n", BAR, BAR);
	
	printf(" Nome do restaurante: ");
	scanf("%[^\n]%*c", nomeAux);		
	formatarDadoRegistro(nomeAux); // strings.c
	
	restExiste = verificaExisteNome(lista, *tamLista, nomeAux); // lista.c
	
	if(restExiste) {		
		
		printf("\n Este restaurante j� est� na lista!");	
		Sleep(WAIT);
		cancelarTarefa(); // uteis.c
		
	} 
	
	else{
				
		lista[posicao].id = posicao;		
		strcpy(lista[posicao].nome, nomeAux);	
		
		printf(" Bairro: ");
		scanf("%[^\n]%*c", bairroAux);
		formatarDadoRegistro(bairroAux); // strings.c
		strcpy(lista[posicao].bairro, bairroAux);	
	
		printf(" Cidade: ");
		scanf("%[^\n]%*c", cidadeAux);
		formatarDadoRegistro(cidadeAux); // strings.c
		strcpy(lista[posicao].cidade, cidadeAux);	
	
		printf(" Tipo de comida (ex.: italiana): ");
		scanf("%[^\n]%*c", tipoAux);		
		formatarDadoRegistro(tipoAux); // strings.c
		strcpy(lista[posicao].tipoComida, tipoAux);		
		
		printf(" Nota para a cozinha (de 0 a 5): ");
		scanf("%d%*c", &nota);	
		
		// Validar nota digitada.
		while(nota < 0 || nota > 5) {
			printf("\n Valor da nota digitado incorretamente...\n");
			printf(" Digite a nota (de 0 a 5) novamente: ");
			scanf("%d%*c", &nota);
		}
	
		lista[posicao].nota = nota;		
		
		atualizarRegistros(lista, *tamLista); // arquivos.c --> inscrever restaurante na base de registros
		
		posicao = posicaoVazia(lista, *tamLista); // lista.c --> retorno da tarefa (primeira posi��o vazia na lista)
		
		ordenarLista(lista, *tamLista); // lista.c --> manter lista ordenada
		
		// Mensagem de conclus�o de tarefa 
		msgSucesso();

		// Liberando mem�ria ocupada pelas strings globais ap�s encerrar a tarefa.	
        liberarAux();
				
	}	
	
	return posicao;
				
}



/* -=-=-=-=-=-=-=-=-=-=-=-=-= DELE��O -=-=-=-=-=-=-=-=-=-=-=-=-= */



/***********************************************************************************
*	Procedimento padr�o para deletar restaurante da lista, a partir	do seu ID, caso 
*	o usu�rio confirme a dele��o.
*	Primeiramente, zera o restaurante com o ID digitado pelo usu�rio. Ap�s isso, 
*	reorganiza a lista de modo a colocar todas as posi��es vazias ao fim. Por fim, 
*	escreve a lista de restaurantes na base de registros.
*	ENTRADA: lista de restaurantes, seu tamanho e o ID digitado na tarefa deletar.
***********************************************************************************/
void deletarRestaurante(Restaurante *lista, int tamLista, int id) {
	
	removerDaLista(lista, tamLista, id); // lista.c
	ordenarLista(lista, tamLista); // lista.c
	atualizarRegistros(lista, tamLista); // arquivos.c 
		
}


/***************************************************************************
*	Apresenta os IDs e nomes dos restaurantes registrados ao usu�rio e 
*	solicita o ID daquele que deseja remover da lista e da base de dados.
*	Ap�s isso, solicita confirma��o para deletar o restaurante.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual. 
*	RETORNO: primeira posi��o vazia do vetor de restaurantes *lista.
*	# c�digo associado � apresentarDados() = 3
****************************************************************************/
int deletar(Restaurante *lista, int *tamLista) {
	
	int posicao;
	
	char *nomeAux;
	nomeAux = (char*) malloc(TAM_STRING * sizeof(char)); // aloca vari�vel global
	validarAlocString(lista, tamLista, nomeAux);
	
	int codigo = 3;
	
	bool restExiste; // busca baseada no ID do restaurante
	int idDeletar;
	
	char confirmar; // intera��o com o usu�rio (confirmar dele��o)
	
	system("cls");
	printf("\n%s DELETAR RESTAURANTE %s\n\n", BAR, BAR);
	
	apresentarDados(lista, tamLista, codigo, 0/*filtro 1*/, ""/*filtro 2*/);
	
	printf("\n\n ID do restaurante que desejas deletar: ");
	scanf("%d%*c", &idDeletar);
	
	restExiste = verificaExisteId(lista, *tamLista, idDeletar, nomeAux); // nome ser� copiado para nomeAux caso exista.

	if(restExiste) {
		
		printf("\n Tens certeza que desejas deletar o restaurante %s da lista (s/n)? ", nomeAux);
		
		// Liberando mem�ria ocupada pela string global nomeAux 
		free(nomeAux);
		nomeAux = NULL;
		
		scanf("%c%*c", &confirmar);
			
		confirmar = toupper(confirmar);	// evitar case-sensitivity.
			
		switch(confirmar) {
			
			case 'S':
				deletarRestaurante(lista, *tamLista, idDeletar);	
				posicao = posicaoVazia(lista, *tamLista); // lista.c --> retorno da tarefa (primeira posi��o vazia na lista)
				msgSucesso(); // uteis.c
				break;		
		 
			case 'N':
				cancelarTarefa(); // uteis.c
				break;
		
			default:
				printf("\n Tarefa confirmada incorretamente!");
				Sleep(WAIT);		
				cancelarTarefa(); // uteis.c
				break;
				
		}
						
	}	
	
	else {	
	
		printf("\n Restaurante com o ID informado inexistente!");
		Sleep(WAIT);
		cancelarTarefa();		
		
 	}	 	

	return posicao;
	
}



/* -=-=-=-=-=-=-=-=-=-=-=-=-= EXPANS�O -=-=-=-=-=-=-=-=-=-=-=-=-= */



/****************************************************************************
*	Copia os dados da lista antiga para a nova alocada com o limite de 
*	registros redefinido pelo usu�rio na tarefa realocarLista().
*	ENTRADA: a nova lista de restaurantes (destino), a lista antiga (fonte)
*	e o novo tamanho da lista (limite).
*****************************************************************************/
void copiarLista(Restaurante *novaLista, Restaurante *lista, int tamLista) {
	
	for(int i = 0; i < tamLista; i++) {
		
		novaLista[i].id = lista[i].id;
		strcpy(novaLista[i].nome, lista[i].nome);		
		strcpy(novaLista[i].bairro, lista[i].bairro);	
		strcpy(novaLista[i].cidade, lista[i].cidade);	
		strcpy(novaLista[i].tipoComida, lista[i].tipoComida);	
		novaLista[i].nota = lista[i].nota;
			
	}	
	
}


/*******************************************************************************
*	Inicializa apenas as posi��es novas, com os valores padr�o, ap�s o usu�rio 
*	solicitar a expans�o da lista de restaurantes na tarefa realocarLista(). 
*	Optei por n�o escrever este procedimento no m�dulo lista.c para manter a 
*	legibilidade da tarefa realocarLista().
*	ENTRADA: nova lista de restaurantes, o tamanho da lista antiga e o da nova.
*******************************************************************************/
void atualizarLista(Restaurante *lista, int tamLista, int novoTam) {
	
		
	int novasPosicoes = novoTam - tamLista;
	int posicao;
	
	for(int i = 0; i < novasPosicoes; i++) {
		
		posicao = tamLista + i;
		
		zerarPosicao(lista, posicao);
		
	}	
	
}


/**************************************************************************
*	Solicita o limite de registros que o usu�rio deseja que a lista de 
*	restaurantes e a base de dados tenham. Se o valor digitado for menor ou 
*	igual ao limite atual ou maior que o limite m�ximo, definido pelo 
*	programador, a tarefa � cancelada.
*	ENTRADA: lista de restaurantes e o ponteiro do seu tamanho atual.
*	RETORNO: nova lista de restaurantes com o novo limite solicitado 
*	carregada com os dados j� registrados anteriormente.
**************************************************************************/
Restaurante *expandirLista(Restaurante *lista, int *tamLista) {
	
	Restaurante *novaLista;
	int novoTam;
	
	system("cls");
	printf("\n%s EXPANDIR LISTA %s\n", BAR, BAR);
	
	printf("\n Limite atual de restaurantes a serem inscritos: %d\n\n", *tamLista);
	
	printf(" => Digite o novo limite (at� %d restaurantes): ", LIMITE);
	scanf("%d%*c", &novoTam);
	
	if(novoTam < *tamLista) {
		
		printf("\n Imposs�vel realizar tarefa!\n");
		printf(" O limite digitado � menor do que o atual...");
		Sleep(WAIT);
		cancelarTarefa();		
		
	} 
	else if(novoTam == *tamLista){
		
		printf("\n Imposs�vel realizar tarefa!\n");
		printf(" O limite atual � igual ao digitado...");
		Sleep(WAIT);
		cancelarTarefa();	
			
	}
	else if(novoTam > LIMITE) {
		
		printf("\n Imposs�vel realizar tarefa!\n");
		printf(" O limite de expans�o m�xima � de %d restaurantes...", LIMITE);
		Sleep(WAIT);
		cancelarTarefa();
		
	}
	else {		
	
		novaLista = (Restaurante*) malloc(novoTam * sizeof(Restaurante)); // aloca o novo vetor de restaurantes
		validarAlocLista(novaLista, tamLista); // verifica se foi poss�vel alocar a nova lista (espa�o em mem�ria suficiente)
		
		copiarLista(novaLista, lista, novoTam); // copia os dados da lista antiga para a nova
		
		// Libera a mem�ria alocada para a lista antiga
		free(lista);
		lista = NULL;
		
		atualizarLista(novaLista, *tamLista, novoTam); // inicializa as novas posi��es da lista
		atualizarRegistros(novaLista, novoTam); // arquivos.c --> registra as novas posi��es na base de dados
	
		msgSucesso(); // uteis.c
	
		*tamLista = novoTam; // redefine o valor do ponteiro do tamanho da lista
		
		return novaLista;
		
	}	
						
}

