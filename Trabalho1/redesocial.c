/* redesocial.c
 *
 * Implementação dos protótipos de redesocial.h para representar uma rede
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

#include "redesocial.h"
#include "listaord.h"

void load_users(avl_tree * t, char * filename) {

    FILE * arq;
    char linha[200];
    bool controle = true;

    avl_info dadosDoArquivo;
    const char s[2] = ";";
    char *token;
    char out[50];

    nome_arq = filename;

    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }
    else {
        while(fgets(linha, 1000, arq) != NULL) {
            if (controle) {
                token = strtok(linha, s);
                int aux = 0;
                while (token != NULL) {
                    if (aux == 0) {
                        strcpy(dadosDoArquivo.usuario, token);
                    }
                    else if (aux == 1) {
                        strcpy(dadosDoArquivo.nome_completo, token);
                    }
                    else if (aux == 2) {
                        dadosDoArquivo.sexo = token[0];
                    }
                    aux++;
                    token = strtok(NULL, s);
                }
            }
            else {
                add_new_user(t, dadosDoArquivo);
            }
            controle = !controle;
        }

        rewind(arq);
        controle = true;

        while(fgets(linha, 1000, arq) != NULL) {
            token = strtok(linha, s);
            if (controle) {
                int aux = 0;
                while (token != NULL) {
                    if (aux == 0) {
                        strcpy(dadosDoArquivo.usuario, token);
                    }
                    else if (aux == 1) {
                        strcpy(dadosDoArquivo.nome_completo, token);
                    }
                    else if (aux == 2) {
                        dadosDoArquivo.sexo = token[0];
                    }
                    aux++;
                    token = strtok(NULL, s);
                }
            }
            else {
                while(token != NULL) {
                    for (int i = 0; i < strlen(token); i++) {
                        if (token[i] == '\n') {
                            token[i] = '\0';
                        }
                    }
                    remove_espacos(out, token);
                    add_friend(t, dadosDoArquivo.usuario, out);
                    token = strtok(NULL, s);
                }
            }
            controle = !controle;
        }
    }
    fclose(arq);
}

bool add_new_user(avl_tree * t, avl_info x) {

    bool h = false;
    add_new_user2(t, x, &h);
    return h;
}

bool add_new_user2(avl_tree * t, avl_info x, bool *h) {

    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        strcpy((*t)->dado.usuario,x.usuario);
        strcpy((*t)->dado.nome_completo,x.nome_completo);
        (*t)->dado.sexo = x.sexo;
        lst_init(&(*t)->dado.amigos);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
        *h = true;
        return true;
    }
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) < 0) { // Inserir a esquerda
        if (add_new_user2(&(*t)->esq, x, h)) { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        return false;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    (*t)->bal = 0;
                    return false;
                    break;
            }
        }
    }
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) > 0) { // Inserir a direita
        if (add_new_user2(&(*t)->dir, x, h)) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                         return false;
                         break;
                case 0 : (*t)->bal = 1;
                         break;
                case 1: // Rebalanceamento
                    if ((*t)->dir->bal == 1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }
                    else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                    }
                    (*t)->bal = 0;
                    return false;
                    break;
            }
        }
    }
    return false; // a chave já está na árvore


}

void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}

void list_users(avl_tree t) {
    if (t != NULL) {
        list_users(t->esq);  // visita a subárvore esquerda
        printf("Usuario: %s\n", t->dado.usuario); // processa a raiz
        printf("Nome completo: %s\n", t->dado.nome_completo);
        printf("Sexo: %c\n", t->dado.sexo);
        printf("Amigos: ");
        lst_print(t->dado.amigos);
        printf("--------------------------------\n");
        list_users(t->dir);  // visita a subárvore direita
    }
}

bool list_friends(avl_tree t, char * username) {
    if (find_user(t, username) != NULL) {
        avl_tree aux = find_user(t, username);
        lista l = aux->dado.amigos;
        while (l != NULL) {
            imprimir_user_especifico(t, l->dado);
            l = l->prox;
        }
        return true;
    }
    return false;
}

int imprimir_user_especifico(avl_tree t, char * username) {
    if (t != NULL) {
        if (strcmp(username, t->dado.usuario) < 0) {
            imprimir_user_especifico(t->esq, username);  // visita a subárvore esquerda
        } else if (strcmp(username, t->dado.usuario) > 0) {
            imprimir_user_especifico(t->dir, username);  // visita a subárvore direita
        } else {
            printf("Usuario: %s\n", t->dado.usuario);
            printf("Nome completo: %s\n", t->dado.nome_completo);
            printf("Sexo: %c\n", t->dado.sexo);
            printf("--------------------------------\n");
            return 0;
        }
    }
    return 2;
}

bool add_friend(avl_tree * t, char * username, char * friendname) {
    if (find_user(*t, username) != NULL && find_user(*t, friendname) != NULL) {
        avl_tree auxUser = find_user(*t, username);
        avl_tree auxFriend = find_user(*t, friendname);

        if (!lst_find(auxUser->dado.amigos, friendname)) {
            lst_ins(&auxUser->dado.amigos, friendname);
            if (!lst_find(auxFriend->dado.amigos, username)) {
                lst_ins(&auxFriend->dado.amigos, username);
            }
            return true;
        }
    }
    return false;
}

avl_tree find_user(avl_tree t, char x []) {
    if (t == NULL){
        return NULL;
    }
    else if (strcmp(x, t->dado.usuario) == 0) {
        return t;
    } else if (strcmp(x, t->dado.usuario) < 0) {
        return find_user(t->esq, x);
    } else return find_user(t->dir, x);

}

char * remove_espacos( char * out, const char * in ) {
    const char * p = in;
    int i = 0;

    while(*p) {
        if (!isspace(*p))
            out[i++] = *p;
        p++;
    }
    out[i] = '\0';
    return out;
}

bool remove_user(avl_tree * t, char * username) {

    bool h;
    avl_tree remUser;
    avl_tree remDosAmigos;
    lista l;
    if (find_user(*t, username)) {
        remUser = find_user(*t, username);
        l = remUser->dado.amigos;
        while (l != NULL) {
            remDosAmigos = find_user(*t, l->dado);
            lst_rem(&remDosAmigos->dado.amigos, remUser->dado.usuario);
            l = l->prox;
        }
        delete(t, username, &h);
        return true;
    }
        return false;
}

bool delete(avl_tree * t, char * x, bool * h) {

    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(x, (*t)->dado.usuario) == 0) { // a chave está neste nó
        p = *t;
        lst_kill(&p->dado.amigos);
        if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) { // nó com uma única subárvore esquerda
            *t = p->esq;
            *h = true;
        }
        else { // nó com duas subávores
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.usuario) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
}

void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotação simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    }
}

void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    }
}

avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}

void save_users(avl_tree t) {
    FILE * arq;
    if ((arq = fopen(nome_arq, "w")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", nome_arq);
        exit(1);
    }
    save_users_aux(t, arq);
    fclose(arq);
}

void save_users_aux(avl_tree t, FILE * arq) {
    if (t != NULL) {
        bool controle = true; // Váriavel booleana que serve para saber se tem mais de um amigp
        // Escrevendo as informações da raiz no arquivo
        fprintf(arq, "%s;%s;%c\n", t->dado.usuario, t->dado.nome_completo, t->dado.sexo);
        lista p = t->dado.amigos;
        while(p != NULL) {
            if (controle != true) {
                fprintf(arq, ";%s", p->dado);
            }
            else {
                fprintf(arq, "%s", p->dado);
                controle = false;
            }
            p = p->prox;
        }
        fprintf(arq, "\n");
        save_users_aux(t->esq, arq); // Escreve a subárvore esquerda
        save_users_aux(t->dir, arq); // Por ultimo escreve a subárvore direita
    }
}
