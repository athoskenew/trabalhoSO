#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <locale.h>
#include <string.h>
#include "fila.c"
#include <unistd.h>
#include <dos.h>
#include <time.h>
/*Implementação do SO  Básico (Primitivo), em relação as operações básicas do gerenciamento de processos*/
/*Agendamento de Processos

/*Vale 10% da nota da 2ª Av*/
//	
//int processo(pilha m){
//
//}
//

void main() {
	/*Implementar Pilhas que são criadas por threads*/
	setlocale(LC_ALL,"Portuguese");
	struct Fila E,B,P,aux;
//	//int bloqueado;
//	//int pronto;
//	//int executando;
	int verificador;
	//char Sim = 's';
	//printf("%c",Sim);
	//char verificadorString[4] = ' ';
	criarFila(&E,100);
	criarFila(&B,100);
	criarFila(&P,100);
	int id=0, tipo;
	printf("Olá sou o Gerenciador do SO!\n");
	
	while(1){
		
		printf("\t1 p/ add Processo em Pronto? s = 1/n = 2\n");
		scanf("%d",&verificador);
		
		if(verificador==2){
			verificador = 0;
			printf("\t1 p/ ver a lista de Processos\n");
			scanf("%d",&verificador);
		
			switch(verificador){
				case 1:
					verificador = 0;
					printf("Lista de processos apos a criacao de um processo\n\n");
					if(estaVazia(&E)){
						printf("\nFila vazia!!\n\n");
					}
					else{
						printf("\nProcesso em Execução => ");
						mostrarFila(&E);
						}
					if(estaVazia(&P)){
						printf("\nFila vazia!!\n\n");
					}
					else{
						printf("\nProcessos em Pronto => ");
						mostrarFila(&P);
						}
					if(estaVazia(&B)){
						printf("\nFila vazia!!\n\n");
					}
					else{
						printf("\nProcessos em Bloqueado => ");
						mostrarFila(&B);
						}
					break;			
		}
		}
		if(verificador==1){
			do{
				printf("Digite o tipo do processo\n1 - CPU-Bound\n2 - I/O-Bound");//definicao do tipo do processo
				scanf("%d",&tipo);
				switch(tipo){
					case 1://caso o processo seja do tipo CPU-Bound
						id++;
						inserir(&P, id);
						printf("O processo %d foi inserido em pronto\n",id);//todo processo criado ira para a fila de pronto
						sleep(1);//aguarda 1s
						remover(&P);//sai da fila de pronto
						printf("O processo %d ficou 1s em pronto\n",id);
						if(!estaVazia(&E)){
							remover(&E);
							printf("Processo %d retirado\n",id-1);//casa haja 1 processo na fila de execucao esse processo eh retirado para a entrada do proximo
							inserir(&E, id);//o processo eh inserido na fila de execucao
							printf("O processo %d foi inserido em execucao\n",id);
						}
						else{
							inserir(&E,id);
							printf("O processo %d foi inserido em execucao\n",id);//o processo eh inserido na fila de execucao
						}
					break;
					case 2://caso o processo seja do tipo I/O-Bound
						id++;
						inserir(&P, id);
						printf("O processo %d foi inserido em pronto\n",id);//todo processo criado ira para a fila de pronto
						sleep(1);//aguarda 1s
						remover(&P);//sai da fila de pronto
						printf("O processo %d ficou 1s em pronto\n",id);
						inserir(&B, id);
						printf("O processo %d foi inserido em bloqueado\n",id);
						sleep(5);//o processo eh inserido na fila de bloqueado
						printf("O processo %d ficou 5s em bloqueado\n",id);
					break;
					default:
						printf("Tipo invalido!");
					break;
				}
			}while(tipo!=1 && tipo!=2);
				//for(i=0;i<P.nItens-2;i++){
			//		inserir(&aux, remover(&P));
			//	}
			
		}
	
		//if(){
			
	//	}
		
		
		
		//printf("/t2 p/ ver as lista de SO em pronto/n");
		//printf("/t3 p/ ver as lista de SO em bloqueado/n");
	}
	//return 0;
}

