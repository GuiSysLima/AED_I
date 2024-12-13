#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#define tamanhoDoEspaco 10

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

int contarNo(arvore raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return contarNo(raiz->esq) + contarNo(raiz->dir);
    }
}

arvore adicionar(int valor, arvore raiz, int *cresceu){

	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
        novo->altura = 0;
	    *cresceu = 1; 
		return novo;
	}

	if(valor > raiz->dado) {
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
        if(*cresceu) {
			switch(raiz->dir->fb){
                case 0:
					raiz->dir->fb = 0;
                    *cresceu = 0;
                    break;
                case -1:
					raiz->dir->fb = -1;
					*cresceu = -1;
					break;
				case 1:
                    raiz->dir->fb = 1;
					*cresceu = 1;
				
                return rotacionar(raiz);
			}
		}

	} 
    else{
        raiz->esq = adicionar(valor, raiz->esq, cresceu);
        if(*cresceu){
            
			switch(raiz->esq->fb) {
                case 0:
					raiz->esq->fb = 0;
                    *cresceu = 0;
					break;
                case -1:
					raiz->esq->fb = -1;
					*cresceu = -1;
					break;
                case 1:
                    raiz->esq->fb = 1;
					*cresceu = 1;
				
                
                return rotacionar(raiz);
			}
		}
	}
    raiz->altura = maior(alturaNoh(raiz->esq), alturaNoh(raiz->dir)) + 1;
	return raiz;
}

int fatorBalanceamento(arvore raiz){
    return labs(alturaNoh(raiz->esq)- alturaNoh(raiz->dir));
}

int alturaNoh(arvore raiz){
    if (raiz==NULL) 
        return -1;
    else
        return raiz->altura;
}

int alturaArvore(arvore raiz){

	int alturaDireita=0;
	int alturaEsquerda=0;

	if (raiz == NULL){	
		return -1;
	}

	alturaEsquerda = alturaArvore(raiz->esq);
	alturaDireita = alturaArvore(raiz->dir);

	if (alturaEsquerda > alturaDireita)
	{
		return alturaEsquerda+1;
	}
	else
	{
		return alturaDireita+1;
	}

}

int contarNos(arvore raiz){
	//contar quantos nós tem na árvore
	if(raiz == NULL){
		return 0;
		
	}else{
		return contarNos(raiz->esq) + contarNos(raiz->dir) + 1; 
	}

}

arvore rotacionar(arvore raiz){

	if(raiz->fb > 0){
		switch(raiz->dir->fb){
			case 0:
                printf("rotacao simples direita\n");
                return rotacao_simples_direita(raiz);
			case -1:
                printf("rotacao dupla esquerda\n");
				return rotacao_dupla_esquerda(raiz);
            case 1:
                printf("rotacao simples esquerda\n");
				return rotacao_simples_esquerda(raiz);					
		} 
	}
    else{
        switch(raiz->esq->fb){
            case 0:
                printf("rotacao simples esquerda\n");
                return rotacao_simples_esquerda(raiz);
            case -1:
                printf("rotacao dupla direita\n");
                return rotacao_dupla_direita(raiz);
            case 1:
                printf("rotacao simples direita\n");
                return rotacao_simples_direita(raiz);
        }
    }
}    

arvore remover (int valor, arvore raiz, int *diminuiu) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado == valor) {

        if(raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
           *diminuiu = 1;
            return NULL;
        }		
		if(raiz->esq == NULL && raiz->dir != NULL) {
            //liberar memória 
            free(raiz);
           *diminuiu = 1;
			return raiz->dir;
		}
		if(raiz->esq != NULL && raiz->dir == NULL) {
            //liberar memória
			free(raiz);
           *diminuiu = 1;
			return raiz->esq;
		}
        if(raiz->esq != NULL && raiz->dir != NULL) {
		    raiz->dado = maior_elemento(raiz->esq);
		    raiz->esq = remover(raiz->dado, raiz->esq, diminuiu);
		    return raiz;
        }
	}	
	if(valor > raiz->dado) {
			raiz->dir = remover(valor, raiz->dir, diminuiu);
       //verifica se a árvore diminuiu e ajusta os fatores de balanço
	} else {
			raiz->esq = remover(valor, raiz->esq, diminuiu);
        //
	}
	return raiz;

}

