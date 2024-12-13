#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;


void inicializar(arvore *raiz){
    *raiz = NULL;

	arvore no_null;
	no_null = (arvore) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
	no_null->pai = NULL;
}


void adicionar(int valor, arvore *raiz){
	
	arvore temp, pai, novo;
	temp = *raiz;
	pai = NULL;
	
	while(temp != NULL) {
		pai = temp;
			
		if(valor > temp->dado){
			temp = temp->dir;
		} else {
			temp = temp->esq;
		}
	}

	novo = (arvore) malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz(novo)){	
		*raiz = novo;
	}else{
		if(valor > pai->dado){
			pai->dir = novo;
		} else{
			pai->esq = novo;
		}
	}
	
	ajustar(raiz, novo);
}

void ajustar(arvore *raiz, arvore elemento){

	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){

		if(cor(tio(elemento)) == VERMELHO){
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;			
			elemento = elemento->pai->pai;
			continue;
		}
		if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){
			rotacao_simples_direita(raiz, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->dir->cor = VERMELHO;
			continue;
		}
		if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)){
			rotacao_simples_esquerda(raiz, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->esq->cor = VERMELHO;
			continue;

		}
	
		if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){	
			
			rotacao_dupla_direita(raiz, elemento->pai->pai);
			elemento->cor = PRETO;
			elemento->dir->cor = VERMELHO;
			elemento->esq->cor = VERMELHO;
			continue;
		}
	
		if(!eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)){
			rotacao_dupla_esquerda(raiz, elemento->pai->pai);
			elemento->cor = PRETO;
			elemento->dir->cor = VERMELHO;
			elemento->esq->cor = VERMELHO;
			continue;
		}
	}
     (*raiz)->cor = PRETO;

}

/*
void adicionar(int valor, arvore *raiz){
	arvore temp, pai, novo;

	novo = (arvore) malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if (*raiz == NULL){
        *raiz = novo;
    }
	else{
		
		temp = *raiz;
		pai = NULL;

		while(temp != NULL){
			pai = temp;
			
			if(valor > temp->dado){
				temp = temp->dir;
			}
			else{
				temp = temp->esq;
			}
		}

		if(eh_raiz(novo)){
			*raiz = novo;
		}
		else{
			if(valor > pai->dado){
				pai->dir = novo;
			}
			else{
				pai->esq = novo;
			}
		}

		ajustar(raiz, novo);
	}
	//ajustar(raiz, novo);
}

void ajustar(arvore *raiz, arvore elemento){

		while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){

			if(cor(tio(elemento)) == VERMELHO){
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;			
				elemento = elemento->pai->pai;
				continue;
			}
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){
				rotacao_simples_direita(raiz, elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->dir->cor = VERMELHO;
				continue;
			}
			if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)){
				rotacao_simples_esquerda(raiz, elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->esq->cor = VERMELHO;
				continue;

			}
		//caso 3a: rotação dupla direita
			if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){	
				//printf("\nCaso3a\n");
				rotacao_dupla_direita(raiz, elemento->pai->pai);
				elemento->cor = PRETO;
				elemento->dir->cor = VERMELHO;
				elemento->esq->cor = VERMELHO;
				//não precisa continuar pois a raiz relativa termina em preto
				//elemento = elemento->pai;
			}
		//caso 3b: rotação dupla esquerda
			if(!eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)){
				rotacao_dupla_esquerda(raiz, elemento->pai->pai);
				elemento->cor = PRETO;
				elemento->dir->cor = VERMELHO;
				elemento->esq->cor = VERMELHO;
				//não precisa continuar pois a raiz relativa termina em preto
				//elemento = elemento->pai;

			}
		}
	
    //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta - CASO 0
	(*raiz)->cor = PRETO;

}
*/
void rotacao_simples_direita(arvore *raiz, arvore pivo){
	arvore u, t1;
	u = pivo->esq;
    t1 = u->dir;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	pivo->esq = t1;
    if(t1 != NULL){
		t1->pai = pivo;
    }
	u->pai = pivo->pai;
    u->dir = pivo;
	pivo->pai = u;

    if(eh_raiz(u)){
		*raiz = u;
    }
	else{
		if(posicao_pivo_esq){
            u->pai->esq = u;
        }
	    else{
			u->pai->dir = u;
        }
	}
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
    arvore u, t1;
	u = pivo->dir;
    t1 = u->esq;

	int posicao_pivo_dir = eh_filho_direito(pivo);

	pivo->dir = t1;
    if(t1 != NULL){
	    t1->pai = pivo;
    }
    u->pai = pivo->pai;
	u->esq = pivo;
	pivo->pai = u;
	if(eh_raiz(u)){
		*raiz = u;
    }
	else{
	    if(posicao_pivo_dir){
		    u->pai->dir = u;
        }
        else{
            u->pai->esq = u;
		}
    }
}

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
	
    	arvore u,v, t2, t3;
	u = pivo->dir;

	v = u->esq;
    	t2 = v->dir;
    	t3 = v->esq;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	pivo->dir = t3;

	if(t3 != NULL) {
		t3->pai = pivo;
	}
	
	v->pai = pivo->pai;
	u->esq = t2;

	if(t2 != NULL){
		t2->pai = u;
	}

	pivo->pai = v;
	u->pai = v;
	
	v->dir = u;
	v->esq = pivo;
	
	if(eh_raiz(v)) {
		*raiz = v;
	}else {
		if(posicao_pivo_esq){
			v->pai->esq = v;
		}
		else{
			v->pai->dir = v;
		}
	}	
}


