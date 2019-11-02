#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct lista {			// estrutura lista para implementação da lista de processos
	int id; 			//id do processo | a ideia é que seja gerado em sequencia (processo 1 = 1, processo 2 = 2 ...)
	int tipo; 			//tipo do processo 1 = CPU Bound | 2 = IO Bound (definidos aleatóriamente com rand())
	int te;				//tempo de execução do processo, será um valor aleatório (de preferencia de 1 a 10 no máximo)
	int estado;			// 1 = bloqueado 2 = pronto 3 = executando | todos começam como prontos (ou seja, valor 2)
	struct lista* prox; //ponteiro para o proximo item da lista
};

struct fila {
	Lista* ini;	// ponteiro para o nó do início da fila
	Lista* fim;	// ponteiro para o nó do fim da fila
};

//typedef struct lista Lista;
//typedef struct fila Fila;

Fila* fila_cria(void) {						// cria uma fila, alocando memória para ela
	Fila* f = (Fila*) malloc(sizeof(Fila));	// aloca memória do tamanho de uma fila
	f->ini = f->fim = NULL;					// inicializa os dois ponteiros (ini e fim) como nulos, pois a fila está vazia
	return f;								// retorna o ponteiro que aponta para o endereço alocado
}

void fila_insere_processo(Fila* f, int id, int tipo, int te) {	// insere um processo (nó) no fim da fila 
	Lista* n = (Lista*) malloc(sizeof(Lista));					// aloca memória para o novo nó
	n->id = id;													//adiciona o id do processo
	n->tipo = tipo;												//adiciona o tipo, CPU Bound ou IO Bound
	n->te = te;													//define um tempo de execução do processo
	n->estado = 2;												//todos os processos começam com valor 2
	n->prox = NULL;												// faz o próximo do nó ser nulo, pois será o último
	if(f->fim != NULL)											// verifica se a fila não está vazia...
		f->fim->prox = n;										// se não estiver, apenas faz o atual nó do fim apontar para o novo nó criado
	else														// caso contrário...
		f->ini = n;												// já que a fila está vazia, o novo nó será tanto o último como o primeiro. Então, é preciso atualizar "ini" também
	f->fim = n;													// faz o ponteiro "fim" apontar para o novo nó, já que ele será mesmo o último da fila
}

int fila_vazia(Fila* f) {		// verifica se a fila está vazia ou não
	return (f->ini == NULL);	// retorna o resultado (0 ou 1) da operação lógica de igualdade entre o ponteiro "ini" e NULL (se for NULL, a fila está vazia: retorna 1)
}


/* função fila retira vai ser útil para finalizar os processos
// depois que todo o seu tempo de execução for utilizado, retorna o id 
*/

int fila_retira(Fila* f) {			// remove o primeiro elemento da fila (FIFO)
	Lista* t;						// ponteiro auxiliar para guardar o nó que vai ser removido
	int v;
	if(fila_vazia(f)) {				// verifica se a fila está vazia. Se estiver...
		printf("Fila vazia!\n");	// imprime mensagem de fila vazia
		exit(1);					// e encerra o programa
	}								// se não estiver, continua a função
	t = f->ini;						// guarda temporariamente o endereço do primeiro nó
	v = t->id;						// guarda temporariamente o id do primeiro nó
	f->ini = t->prox;				// atualiza ponteiro "ini" para o próximo elemento da fila
	if(f->ini == NULL)				// se a fila tiver ficado vazia após a remoção...
		f->fim = NULL;				// atualiza também o ponteiro do fim para NULL
	free(t);						// libera o endereço do nó removido
	return v;						// retorna o valor do nó removido (id)
}

/* função que imprime os processos também
// pode ser usada para verificação dos dados
// dos processos que estão na fila
*/

void fila_imprime_processos(Fila* f){
	Lista* t; 																								//variavel auxiliar para ler os nós

	if(fila_vazia(f)){																						//se a fila estiver vazia, interrompe o programa
		printf("Fila vazia!\n");
		exit(1);
	}
	
	t = f->ini; 																							//lista t guarda o primeiro nó da fila
	while(t!=NULL){
		Lista* m = t->prox; 																				//guarda o nó seguinte de t
		printf("id: %d | tipo: %d | tempo de execucao: %d, estado: %d\n", t->id, t->tipo,t->te,t->estado);	//imprime tudo em t
		t = m; 																								//faz o t ser o próximo nó para continuar o laço
	}
}

void fila_libera(Fila* f) {		// libera a memória alocada para a fila
	Lista* q = f->ini;			// ponteiro auxiliar para começar a percorrer a lista da fila desde o início
	while(q != NULL) {			// laço para percorrer a lista da fila
		Lista* t = q->prox;			// guarda o endereço do próximo nó para que o atual seja liberado sem perder a lista
		free(q);					// libera o nó atual
		q = t;						// aponta para o próximo nó (que estava guardado em "t")
	}
	free(f);					// libera, por fim, o ponteiro da fila inteira
}