/*
arvore remover(int valor, arvore raiz, int *diminuiu) {
	int controle;

    if(raiz == NULL){
		return NULL;
    }
    if(valor < raiz->dado){
        raiz->dir = remover(valor, raiz->dir, diminuiu);

        if(*diminuiu) {
			switch(raiz->fb) {
				case 0:
					raiz->dir->fb= 0;
                    *diminuiu = 0;
					break;
			    case -1:
					raiz->dir->fb = -1;
					*diminuiu = -1;
					break;
				case 1:

                    raiz->dir->fb = 1;
					*diminuiu = 1;
				return rotacionar(raiz);
			}
		}

	}
    else{
        raiz->esq = remover(valor, raiz->esq, diminuiu);

        if(*diminuiu){
			switch(raiz->fb){
				case 0:
					raiz->esq->fb = 0;
                    *diminuiu = 0;
					break;
			    case -1:
					raiz->esq->fb = -1;
					*diminuiu = -1;
					break;
				case 1:
                    raiz->esq->fb = 1;
					*diminuiu = 1;
			
                return rotacionar(raiz);
			}
		}
    }
    return raiz;
}
*/

arvore buscar(arvore raiz, int valor){

    if(raiz == NULL) {
        return NULL;
    }

    if(raiz->dado == valor)  {
        return raiz;
    }
    if(valor >= raiz->dado) {
        return buscar(raiz->dir,valor);
    } else {
        return buscar(raiz->esq,valor);
    }
    buscar(raiz, valor);
    
}

arvore rotacao_simples_direita(arvore raiz) {
	arvore p, u, t1, t2, t3;

	p = raiz;
	u = raiz->dir;
    t1 = p->esq;

    t2 = u->esq;
    t3 = u->dir;

	p->esq = t2;
	u->dir = p;
    
	if(u->fb == 1){
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	

    raiz->altura = maior(alturaNoh(raiz->esq), alturaNoh(raiz->dir)) + 1;
    u->altura = maior(alturaNoh(u->esq), raiz->altura) + 1;
    raiz = u;

    //return u;
	return raiz;
}


arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p, u, t1, t2, t3;
	p = raiz;

	u = raiz->dir;
    t1 = p->esq;

    t2 = u->esq;
    t3 = u->dir;

	p->dir = t2;
	u->esq = p;
    
	if(u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	
    raiz->altura = maior(alturaNoh(raiz->esq), alturaNoh(raiz->dir)) + 1;
    u->altura = maior(alturaNoh(u->esq), raiz->fb) + 1;
    //ou p

    //return u;
	return raiz;
}

arvore rotacao_dupla_esquerda(arvore raiz){
    raiz->esq = rotacao_simples_esquerda(raiz->esq);
	return rotacao_simples_direita(raiz);
}

arvore rotacao_dupla_direita(arvore raiz){

    raiz->dir = rotacao_simples_direita(raiz->dir);
	return rotacao_simples_esquerda(raiz);
}

void imprimir(arvore raiz){
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

void imprimir_elemento(arvore raiz){
	printf("%d [%d]", raiz->dado, raiz->altura);
}

int altura(arvore raiz){
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz){
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz){
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return menor_elemento(raiz->esq);
}

void pre_order(arvore raiz){
	if(raiz != NULL) {
		imprimir_elemento(raiz);
        //imprimir(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz){
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
        //imprimir(raiz);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz){
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
        //imprimir(raiz);
		in_order(raiz->dir);
	}
}

void salvar_arquivo(char *nome, arvore salvar_lista){
    FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(salvar_lista, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
        //percurso pré-order
		fwrite(raiz, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}
/*
arvore carregar_arquivo(char *nome, arvore carregar_lista){
	FILE *arq;
	arq = fopen(nome, "rb");
	int temp;
    int *fb;

	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			carregar_lista = adicionar(temp, carregar_lista, fb);		
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));
            //printf("\n[%d]", carregar_lista->dado->num);
		}
		fclose(arq);

	}
	return carregar_lista;
}
*/
