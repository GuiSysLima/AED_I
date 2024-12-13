#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    
    arvore lista;
    int opcao;
    int controleFB;
    int cont;
    inicializar(&lista);

    while(1) {
        scanf("%d", &opcao);
        fflush(stdin);   
        switch(opcao) {
            int valor;
            case 1:
                scanf("%d", &valor);
                fflush(stdin);
                lista = adicionar(valor, lista, &controleFB);
                break;
            case 2:
                scanf("%d", &valor);
                fflush(stdin);
				lista = remover(valor, lista, &controleFB);
                break;
            case 10:
                //pre_order(lista);
                //pos_order(lista);
                in_order(lista);
                printf("\n\nmaior elemento: [%d]\n", maior_elemento(lista));
                printf("menor elemento: [%d]\n", menor_elemento(lista));
                printf("\n\n\t\t ------- ALTURA ------- \n\n");
                printf("\t\t\t\n [%d] \n", altura(lista));
                printf("\n");
                break;
            case 99:
                printf("\n\nEncerrado!\n\n");
                exit(0);
        }
    }
}
