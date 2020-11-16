/* redesocial.h
 *
 * Prot�tipo das fun��es de redesocial.c para representar uma rede
 * social em uma �rvore AVL.
 *
 * Daniel Bou de Souza (Ci�ncia da Computa��o)
 * Gabriel Romano Godoi Pereira (Ci�ncia da Computa��o)
 * Jaime Mathias de Lara Bueno (Ci�ncia da Computa��o)
 *
 * Disciplina: Estrutura de Dados II
 *
 *17/10/2019
*/

#ifndef _REDESCOIAL_H
#define _REDESOCIAL_H

#include "listaord.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * nome_arq;

// Defini��o da estrutura de dados
typedef struct {
    char usuario[21]; // nome de usu�rio
    char nome_completo[51]; // nome completo
    char sexo;
    lista amigos; // lista encadeada ordenada dos amigos
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do n�
};

/* Fun��o que carrega os usu�rios */
void load_users(avl_tree * t, char * filename);

/* Fun��o que adiciona um novo usu�rio e devolve true para
indicar o sucesso da opera��o, ou false, caso contr�rio.
Restri��o: avl_tree *t precisa estar inicializada. */
bool add_new_user(avl_tree * t, avl_info x);

/* Fun��o auxiliar de add_new_user que adiciona um novo usu�rio
e altera bool *h para true para indicar o sucesso da opera��o, ou false,
caso contr�rio.
Restri��o: avl_tree * t precisa estar inicializada. */
bool add_new_user2(avl_tree * t, avl_info x, bool *h);

/* Fun��o que procura um usuario e e devolve true para
indicar o sucesso da opera��o, ou false, caso contr�rio */
bool search_user(avl_tree t, char nome[]);

/* Faz uma rota��o para a direita na �rvore AVL t.  */
void rotacao_dir(avl_tree * t);

/* Faz uma rota��o para a esquerda na �rvore AVL t.  */
void rotacao_esq(avl_tree *);

/*
 * Fun��o que lista todos os usu�rios da rede social, de
 * forma ERD, sub�vore esquerda, raiz e, por fim, sub�rvore
 * direita.
*/
void list_users(avl_tree t);

/*
 * Fun��o que adiciona um usuario como amigo e devolve true para
 * indicar o sucesso da opera��o, ou false, caso contr�rio
 * Restri��o: avl_tree * t precisa estar inicializada.
*/
bool add_friend(avl_tree * t, char * username, char * friendname);

/*
 * Fun��o que procura se o usu�rio (char x[]) encontra-se na �rvore.
 * Devolve o endere�o do n� para indicar o sucesso da opera��o, ou NULL,
 * caso contr�rio.
 * Restri��o: avl_tree * t precisa estar inicializada.
 */
avl_tree find_user(avl_tree t, char x[]);

/* Fun��o que remove os espa�os de uma string */
char * remove_espacos( char * out, const char * in );

/*
 * Fun��o que imprime todos os amigos de um usuario (char *username).
 * A fun��o devolve true se o usu�rio (char *username) estiver
 * cadastrado na rede; ou false, caso contr�rio.
 * Restri��o: avl_tree * t precisa estar inicializada.
 */
bool list_friends(avl_tree t, char * username);

/*
 * Fun��o auxiliar de list_friends que imprime os dados de um usuario
 * especifico (char *username). Devolve 2 para indicar sucesso ou 0 se
 * o usuario n�o for encontrado.
 * Restri��o: avl_tree * t precisa estar inicializada.
 */
int imprimir_user_especifico(avl_tree t, char * username);


/*
 * Fun��o que remove o usu�rio (username) da avl *t e tamb�m da lista de amigos dos demais
 * n�s. A fun��o devolve true para indicar sucesso, ou false, caso constr�rio.
 * Restri��o: avl_tree * t precisa estar inicializada.
*/

bool remove_user(avl_tree * t, char * username);

/*
 * Se a palavra x est� contida na �rvore AVL t, x �
 * removida de t, h sinaliza uma diminui��o da altura
 * de t e a fun��o devolve verdadeiro; caso contr�rio,
 * nada � feito e a fun��o devolve falso.
 * Restri��o: avl_tree * t precisa estar inicializada.
 */
bool delete(avl_tree * t, char * x, bool * h);

/*
 * Faz o balanceamento da �rvore AVL t ap�s uma remo��o
 * em sua sub�rvore esquerda e sinaliza se houve uma
 * dimui��o da altura dessa sub�rvore atrav�s de h.
 */
void balance_esq(avl_tree * t, bool * h);

/*
 * Faz o balanceamento da �rvore AVL t ap�s uma remo��o
 * em sua sub�rvore direita e sinaliza se houve uma
 * dimui��o da altura dessa sub�rvore atrav�s de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o n� que cont�m o menor
 * valor na �rvore AVL t e sinaliza atrav�s de h se
 * houve uma diminui��o da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);

/*
 * Fun��o que atualiza as informa��es do usu�rios
 * da rede social, que est�o na avl_tree t, em
 * um arquivo de texto na forma de escrita ERD.
*/
void save_users(avl_tree t);

/*
 * Fun��o que auxilia na escrita das informa��es dos
 * usu�rios da rede social, que est�o na avl_tree t,
 * no arquivo arq de forma recursiva.
*/
void save_users_aux(avl_tree t, FILE * arq);

#endif
