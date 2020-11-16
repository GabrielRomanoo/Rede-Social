/* listaord.c
 * Implementação das operações sobre o TAD lista ordenada.
 * 24/04/2019
 */

#include "listaord.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lst_init(lista * l)
{
    *l = NULL;
}

void lst_ins(lista * l, char val[])
{
    lista n;
    if ((n = (lista) malloc(sizeof(struct lst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    strcpy(n->dado, val);
    //n->dado = val;
    if (*l == NULL || strcmp(val, (*l)->dado) < 0) {
       n->prox = *l;
       *l = n;
    }
    else {
        lista p = *l;
        while (p->prox != NULL && strcmp(val, (*l)->dado) >= 0) {
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
    }
}

void lst_print(lista l)
{
    printf("[ ");
    while (l != NULL) {
        printf("%s,", l->dado);
        l = l->prox;
    }
    printf("\b ]\n");
}

void lst_kill(lista * l)
{
	lista p;
	while (*l != NULL) {
		p = *l;
		*l = (*l)->prox;
		free(p);
	}
}

bool lst_find(lista l, char x[])
{
    while (l != NULL && strcmp(l->dado,x) != 0) {
        l = l->prox;
    }
    if (l != NULL && strcmp(l->dado,x) == 0) {
        return true;
    }
    return false;
}

bool lst_rem(lista * l, char x[])
{
    if (*l == NULL || strcmp(x, (*l)->dado) < 0) {
        return false;
    }
    else {
        lista p = *l;
        if (strcmp((*l)->dado,x) == 0) {
            (*l) = p->prox;
            free(p);
            return true;
        }
        else {
            while (p->prox != NULL && strcmp(x, p->prox->dado) > 0) {
                p = p->prox;
            }
            if (p->prox != NULL && strcmp((*l)->prox->dado,x) == 0) {
                lista n = p->prox;
                p->prox = n->prox;
                free(n);
                return true;
            }
        }
        return false;
    }
}
