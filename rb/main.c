#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc, char * argv[]) {
	arvore a;
	int opcao;
	int cont = 0;
	int cont_remo = 0;
	inicializar(&a);

	while(1) {
		printf("\t\t\n\n-------------- MENU --------------\n\n");
		scanf("%d", &opcao);

		switch(opcao){
				int valor;
				case 1:
					printf("\t\t\n\n-------------- ADICIONAR --------------\n\n");
					scanf("%d", &valor);
					adicionar(valor, &a);
					cont++;
					printf("contagem: [%d]", cont);
					//in_order(a);
					//imprimir(a);
					break;
				case 2:	
					printf("\t\t\n\n-------------- REMOVER --------------\n\n");
					scanf("%d", &valor);
					remover(valor, &a);
					cont_remo++;
					break;
				case 10:
					//imprimir(a);

					in_order(a);
					//pre_order(a);
					printf("\n\nmaior elemento: [%d]\n", maior_elemento(a));
					printf("menor elemento: [%d]\n", menor_elemento(a));
					printf("\n\t\t\n ----------- Altura -----------\n\n");
					printf("\n\n\n[%d]", altura(a));
				
					printf("\n");
					break;

				case 99:
						exit(0);
		}
	}
}