void rotacao_dupla_direita(arvore *raiz, arvore pivo){
	
	arvore u,v, t2, t3;
	u = pivo->esq;

	v = u->dir;
    	t2 = v->esq;
    	t3 = v->dir;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	pivo->esq = t3;
	if(t3 != NULL){
		t3->pai = pivo;
	}
	
	v->pai = pivo->pai;
	u->dir = t2;

	if(t2 != NULL){
		t2->pai = u;
	}
	pivo->pai = v;
	u->pai = v;
	
	v->dir = pivo;
	v->esq = u;
	
	if(eh_raiz(v)){
		*raiz = v;
	} else {
		if(posicao_pivo_esq){
			v->pai->esq = v;
		} else{
			v->pai->dir = v;
		}
	}	
}

/*
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
	
    arvore u, t1;
	u = pivo->dir;
    t1 = u->esq;

	int posicao_pivo_dir = eh_filho_direito(pivo);

	pivo->dir = t1;
    if(t1 != NULL){
	    t1->pai = pivo;
    }
    u->pai = pivo->pai;
	u->esq = pivo;
	pivo->pai = u;
	if(eh_raiz(u)){
		*raiz = u;
    }
	else{
	    if(posicao_pivo_dir){
		    u->pai->dir = u;
        }
        else{
            u->pai->esq = u;
		}
    }
	rotacao_simples_direita(raiz, u->pai);
	//rotacao_simples_esquerda(raiz, u->pai);
}



void rotacao_dupla_direita(arvore *raiz, arvore pivo){
	arvore u, t1;
	u = pivo->esq;
    t1 = u->dir;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	pivo->esq = t1;
    if(t1 != NULL){
		t1->pai = pivo;
    }
	u->pai = pivo->pai;
    u->dir = pivo;
	pivo->pai = u;

    if(eh_raiz(u)){
		*raiz = u;
    }
	else{
		if(posicao_pivo_esq){
            u->pai->esq = u;
        }
	    else{
			u->pai->dir = u;
        }
	}
	rotacao_simples_esquerda(raiz, u->pai);
	//rotacao_simples_direita(raiz, u->pai);
	printf("rotacao dupla");
}
*/

