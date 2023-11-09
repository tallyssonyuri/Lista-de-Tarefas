#ifndef PROJ_H
#define PROJ_H

typedef struct { /* Define uma estrutura para representar uma tarefa */
  char descricao[300]; /* Um array de tamanho 300 */
  int prioridade; /* Um inteiro */ 
  char categoria[100]; /* Um array de tamanho 100 */
} Tarefa; /* Nome da estrutura */

typedef struct { /* Define uma estrutura para representar uma lista de tarefas */
  Tarefa tarefas[100]; /* Um array de tamanho 100 */
  int qtd; /* Quantidade de tarefas na lista */
} ListaDeTarefas; /* Nome da estrutura */

/*  Declaração das funções que serão usadas no programa. */
int cadastrarTarefas(ListaDeTarefas *lt);
int deletarTarefas(ListaDeTarefas *lt);
int listarTarefas(ListaDeTarefas lt);

void printMenu();
int salvarTarefas(ListaDeTarefas *lt, char *arquivo);
int carregarTarefas(ListaDeTarefas *lt, char *arquivo);

#endif
