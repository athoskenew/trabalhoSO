#include <stdlib.h>
#include <stdio.h>

struct Processo{
	int id;
	int tipo;
};
typedef struct Processo Processo

struct Fila {

	int capacidade;
	Processo *dados;
	int primeiro;
	int ultimo;
	int nItens; 

};
	
void criarFila( struct Fila *f, int c ) { 

	f->capacidade = c;
	f->dados = (float*) malloc (f->capacidade * sizeof(float));
	f->primeiro = 0;
	f->ultimo = -1;
	f->nItens = 0; 

}

void criarFilaProcesso( struct Fila *f,struct Processo *p, int c ) { 

	f->capacidade = c;
	f->dados = (Processo*) malloc (f->capacidade * sizeof(Processo));
	f->primeiro = 0;
	f->ultimo = -1;
	f->nItens = 0; 

}

void inserir(struct Fila *f, int v) {

	if(f->ultimo == f->capacidade-1)
		f->ultimo = -1;

	f->ultimo++;
	f->dados[f->ultimo] = v; // incrementa ultimo e insere
	f->nItens++; // mais um item inserido

}

int remover( struct Fila *f ) { // pega o item do começo da fila

	int temp = f->dados[f->primeiro++]; // pega o valor e incrementa o primeiro

	if(f->primeiro == f->capacidade)
		f->primeiro = 0;

	f->nItens--;  // um item retirado
	return temp;

}

int estaVazia( struct Fila *f ) { // retorna verdadeiro se a fila está vazia

	return (f->nItens==0);

}

int estaCheia( struct Fila *f ) { // retorna verdadeiro se a fila está cheia

	return (f->nItens == f->capacidade);
}

void mostrarFila(struct Fila *f){

	int cont, i;

	for ( cont=0, i= f->primeiro; cont < f->nItens; cont++){

		printf("%.2f\t",f->dados[i++]);

		if (i == f->capacidade)
			i=0;

	}
	printf("\n\n");

}

void mostrarFilaProcesso(struct Processo *p){

	int cont, i;

	for ( cont=0, i= p->primeiro; cont < p->nItens; cont++){

		printf("%d\t",p->id);

		if (i == p->capacidade)
			i=0;

	}
	printf("\n\n");

}
