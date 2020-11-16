/* trabalho1.c
 *
 * Programa que simula uma rede social e armazena as informações
 * a respeito de seus usuários em uma árvore AVL.
 *
 * Daniel Bou de Souza (Ciência da Computação)
 * Gabriel Romano Godoi Pereira (Ciência da Computação)
 * Jaime Mathias de Lara Bueno (Ciência da Computação)
 *
 * Disciplina: Estrutura de Dados II
 *
 *17/10/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "redesocial.h"

int main()
{
    avl_tree t = NULL;
    avl_info x;
    char filename[100], nome[21];
    int op;

    printf("Informe o nome do arquivo: ");
    scanf(" %99[^\n]", filename);
    //fflush(stdin);

    load_users(&t, filename);

    do {
        printf("\n\n\tREDE SOCIAL\n");
        printf("<1> Imprimir Usuarios\n");
        printf("<2> Remover Usuario\n");
        printf("<3> Adicionar Usuario\n");
        printf("<4> Adicionar Amigo\n");
        printf("<5> Imprimir Amigos\n");
        printf("<6> Carregar Usuarios\n");
        printf("<0> Sair do programa\n");
        printf("Opcao: ");
        scanf(" %d", &op);
        //fflush(stdin);

        switch (op) {
            case 1:
                printf("\n\nLista de usuarios: \n");
                printf("--------------------------------\n");
                list_users(t);
                break;

            case 2:
                printf("\n\nInforme o nome do usuario: ");
                scanf(" %21[^\n]", nome);
                //fflush(stdin);
                if (remove_user(&t, nome) == true) {
                    printf("\n\nUsuario removido com sucesso!\n");
                }
                else {
                    printf("\n\nFalha na remocao do usuario!\n");
                }
                break;

            case 3:
                printf("\n\nInforme o nome completo do usuario: ");
                scanf(" %51[^\n]", x.nome_completo);
                //fflush(stdin);
                printf("\n\nInforme o nome do usuario: ");
                scanf(" %21[^\n]", x.usuario);
                //fflush(stdin);
                printf("\n\nInforme o sexo do usuario: ");
                scanf(" %c", &x.sexo);
                //fflush(stdin);
                if (add_new_user(&t,x) == true) {
                    printf("\n\nUsuario adicionado com sucesso!\n");
                }
                else {
                    printf("\n\nFalha na adicao do usuario!\n");
                }
                break;

            case 4:
                printf("\n\nInforme o nome do usuario: ");
                scanf(" %21[^\n]", x.usuario);
                //fflush(stdin);
                printf("\n\nInforme o nome do amigo: ");
                scanf(" %21[^\n]", nome);
                //fflush(stdin);
                if (add_friend(&t,x.usuario,nome) == true) {
                    printf("\n\nAmigo adicionado com sucesso!\n");
                }
                else {
                    printf("\n\nFalha na adicao de amizade!\n");
                }
                break;

            case 5:
                printf("\n\nInforme o nome do usuario: ");
                scanf(" %21[^\n]", nome);
                //fflush(stdin);
                printf("\n\nLista de Amigos: \n");
                printf("--------------------------------\n");
                if (list_friends(t,nome) == false) {
                    printf("\n\nUsuario nao cadastrado na rede!\n");
                }
                break;

            case 6:
                save_users(t);
                printf("\n\nUsuarios carregados!\n");
                break;

            case 0:
                break;

            default:
                printf("\nErro: opcao invalida!\n");
        }
    } while (op != 0);
    return 0;
}
