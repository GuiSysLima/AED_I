#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar(arvore *raiz){
	*raiz = NULL;
}

arvore adicionar(arvore raiz, tipo_dado *valor){
    if(raiz == NULL){
        arvore novo = (arvore) malloc(sizeof(struct no));

        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;

        return novo;
    }
    if(valor->num > raiz->dado->num){
        raiz->dir = adicionar(raiz->dir, valor);
    }
    else{
        raiz->esq = adicionar(raiz->esq, valor);
    }

    return raiz;
}


int altura(arvore raiz){
	int esq_aux, dir_aux;
	if(raiz == NULL){
		return -1;
	}
	esq_aux = altura(raiz->esq);
	dir_aux = altura(raiz->dir);
	return (esq_aux > dir_aux ? esq_aux : dir_aux) + 1;
}

int maior(arvore raiz) {
    if(raiz == NULL) {
        return -1;
    }

    no* temp = raiz;
    while(temp->dir != NULL) {
       temp = temp->dir;
    }
    return temp->dado->num;
}


arvore buscar(arvore raiz, int valor){
    //caso base 1
    if(raiz == NULL) {
        return NULL;
    }

    //caso base 2
    if(raiz->dado->num == valor)  {
        return raiz;
    }
    if(valor >= raiz->dado->num) {
        return buscar(raiz->dir,valor);
    } else {
        return buscar(raiz->esq,valor);
    }
    buscar(raiz, valor);
    
}

int maior_elemento(arvore raiz){
	if(raiz == NULL)
			return -1;
	else if(raiz->dir == NULL)
		return raiz->dado->num;
	else
		return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz){
	if(raiz == NULL)
		return -1;
	else if(raiz->esq == NULL)
		return raiz->dado->num;
	else
		return menor_elemento(raiz->esq);
}

arvore remover (arvore raiz, int valor) {

      if(raiz == NULL){
         return NULL;
      }

      if(raiz->dado->num == valor){
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }

            if(raiz->esq != NULL && raiz->dir == NULL) {
                no * filho = raiz->esq;
                free(raiz);
                return filho;
            }

            if(raiz->dir != NULL && raiz->esq == NULL) {
                no * filho = raiz->dir;
                free(raiz);
                return filho;
            }

            if(raiz->esq != NULL && raiz->dir != NULL) {
                int m = maior(raiz->esq);
				//maior(raiz->esq, raiz->dir);
                raiz->dado->num = m;
                raiz->esq = remover(raiz->esq, m);
                return raiz;
            }   
      }
      if(valor >= raiz->dado->num) {
        raiz->dir = remover(raiz->dir,valor);
    } else {
        raiz->esq = remover(raiz->esq,valor);
    }   

    return raiz;
}


/*
arvore remover(int valor, arvore raiz){
	if(raiz == NULL){
		return NULL;
	}
	if(raiz->dado->num == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->num, raiz->esq);
		return raiz;
	}	
	if(valor > raiz->dado->num) {
			raiz->dir = remover(valor, raiz->dir);
	} else {
			raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;

}
*/

void pre_order(arvore raiz){
    if(raiz != NULL){
        printf("[%d]\n",raiz->dado->num);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void in_order(arvore raiz){
    if(raiz != NULL){
        in_order(raiz->esq);
        printf("[%d]\n",raiz->dado->num);
        in_order(raiz->dir);
    }
}

void post_order(arvore raiz){
    if(raiz != NULL){
        post_order(raiz->esq);
        post_order(raiz->dir);
        printf("[%d]\n",raiz->dado->num);
    }
}

tipo_dado * ler_dados(){
    tipo_dado * novo = (tipo_dado*) malloc(sizeof(tipo_dado));
    scanf("%d", &novo->num);
    //__fpurge(stdin); 
    fflush(stdin);
    return novo;
}