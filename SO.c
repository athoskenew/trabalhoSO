#include <stdio.h>
#include <stdlib.h>
#include "fila.c"
#define QUANTUM 2
// assinaturas das funções
void gerar_processos(Fila* f,int quantidade);
void retira_finalizado(Fila* f, Fila* p);
void executar_processos(Fila* f, Fila* p);

int main (void){
	Fila* p = fila_cria();
	Fila* f = fila_cria(); //cria a fila de processos vazia
	Fila* finalizados = fila_cria(); //fila onde processo finalizados ficarão
	srand(time(NULL)); //alimentando rand()
	gerar_processos(f,20); //gerando 20 processos
	fila_insere_processo(f,25,2,0); //processo criado para testar função
	fila_imprime_processos(f); //imprimindo os processos da fila
	retira_finalizado(f,p);
	printf("");
	printf("######################################\n");
	fila_imprime_processos(p); //imprimindo os processos atualizados
	printf("");
	printf("######################################\n");
	executar_processos(f,p);
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


void retira_finalizado(Fila* f, Fila* p){
	Lista* aux = f->ini;
	Lista* dois = f->ini;
	Fila* k = p;
	//se o te for 0 então retira e retorna a lista
	for(aux;aux!=NULL;aux=aux->prox){	
		//ve se o te é 0
		if(aux->te==0){
			if(aux->prox==NULL){ //se encontrar no ultimo laço, apenas para o loop
				break;
			}
			printf("Achou - id: %d \n",aux->id);
			aux = aux->prox;
		}
		//se não for passa o processo pra fila k
		fila_insere_processo(k,aux->id,aux->tipo,aux->te); 
	}
	
	//return k; //se não, retorna a fila anterior
}

void executar_processos(Fila* f, Fila* p){
	Lista* aux;
	aux = f->ini;
	Fila* k = p;
	Fila* m = f;
	while(!fila_vazia(m)){
		Lista* prox = aux->prox;
		printf("Executando processo: %d | TE T = %d\n", aux->id, aux->te);
		
		//retira 2 do tempo execução do processo atual
		if(aux->te<QUANTUM){
			printf("Retirado %d do processo %d | TE T = %d\n", aux->te, aux->id,0);
			aux->te = 0; //retira tudo pq é menor que o quantum
		}
		else{
			aux->te = (aux->te-QUANTUM);
			printf("Retirado %d do processo %d | TE T = %d\n", QUANTUM, aux->id, aux->te);	
		}
		
		//passa para o próximo processo
		retira_finalizado(m,k);
		aux = prox;
	}
}

