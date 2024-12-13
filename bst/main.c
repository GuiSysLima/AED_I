#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"

int main(int argc, char const *argv[]){
    
    arvore lista;
    int opcao;
    int cont;
    lista = NULL;
    inicializar(&lista);

    while(1) {
        scanf("%d", &opcao);
        //__fpurge(stdin); 
        fflush(stdin);   
        switch(opcao) {
            int valor;
            case 1:
                lista = adicionar(lista, ler_dados());
                break;
            case 2:
                scanf("%d", &valor);
				lista = remover(lista, valor);
                break;
            case 10:
                //post_order(lista);
                //pre_order(lista);
                in_order(lista);
                printf("\n\nmaior elemento: [%d]\n", maior_elemento(lista));
                printf("menor elemento: [%d]\n", menor_elemento(lista));
                printf("\t\n\n -------- Altura --------\n\n");
            	printf("\t\t\t\n [%d] \n", altura(lista));
                printf("\n");
                break;
            case 99:
                printf("Encerrado!\n");
                return 0;
        }
    }
}
