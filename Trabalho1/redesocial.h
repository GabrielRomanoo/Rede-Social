/* redesocial.h
 *
 * Protótipo das funções de redesocial.c para representar uma rede
 * social em uma árvore AVL.
 *
 * Daniel Bou de Souza (Ciência da Computação)
 * Gabriel Romano Godoi Pereira (Ciência da Computação)
 * Jaime Mathias de Lara Bueno (Ciência da Computação)
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

// Definição da estrutura de dados
typedef struct {
    char usuario[21]; // nome de usuário
    char nome_completo[51]; // nome completo
    char sexo;
    lista amigos; // lista encadeada ordenada dos amigos
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/* Função que carrega os usuários */
void load_users(avl_tree * t, char * filename);

/* Função que adiciona um novo usuário e devolve true para
indicar o sucesso da operação, ou false, caso contrário.
Restrição: avl_tree *t precisa estar inicializada. */
bool add_new_user(avl_tree * t, avl_info x);

/* Função auxiliar de add_new_user que adiciona um novo usuário
e altera bool *h para true para indicar o sucesso da operação, ou false,
caso contrário.
Restrição: avl_tree * t precisa estar inicializada. */
bool add_new_user2(avl_tree * t, avl_info x, bool *h);

/* Função que procura um usuario e e devolve true para
indicar o sucesso da operação, ou false, caso contrário */
bool search_user(avl_tree t, char nome[]);

/* Faz uma rotação para a direita na árvore AVL t.  */
void rotacao_dir(avl_tree * t);

/* Faz uma rotação para a esquerda na árvore AVL t.  */
void rotacao_esq(avl_tree *);

/*
 * Função que lista todos os usuários da rede social, de
 * forma ERD, subávore esquerda, raiz e, por fim, subárvore
 * direita.
*/
void list_users(avl_tree t);

/*
 * Função que adiciona um usuario como amigo e devolve true para
 * indicar o sucesso da operação, ou false, caso contrário
 * Restrição: avl_tree * t precisa estar inicializada.
*/
bool add_friend(avl_tree * t, char * username, char * friendname);

/*
 * Função que procura se o usuário (char x[]) encontra-se na árvore.
 * Devolve o endereço do nó para indicar o sucesso da operação, ou NULL,
 * caso contrário.
 * Restrição: avl_tree * t precisa estar inicializada.
 */
avl_tree find_user(avl_tree t, char x[]);

/* Função que remove os espaços de uma string */
char * remove_espacos( char * out, const char * in );

/*
 * Função que imprime todos os amigos de um usuario (char *username).
 * A função devolve true se o usuário (char *username) estiver
 * cadastrado na rede; ou false, caso contrário.
 * Restrição: avl_tree * t precisa estar inicializada.
 */
bool list_friends(avl_tree t, char * username);

/*
 * Função auxiliar de list_friends que imprime os dados de um usuario
 * especifico (char *username). Devolve 2 para indicar sucesso ou 0 se
 * o usuario não for encontrado.
 * Restrição: avl_tree * t precisa estar inicializada.
 */
int imprimir_user_especifico(avl_tree t, char * username);


/*
 * Função que remove o usuário (username) da avl *t e também da lista de amigos dos demais
 * nós. A função devolve true para indicar sucesso, ou false, caso constrário.
 * Restrição: avl_tree * t precisa estar inicializada.
*/

bool remove_user(avl_tree * t, char * username);

/*
 * Se a palavra x está contida na árvore AVL t, x é
 * removida de t, h sinaliza uma diminuição da altura
 * de t e a função devolve verdadeiro; caso contrário,
 * nada é feito e a função devolve falso.
 * Restrição: avl_tree * t precisa estar inicializada.
 */
bool delete(avl_tree * t, char * x, bool * h);

/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore esquerda e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);

/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore direita e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);

/*
 * Função que atualiza as informações do usuários
 * da rede social, que estão na avl_tree t, em
 * um arquivo de texto na forma de escrita ERD.
*/
void save_users(avl_tree t);

/*
 * Função que auxilia na escrita das informações dos
 * usuários da rede social, que estão na avl_tree t,
 * no arquivo arq de forma recursiva.
*/
void save_users_aux(avl_tree t, FILE * arq);

#endif
