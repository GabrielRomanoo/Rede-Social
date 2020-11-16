/* listaord.h
 * Defini��o do TAD para representar uma lista ordenada implementada
 * de forma encadeada e prot�tipo das opera��es sobre esse TAD.
 * 24/04/2019
 */

#ifndef _LISTAORD_H
#define _LISTAORD_H
#include <stdbool.h>

typedef struct lst_no * lista;
struct lst_no {
    char dado[50];
    lista prox;
};

/* inicializa a lista ordenada */
void lst_init(lista *);

/* insere um novo elemento na lista ordenada */
void lst_ins(lista *, char[]);

/* imprime os elementos da lista ordenada */
void lst_print(lista);

/* destr�i uma lista ordenada */
void lst_kill(lista *);

/* procura um elemento e devolve true para
indicar o sucesso da opera��o, ou false, caso contr�rio */
bool lst_find(lista l, char[]);

/* remove um elemento da lista ordenada */
bool lst_rem(lista *, char[]);

#endif
