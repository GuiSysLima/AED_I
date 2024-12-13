#ifndef BST_H
#define BST_H
#include <stdio.h>

typedef struct lista{
    int num;
}tipo_dado;

typedef struct no{
    tipo_dado *dado;
    struct no * esq;
    struct no * dir;
    struct no * pai;
}no;


typedef no * arvore;

arvore remover (arvore raiz, int valor);
arvore adicionar(arvore raiz, tipo_dado *valor);

int maior(arvore raiz);
int altura(arvore raiz);

arvore buscar(arvore raiz, int valor);

void in_order(arvore raiz);
void pre_order(arvore raiz);
void post_order(arvore raiz);
void inicializar(arvore *raiz);

int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);

tipo_dado* ler_dados();

#endif