enum cor cor(arvore elemento){
	enum cor c;
	if(elemento == NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (!eh_raiz(elemento) && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento){
	return (!eh_raiz(elemento) && elemento == elemento->pai->dir);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}


void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
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

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz){

	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

void rb_transplant(arvore t, arvore u, arvore v){
	if(u->pai == no_null)
		no_null = v;
	else if(u == u->pai->esq)
		u->pai->esq = v;
	else
		u->pai->dir = v;
	v->pai = u->pai;
}

void remover(int valor, arvore *raiz){
	arvore posicao;

	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado){
            if(posicao->esq != NULL && posicao->dir != NULL){ 
    			posicao->dado = maior_elemento(posicao->esq);   
	    		remover(posicao->dado, &(posicao->esq));
				
                break;
            }

			if(posicao->esq == NULL && posicao->dir != NULL){
                arvore filhoDireito;

                filhoDireito = posicao->dir;
				filhoDireito->cor = PRETO;
                filhoDireito->pai = posicao->pai;
				if(eh_raiz(posicao)){
					*raiz = posicao->dir;
				}
				else{
					if(eh_filho_esquerdo(posicao)){
    					posicao->pai->esq = filhoDireito;
					} 
					else{
						posicao->pai->dir = filhoDireito;
    				}
				}
				
				break;
			}

			if(posicao->esq != NULL && posicao->dir == NULL){
				arvore filhoEsquerdo;

                filhoEsquerdo = posicao->esq;
				filhoEsquerdo->cor = PRETO;
                filhoEsquerdo->pai = posicao->pai;
				if(eh_raiz(posicao)){
					*raiz = posicao->esq;
				} 
				else{
					if(eh_filho_direito(posicao)){
    					posicao->pai->dir = filhoEsquerdo;
					}
					else{
						posicao->pai->esq = filhoEsquerdo;
    				} 
				}
				
				break;
			}

			if(posicao->esq == NULL && posicao->dir == NULL){		
				
				if(eh_raiz(posicao)){
					*raiz = NULL;
					break;
				}

				if(posicao->cor == VERMELHO){
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
					break;
				} 
				else{
					no_null->pai = posicao->pai;
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;
					
					reajustar(raiz, no_null);
					break;
				}
			}
		}	
		if(valor > posicao->dado){
			posicao = posicao->dir;
			//remover(posicao->dado, &(posicao->dir));
		}
		else{
			posicao = posicao->esq;
			//remover(posicao->dado, &(posicao->esq));
		}
	}
}


/*
void remover(int valor, arvore *raiz){
	arvore posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado){
            if(posicao->esq != NULL && posicao->dir != NULL){ 
    			posicao->dado = maior_elemento(posicao->esq);   
	    		remover(posicao->dado, &(posicao->esq));
                break;
            }

			if(posicao->esq == NULL && posicao->dir != NULL){
                arvore filhoDireito;

                filhoDireito = posicao->dir;
				filhoDireito->cor = PRETO;
                filhoDireito->pai = posicao->pai;

				if(eh_raiz(posicao)){
					*raiz = posicao->dir;
				}
				else{
					if(eh_filho_esquerdo(posicao)){
    					posicao->pai->esq = filhoDireito;
					} 
					else{
						posicao->pai->dir = filhoDireito;
    				}     
					reajustar(raiz, posicao); 
				}
				posicao->dado = maior_elemento(posicao->dir);
				remover(posicao->dado, &(posicao->esq));
				//reajustar(raiz, posicao);
				//free(posicao);
				break;
			}

			if(posicao->esq != NULL && posicao->dir == NULL){
				arvore filhoEsquerdo;

                filhoEsquerdo = posicao->esq;
				filhoEsquerdo->cor = PRETO;
                filhoEsquerdo->pai = posicao->pai;

				if(eh_raiz(posicao)){
					*raiz = posicao->esq;
				} 
				else{
					if(eh_filho_direito(posicao)){
    					posicao->pai->dir = filhoEsquerdo;
					}
					else{
						posicao->pai->esq = filhoEsquerdo;
    				} 
					reajustar(raiz, posicao);
				}
				posicao->dado = maior_elemento(posicao->esq);
				remover(posicao->dado, &(posicao->esq));
				//reajustar(raiz, posicao);
				//free(posicao);
				break;
					
			}

			if(posicao->esq == NULL && posicao->dir == NULL){				
				if(eh_raiz(posicao)){
					*raiz = NULL;
					//posicao->dado = maior_elemento(posicao->esq);
					//remover(posicao->dado, &(posicao->pai));
					//free(posicao);
					reajustar(raiz, no_null);
					break;
				}

				if(posicao->cor == VERMELHO){
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
					reajustar(raiz, posicao);
					break;
				} 
				else{
					no_null->pai = posicao->pai;
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;
					
					reajustar(raiz, no_null);
					break;
				}
				posicao->dado = maior_elemento(posicao->dir);
				remover(posicao->dado, &(posicao->pai));
				//free(posicao);
			}
		}	
		if(valor > posicao->dado){
			posicao = posicao->dir;
		}
		else{
			posicao = posicao->esq;
		}
	}
}
*/

