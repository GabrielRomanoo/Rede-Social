# Rede Social
Projeto de uma rede social com diversas funcionalidades

## Integrantes
- Gabriel Romano
- Jaime Mathias
- Daniel Bou

## Funcionalidades

- **Carregar usuários**: `void load_users(avl_tree * t, char * filename)`. A configuração
inicial da rede social é carregada a partir de um arquivo texto
(filename) onde cada usuário é descrito por duas linhas. A primeira linha
contém o nome de usuário, seu nome completo e sexo ('m' ou 'f'), separados por
um ; (ponto e vírgula). A segunda linha contém os nomes de usuários de seus
amigos, também separados por um ; (ponto e vírgula).

- **Adicionar um novo usuário**: `bool add_new_user(avl_tree * t, avl_info x)`. Acrescenta um novo
usuário à rede social. A lista de amigos do usuário é inicialmente vazia.
Para que a operação seja realizada, o nome de usuário deve ser único, ou seja, não
pode haver nenhum usuário cadastrado com esse nome. A função devolve true
para indicar o sucesso da operação; ou false, para indicar a falha.

- **Adicionar um amigo**: `bool add_friend(avl_tree t, char * username, char *
friendname)`. Acrescenta um amigo (friendname) a lista de amigos de um
usuário (username). A função devolve true para
indicar o sucesso da operação; ou false, para indicar uma falha.

- **Listar usuários**: `void list_users(avl_tree t)`. Gera uma listagem em ordem alfabética
pelo nome de usuário de todos os usuários da rede (imprime o nome de usuário,
nome completo e sexo);

- **Listar amigos**: `bool list_friends(avl_tree t, char * username)`. Mostra o nome
de usuário, nome completo e sexo de todos os amigos de um usuário
(username). A função devolve true se o usuário (username) estiver
cadastrado na rede; ou false, caso contrário;

- **Remover usuário**: `bool remove_user(avl_tree * t, char * username)`. Remove o
usuário (username) da rede social e também da lista de amigos dos demais
usuários. A função deve verificar se o usuário existe para fazer a operação e deve
devolver true para indicar seu sucesso; ou false, para indicar a falha.

- **Finalizar o programa**: `void save_users(avl_tree t)`. Grava em um arquivo texto as
informações da rede, no mesmo formato descrito no item a).
