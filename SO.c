#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <locale.h>
#include <string.h>
#include "fila.c"
#include <unistd.h>
#include <time.h>
/*Implementa��o do SO  B�sico (Primitivo), em rela��o as opera��es b�sicas do gerenciamento de processos*/
/*Agendamento de Processos

/*Vale 10% da nota da 2� Av*/
//	
//int processo(pilha m){
//
//}
//

void main() {
	/*Implementar Pilhas que s�o criadas por threads*/
	setlocale(LC_ALL,"Portuguese");
	struct Fila E,B,P;
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
	printf("Ol� sou o Gerenciador do SO!\n");
	
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
					if(estaVazia(&E)){
						printf("\nFila vazia!!\n\n");
					}
					else{
						printf("\nProcessos em Execu��o => ");
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
			verificador = 0;
			printf("Qual o id do processo?\n");
			scanf("%d", &verificador);
			inserir(&P,verificador);
		}
	
		sleep(100);
		//if(){
			
	//	}
		
		
		
		//printf("/t2 p/ ver as lista de SO em pronto/n");
		//printf("/t3 p/ ver as lista de SO em bloqueado/n");
	}
	//return 0;
}

