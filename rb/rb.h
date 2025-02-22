#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef int tipo_dado;

typedef struct no_rb {
	tipo_dado dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
} no_rb;


typedef no_rb * arvore;

void inicializar(arvore *raiz);
void adicionar(int valor, arvore *raiz);
void remover(int valor, arvore *raiz);

int altura(arvore raiz);
int maior(int a, int b);

int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);

void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

void imprimir_elemento(arvore raiz);
void imprimir(arvore raiz);

void ajustar(arvore *raiz, arvore elemento);
void reajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_direita(arvore *raiz, arvore pivo);

enum cor cor(arvore elemento);


void rb_transplant(arvore t, arvore u, arvore v);
arvore nova_arvore(int data);

int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento);

arvore irmao(arvore elemento);
arvore tio(arvore elemento);

void retira_duplo_preto(arvore *raiz, arvore elemento);

#endif