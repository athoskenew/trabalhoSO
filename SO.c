#include <stdio.h>
#include <stdlib.h>
#include "fila.c"
#define QUANTUM 2
// assinaturas das fun��es
void gerar_processos(Fila* f,int quantidade);
Fila* retira_finalizado(Fila* f);
void executar_processos(Fila* f);
Fila* remanejar(Fila* f);

int main (void){
	Fila* p;
	Fila* f = fila_cria(); //cria a fila de processos vazia
	
	srand(time(NULL)); //alimentando rand()
	fila_insere_processo(f,50,2,0); //processo criado para testar fun��o
	gerar_processos(f,10); //gerando 20 processos
	fila_insere_processo(f,25,2,0); //processo criado para testar fun��o
	fila_imprime_processos(f); //imprimindo os processos da fila

//	p = remanejar(f); //n�o usaremos remanejar por enquanto
//	f = retira_finalizado(f);
	
	printf("######################################\n");
	
//	fila_imprime_processos(p); //imprimindo os processos atualizados
	
	printf("######################################\n");
	executar_processos(f);
	return 0;
}


/* Essa fun��o ir� gerar processos aleat�rios
** De acordo com a quantidade solicitada
** E adicionar� cada processo na fila f inserida
** id = procedural
** tipo = aleat�rio entre 1 e 2
** tempo de execu��o = aleat�rio entre 1 e 10
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
** J� foram finalizados
** E retorna uma lista sem eles
** Facilitando a manipula��o da lista
*/

Fila* retira_finalizado(Fila* f){
	Lista* aux = f->ini;
	Lista* dois = f->ini;
	Fila* k = fila_cria();
	//se o te for 0 ent�o retira e retorna a lista
	for(aux;aux!=NULL;aux=aux->prox){	
		//ve se o te � 0
		if(aux->te==0){
			if(aux->prox==NULL){ //se encontrar no ultimo la�o, apenas para o loop
				break;
			}
			printf("Achou - id: %d \n",aux->id);
			aux = aux->prox;
		}
		//se n�o for passa o processo pra fila k
		fila_insere_processo(k,aux->id,aux->tipo,aux->te); 
	}
	return k;
	//return k; //se n�o, retorna a fila anterior
}

/* Essa fun��o ir� passar todos os processos
** Que j� foram finalizados de uma fila f para
** Uma outra fila p, e liberar� toda
** a fila antiga f, perdendo sua refer�ncia
*/

Fila* remanejar(Fila* f){
	Fila* tst = f;
	Lista* aux = f->ini;
	Fila* k = fila_cria();
	//se o te for 0 ent�o retira e retorna a lista com te 0
	for(aux;aux!=NULL;aux=aux->prox){	
		//ve se o te � 0
		if(aux->te==0){
			if(aux->prox==NULL){ //se encontrar no ultimo la�o, apenas para o loop
				fila_insere_processo(k,aux->id,aux->tipo,aux->te);
				break;
			}
			printf("Achou - id: %d \n",aux->id);
			fila_insere_processo(k,aux->id,aux->tipo,aux->te);
		}
		//se n�o for passa o processo pra fila k
		else{
			aux = aux->prox; //caso n�o seja 0, passa para proximo n�
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
		
			//retira 2 do tempo execu��o do processo atual
			if(aux->te<QUANTUM){
				printf("Retirado %d do processo %d | TE T = %d\n", aux->te, aux->id,0);
				aux->te = 0; //retira tudo pq � menor que o quantum
			}
			else{
				aux->te = (aux->te-QUANTUM);
				printf("Retirado %d do processo %d | TE T = %d\n", QUANTUM, aux->id, aux->te);	
			}
		
			//passa para o pr�ximo processo
		}
		m = retira_finalizado(m);
		aux = m->ini;
		sleep(1);
	}
}

