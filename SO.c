#include <stdio.h>
#include <stdlib.h>
#include "fila.c"
#define QUANTUM 2
// assinaturas das funções
void gerar_processos(Fila* f,int quantidade);
void executar_processos(Fila*f);

int main (void){
	
	Fila* f = fila_cria(); //cria a fila de processos vazia
	Fila* finalizados = fila_cria(); //fila onde processo finalizados ficarão
	srand(time(NULL)); //alimentando rand()
	gerar_processos(f,20); //gerando 20 processos
	
	
	
	
	fila_imprime_processos(f); //imprimindo os processos da fila
	executar_processos(f);
	return 0;
}


/* essa função irá gerar processos aleatórios
// de acordo com a quantidade solicitada
// e adicionará cada processo na fila f inserida
id = procedural
tipo = aleatório entre 1 e 2
tempo de execução = aleatório entre 1 e 10
estado = 2 (pronto)
*/

void gerar_processos(Fila* f,int quantidade){
	srand(time(NULL)); //alimenta o rand - verificar se precisa estar aq
	int i;
	//roda a quantidade recebida de vezes
	for (i=1;i<quantidade+1;i++){
		int tipo_processo = (rand()%2)+1;
		int tempo_execucao = (rand()%10)+1;
		fila_insere_processo(f,i,tipo_processo,tempo_execucao); //criando processos com id = i e tipo = rand e te = rand
	}
}

void executar_processos(Fila*f){
	Lista* aux;
	aux = f->ini;
	while(!fila_vazia(f)){
		Lista* prox = aux->prox;
		printf("Executando processo: %d | TE T = %d\n", aux->id, aux->te);
		//retira 2 do tempo execução do processo atual
		aux->te = (aux->te-QUANTUM);
		printf("Retirado %d do processo %d | TE T = %d\n", QUANTUM, aux->id, aux->te);
		//passa para o próximo processo
		if(aux->te<=0){
			printf("Processo %d com te = %d", aux->id, aux->te);
			break;
		}
		aux = prox;
	}
}