/*
void reajustar(arvore *raiz, arvore elemento){
    //cor(irmao(elemento)->dir), cor(irmao(elemento)->esq);
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){
		if(eh_raiz(elemento)){
			elemento->cor = PRETO;
			if(elemento == no_null)
				*raiz = NULL;
			return;
		}
		//caso 2
		if( cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO)
		{
			
			if(eh_filho_esquerdo(elemento)){
				rotacao_simples_esquerda(raiz, elemento->pai);
			}
			else{
				rotacao_simples_direita(raiz, elemento->pai);	
			}
			elemento->pai->pai->cor = PRETO;
			elemento->pai->cor = VERMELHO;

			reajustar(raiz, elemento);
			return;
		}
		//caso 3
		if( cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == VERMELHO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == PRETO){
			
			rotacao_simples_direita(raiz, elemento->pai);
			//irmao(elemento)->cor = VERMELHO;
			elemento->pai->cor = VERMELHO;
			elemento->pai->pai->cor = PRETO;
			elemento->pai->pai->cor = elemento->pai->pai->esq->cor;
			
			reajustar(raiz, elemento);
			retira_duplo_preto(raiz, elemento->pai);
			//Verificar e remover o no_null
			//Chamada recursiva para eliminar o duplo preto do elemento P
			return;
		}	

		//caso 4
		if(  cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == PRETO){
			rotacao_simples_direita(raiz, elemento->pai);
			//irmao(elemento)->cor = VERMELHO;
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->cor = PRETO;

			reajustar(raiz, elemento);
			retira_duplo_preto(raiz, elemento->pai);
			//Verificar e remover o no_null
			return;
		}

		//Caso 5a(direita):
		if( cor(elemento->pai) == PRETO || cor(elemento->pai) == VERMELHO &&
			cor(tio(elemento->esq)) == no_null &&
			cor(tio(elemento->dir)) == PRETO &&
			cor(irmao(elemento)->esq) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO){
				
			rotacao_dupla_direita(raiz, elemento->pai);
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = elemento->pai->pai->cor;
			elemento->pai->pai->cor = elemento->pai->cor;
			reajustar(raiz, elemento);
			return;
		}

		//caso 5b(esquerda):
		if( cor(elemento->pai) == PRETO || cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == VERMELHO){
			
			rotacao_dupla_esquerda(raiz, elemento->pai);
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->esq->cor = elemento->pai->pai->cor;
			elemento->pai->pai->cor = elemento->pai->cor;
			reajustar(raiz, elemento);
			return;
		}

		//caso 6a(direita):
		if( cor(elemento->pai) == PRETO || cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == VERMELHO){
			
			rotacao_simples_direita(raiz, elemento->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			reajustar(raiz, elemento);
			return;
		}

		//caso 6b(esquerda):
		if( cor(elemento->pai) == PRETO || cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO){	
			
			rotacao_simples_esquerda(raiz, elemento->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			reajustar(raiz, elemento);
			return;
		
		}
	}
		
}
*/


