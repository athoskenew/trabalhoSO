#include <stdio.h>
#include <stdlib.h>
#include "fila.c"
#define QUANTUM 2
// assinaturas das funções
void gerar_processos(Fila* f,int quantidade);
Fila* retira_finalizado(Fila* f);
void executar_processos(Fila* f);
Fila* remanejar(Fila* f);

int main (void){
	Fila* p;
	Fila* f = fila_cria(); //cria a fila de processos vazia
	
	srand(time(NULL)); //alimentando rand()
	fila_insere_processo(f,50,2,0); //processo criado para testar função
	gerar_processos(f,10); //gerando 20 processos
	fila_insere_processo(f,25,2,0); //processo criado para testar função
	fila_imprime_processos(f); //imprimindo os processos da fila

//	p = remanejar(f); //não usaremos remanejar por enquanto
//	f = retira_finalizado(f);
	
	printf("######################################\n");
	
//	fila_imprime_processos(p); //imprimindo os processos atualizados
	
	printf("######################################\n");
	executar_processos(f);
	return 0;
}


/* Essa função irá gerar processos aleatórios
** De acordo com a quantidade solicitada
** E adicionará cada processo na fila f inserida
** id = procedural
** tipo = aleatório entre 1 e 2
** tempo de execução = aleatório entre 1 e 10
** estado = 2 (pronto)
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

/* Retira da fila os processos que
** Já foram finalizados
** E retorna uma lista sem eles
** Facilitando a manipulação da lista
*/

Fila* retira_finalizado(Fila* f){
	Lista* aux = f->ini;
	Lista* dois = f->ini;
	Fila* k = fila_cria();
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
	return k;
	//return k; //se não, retorna a fila anterior
}

/* Essa função irá passar todos os processos
** Que já foram finalizados de uma fila f para
** Uma outra fila p, e liberará toda
** a fila antiga f, perdendo sua referência
*/

Fila* remanejar(Fila* f){
	Fila* tst = f;
	Lista* aux = f->ini;
	Fila* k = fila_cria();
	//se o te for 0 então retira e retorna a lista com te 0
	for(aux;aux!=NULL;aux=aux->prox){	
		//ve se o te é 0
		if(aux->te==0){
			if(aux->prox==NULL){ //se encontrar no ultimo laço, apenas para o loop
				fila_insere_processo(k,aux->id,aux->tipo,aux->te);
				break;
			}
			printf("Achou - id: %d \n",aux->id);
			fila_insere_processo(k,aux->id,aux->tipo,aux->te);
		}
		//se não for passa o processo pra fila k
		else{
			aux = aux->prox; //caso não seja 0, passa para proximo nó
		} 
	}
	//fila_libera(tst); //libera a fila f passada como argumento, tomar cuidado com isso
	return k; //retorna a fila com processos zerados
}

void executar_processos(Fila* f){
	Lista* aux;
	Fila* m = f;
	aux = m->ini;
	while(!fila_vazia(m)){
		for(aux;aux!=NULL;aux=aux->prox){
			//Lista* prox = aux->prox;

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
		}
		m = retira_finalizado(m);
		aux = m->ini;
		sleep(1);
	}
}

