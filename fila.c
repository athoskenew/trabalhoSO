#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct lista {			// estrutura lista para implementa��o da lista de processos
	int id; 			//id do processo | a ideia � que seja gerado em sequencia (processo 1 = 1, processo 2 = 2 ...)
	int tipo; 			//tipo do processo 1 = CPU Bound | 2 = IO Bound (definidos aleat�riamente com rand())
	int te;				//tempo de execu��o do processo, ser� um valor aleat�rio (de preferencia de 1 a 10 no m�ximo)
	int estado;			// 1 = bloqueado 2 = pronto 3 = executando | todos come�am como prontos (ou seja, valor 2)
	struct lista* prox; //ponteiro para o proximo item da lista
};

struct fila {
	Lista* ini;	// ponteiro para o n� do in�cio da fila
	Lista* fim;	// ponteiro para o n� do fim da fila
};

//typedef struct lista Lista;
//typedef struct fila Fila;

Fila* fila_cria(void) {						// cria uma fila, alocando mem�ria para ela
	Fila* f = (Fila*) malloc(sizeof(Fila));	// aloca mem�ria do tamanho de uma fila
	f->ini = f->fim = NULL;					// inicializa os dois ponteiros (ini e fim) como nulos, pois a fila est� vazia
	return f;								// retorna o ponteiro que aponta para o endere�o alocado
}

void fila_insere_processo(Fila* f, int id, int tipo, int te) {	// insere um processo (n�) no fim da fila 
	Lista* n = (Lista*) malloc(sizeof(Lista));					// aloca mem�ria para o novo n�
	n->id = id;													//adiciona o id do processo
	n->tipo = tipo;												//adiciona o tipo, CPU Bound ou IO Bound
	n->te = te;													//define um tempo de execu��o do processo
	n->estado = 2;												//todos os processos come�am com valor 2
	n->prox = NULL;												// faz o pr�ximo do n� ser nulo, pois ser� o �ltimo
	if(f->fim != NULL)											// verifica se a fila n�o est� vazia...
		f->fim->prox = n;										// se n�o estiver, apenas faz o atual n� do fim apontar para o novo n� criado
	else														// caso contr�rio...
		f->ini = n;												// j� que a fila est� vazia, o novo n� ser� tanto o �ltimo como o primeiro. Ent�o, � preciso atualizar "ini" tamb�m
	f->fim = n;													// faz o ponteiro "fim" apontar para o novo n�, j� que ele ser� mesmo o �ltimo da fila
}

int fila_vazia(Fila* f) {		// verifica se a fila est� vazia ou n�o
	return (f->ini == NULL);	// retorna o resultado (0 ou 1) da opera��o l�gica de igualdade entre o ponteiro "ini" e NULL (se for NULL, a fila est� vazia: retorna 1)
}


/* fun��o fila retira vai ser �til para finalizar os processos
// depois que todo o seu tempo de execu��o for utilizado, retorna o id 
*/

int fila_retira(Fila* f) {			// remove o primeiro elemento da fila (FIFO)
	Lista* t;						// ponteiro auxiliar para guardar o n� que vai ser removido
	int v;
	if(fila_vazia(f)) {				// verifica se a fila est� vazia. Se estiver...
		printf("Fila vazia!\n");	// imprime mensagem de fila vazia
		exit(1);					// e encerra o programa
	}								// se n�o estiver, continua a fun��o
	t = f->ini;						// guarda temporariamente o endere�o do primeiro n�
	v = t->id;						// guarda temporariamente o id do primeiro n�
	f->ini = t->prox;				// atualiza ponteiro "ini" para o pr�ximo elemento da fila
	if(f->ini == NULL)				// se a fila tiver ficado vazia ap�s a remo��o...
		f->fim = NULL;				// atualiza tamb�m o ponteiro do fim para NULL
	free(t);						// libera o endere�o do n� removido
	return v;						// retorna o valor do n� removido (id)
}

/* fun��o que imprime os processos tamb�m
// pode ser usada para verifica��o dos dados
// dos processos que est�o na fila
*/

void fila_imprime_processos(Fila* f){
	Lista* t; 																								//variavel auxiliar para ler os n�s

	if(fila_vazia(f)){																						//se a fila estiver vazia, interrompe o programa
		printf("Fila vazia!\n");
		exit(1);
	}
	
	t = f->ini; 																							//lista t guarda o primeiro n� da fila
	while(t!=NULL){
		Lista* m = t->prox; 																				//guarda o n� seguinte de t
		printf("id: %d | tipo: %d | tempo de execucao: %d, estado: %d\n", t->id, t->tipo,t->te,t->estado);	//imprime tudo em t
		t = m; 																								//faz o t ser o pr�ximo n� para continuar o la�o
	}
}

void fila_libera(Fila* f) {		// libera a mem�ria alocada para a fila
	Lista* q = f->ini;			// ponteiro auxiliar para come�ar a percorrer a lista da fila desde o in�cio
	while(q != NULL) {			// la�o para percorrer a lista da fila
		Lista* t = q->prox;			// guarda o endere�o do pr�ximo n� para que o atual seja liberado sem perder a lista
		free(q);					// libera o n� atual
		q = t;						// aponta para o pr�ximo n� (que estava guardado em "t")
	}
	free(f);					// libera, por fim, o ponteiro da fila inteira
}