void reajustar(arvore *raiz, arvore elemento){
    //cor(irmao(elemento)->dir), cor(irmao(elemento)->esq);
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){
		
		// #Caso 1
		if(eh_raiz(elemento)){
			elemento->cor = PRETO;
			if(elemento == no_null)
				*raiz = NULL;
			return;
		}
		// #Caso 2
		if( cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO){
			
			if(eh_filho_esquerdo(elemento)){
				rotacao_simples_esquerda(raiz, elemento->pai);
			}
			else{
				rotacao_simples_direita(raiz, elemento->pai);	
			}
			elemento->pai->pai->cor = PRETO;
			elemento->pai->cor = VERMELHO;

			reajustar(raiz, elemento);
			return;
		}
		// #Caso 3 
		if(cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
		
			elemento->cor = PRETO;
			elemento->pai->cor = DUPLO_PRETO;
			irmao(elemento)->cor = VERMELHO;
		
			if(eh_filho_esquerdo(elemento)) {
				elemento->pai->esq = NULL;
			} else {
				elemento->pai->dir = NULL;
			}	

			reajustar(raiz, elemento->pai);
			return;
		}		

		// #Caso 4
		if(  cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == PRETO){

			elemento->cor = PRETO;
			elemento->pai->cor = PRETO;
			irmao(elemento)->cor = VERMELHO;
		
			if(eh_filho_esquerdo(elemento)) {
				elemento->pai->esq = NULL;
			} else {
				elemento->pai->dir = NULL;
			}
			return;
		}

		// #Caso 5a
		if(  eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == VERMELHO) {	
		
		
			rotacao_simples_direita(raiz,irmao(elemento));
		
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->dir->cor = VERMELHO;

			reajustar(raiz, elemento);
			return;
		}

		// #Caso 5b
		if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == VERMELHO &&
		 cor(irmao(elemento)->esq) == PRETO) {	
			rotacao_simples_esquerda(raiz,irmao(elemento));
		
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->esq->cor = VERMELHO;

			reajustar(raiz, elemento);
			return;
		}

		// #Caso 6a
		if(cor(elemento->pai->dir) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO) {	
		
			enum cor cor_topo = elemento->pai->cor;

			rotacao_simples_esquerda(raiz, elemento->pai);

			elemento->pai->pai->cor = cor_topo;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			retira_duplo_preto(raiz, elemento);

			return;
		}

		// #Caso 6b
		if(cor(elemento->pai->esq) == PRETO &&
			cor(irmao(elemento)->esq) == VERMELHO) {
		
			enum cor cor_topo = elemento->pai->cor;

			rotacao_simples_direita(raiz, elemento->pai);

			elemento->pai->pai->cor = cor_topo;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->esq->cor = PRETO;
			retira_duplo_preto(raiz, elemento);

			return;
		}
		
		/*
		if(eh_raiz(elemento)){
			elemento->cor = PRETO;
			if(elemento == no_null)
				*raiz = NULL;
			return;
		}
		//caso 2
		if( cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO)
		{
			
			if(eh_filho_esquerdo(elemento)){
				rotacao_simples_esquerda(raiz, elemento->pai);
			}
			else{
				rotacao_simples_direita(raiz, elemento->pai);	
			}
			elemento->pai->pai->cor = PRETO;
			elemento->pai->cor = VERMELHO;

			reajustar(raiz, elemento);
			return;
		}
		//caso 3
		if( cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == DUPLO_PRETO){

			retira_duplo_preto(raiz, no_null);
			//Verificar e remover o no_null
			//Chamada recursiva para eliminar o duplo preto do elemento P
			return;
		}	

		//caso 4
		if(  cor(elemento->pai) == VERMELHO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == PRETO &&
			cor(irmao(elemento)->dir) == PRETO){

			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->pai->esq->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			retira_duplo_preto(raiz, elemento->pai->pai->esq);
			//Verificar e remover o no_null
			//Chamada recursiva para eliminar o duplo preto do elemento P
			return;
		}

		//Caso 5a(direita):
		if( cor(elemento->pai) == VERMELHO || cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO){

			//rotacao_dupla_direita(raiz, elemento->pai);
			rotacao_simples_esquerda(raiz, elemento->pai->pai->esq);
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->pai->esq->cor = PRETO;
			elemento->pai->pai->dir = elemento->pai->pai;
			elemento->pai->pai = elemento->pai->pai->esq;
			return;
		}

		//caso 5b(esquerda):
		if( cor(elemento->pai) == VERMELHO || cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->dir) == VERMELHO &&
			cor(irmao(elemento)->esq) == PRETO){

			rotacao_dupla_direita(raiz, elemento->pai);
			//rotacao_simples_esquerda(raiz, elemento->pai->pai->dir);
			elemento->pai->pai->cor = VERMELHO;
			elemento->pai->pai->dir->cor = PRETO;
			elemento->pai->pai->esq = elemento->pai->pai;
			elemento->pai->pai = elemento->pai->pai->dir;
			return;
		}

		//caso 6a(direita):
		if( cor(elemento->pai) == VERMELHO || cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->dir) == VERMELHO &&
			cor(irmao(elemento)->esq) == PRETO){
			
			rotacao_simples_esquerda(raiz, elemento->pai);
			//rotacao_simples_direita(raiz, elemento->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			return;
		}

		//caso 6b(esquerda):
		if( cor(elemento->pai) == VERMELHO || cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == PRETO &&
			cor(irmao(elemento)->esq) == VERMELHO &&
			cor(irmao(elemento)->dir) == PRETO){
			
			rotacao_simples_direita(raiz, elemento->pai);
			//rotacao_simples_esquerda(raiz, elemento->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->esq->cor = PRETO;
			return;
		
		}
		*/
	}
		
}

void retira_duplo_preto(arvore *raiz, arvore elemento){
	if(elemento == no_null){
		if(eh_filho_esquerdo(elemento)){
			elemento->pai->esq = NULL;
        }
	    else{
            elemento->pai->dir = NULL;
        }
    }
	else{
		elemento->cor = PRETO;
    }           
}
