#ifndef AVL_H
#define AVL_H
#include <stdio.h>

typedef int tipo_dado;

typedef struct no{
	tipo_dado dado;
	int fb;
    int altura;
	struct no *esq, *dir;
}no;

typedef no* arvore;


void inicializar(arvore *raiz);

arvore adicionar(int valor, arvore raiz, int *cresceu);
arvore buscar(arvore raiz, int valor);
arvore remover(int valor, arvore raiz, int *diminuiu);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);
arvore carregar_arquivo(char *nome, arvore carregar_lista);

int maior(int a, int b);
int altura(arvore raiz);
int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);


void imprimir(arvore raiz);
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

tipo_dado * ler_dados();

void imprimir_elemento(arvore raiz);

int fatorBalanceamento(arvore raiz);
int contarNo(arvore raiz);

void salvar_auxiliar(arvore raiz, FILE *arq);
void salvar_arquivo(char *nome, arvore salvar_lista);
void pre_order(arvore raiz);
void in_order(arvore raiz);
void pos_order(arvore raiz);

int contarNos(arvore raiz);

void imprimirTest(arvore raiz, int espaco);

int alturaNoh(arvore raiz);
int alturaArvore(arvore raiz);
int contarNos(arvore raiz);

#endif
