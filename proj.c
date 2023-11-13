#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj.h"

int cadastrarTarefas(ListaDeTarefas *lt){ /* Função para cadastrar uma tarefa. Recebe um ponteiro para uma lista de tarefas */
  if(lt->qtd >= 100) { /* Não será possivel cadastrar novas tarefas a partir de 100, pois é o maximo do struct declarado */
    printf("A lista de tarefas está cheia.\n\n\n");
    return 1;
  }

  printf("Digite a descricao da tarefa: ");
  fgets(lt->tarefas[lt->qtd].descricao, 300, stdin); /* Leitura da descricao informada pelo usuario para ser adicionada no struct informado */
  lt->tarefas[lt->qtd].descricao[strcspn(lt->tarefas[lt->qtd].descricao, "\n")] = 0; /* Remove o caractere de nova linha do final da descrição. Assim não irá atrapalhar na execução do próximo item */
  while ((getchar()) != '\n'); /* Limpa o buffer de entrada. */

  printf("Digite a prioridade da tarefa (Sugerimos definir valores de 0-10): "); /*Leitura da prioridade da tarefa*/
  scanf("%d", &lt->tarefas[lt->qtd].prioridade);
  while ((getchar()) != '\n'); 

  printf("Digite a categoria da tarefa: "); /* Leitura da categoria da tarefa*/
  fgets(lt->tarefas[lt->qtd].categoria, 100, stdin);
  lt->tarefas[lt->qtd].categoria[strcspn(lt->tarefas[lt->qtd].categoria, "\n")] = 0;
  while ((getchar()) != '\n');

  printf("Digite o estado da tarefa (0 para completo, 1 para em andamento, 2 para não iniciado): "); /*Leitura do estado da tarefa */
  int estado;
  scanf("%d", &estado);
  lt->tarefas[lt->qtd].estado = estado;
  if (estado == 0) {
    strcpy(lt->tarefas[lt->qtd].estadoStr, "Completo");
  } else if (estado == 1) {
    strcpy(lt->tarefas[lt->qtd].estadoStr, "Em andamento");
  } else if (estado == 2) {
    strcpy(lt->tarefas[lt->qtd].estadoStr, "Não iniciado");
  }
  while ((getchar()) != '\n');

  lt->qtd++; /* Incrementa a quantidade de tarefas na lista. */

  printf("\nTarefa cadastrada!\n\n\n");
  return 0;
}

int deletarTarefas(ListaDeTarefas *lt){ /* Função para deletar uma tarefa. Recebe um ponteiro para uma lista de tarefas. */

  if(lt->qtd == 0) { /*  Verifica se a lista de tarefas está vazia, pois se estiver será informado ao usuario */
    printf("Não há tarefas para deletar.\n\n");
    return 1;
  }
  int indice; /* Variável para armazenar o índice da tarefa a ser deletada. */
  printf("Digite o índice da tarefa a ser deletada: ");
  scanf("%d", &indice);
  printf("Tarefa %d foi deletada com sucesso!\n\n", indice);

  if(index < 0 || indice >= lt->qtd) { /* Verifica se o índice é válido. */
    printf("Índice inválido.\n\n");
    return 1;
  }

  for(int i = indice; i < lt->qtd - 1; i++) { /* Loop para mover todas as tarefas após a tarefa deletada uma posição para trás no array. */
    lt->tarefas[i] = lt->tarefas[i + 1];
  }

  lt->qtd--; /* Decrementa a quantidade de tarefas na lista. */

  return 0;
}

int listarTarefas(ListaDeTarefas lt){ /* Função para listar as tarefas. Recebe uma lista de tarefas. */

  if(lt.qtd == 0) { /*  Verifica se a lista de tarefas está vazia, pois se estiver será informado ao usuario */
    printf("Não há tarefas para listar.\n\n");
    return 1;
  }
  for(int i = 0; i < lt.qtd; i++) { /* Loop para imprimir todas as tarefas na lista. */
    printf("Tarefa %d\n", i);
    printf("Descricao: %s\n", lt.tarefas[i].descricao);
    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);   
    printf("Categoria: %s\n", lt.tarefas[i].categoria);
    printf("Estado: %s\n", lt.tarefas[i].estadoStr);
    printf("\n");
  }

  return 0;
}

void printMenu(){ /* Função para imprimir o menu de opções. */
  printf("1. Adicionar tarefa\n");
  printf("2. Deletar tarefa\n");
  printf("3. Listar tarefas\n");
  printf("4. Sair\n\n");
}

int salvarTarefas(ListaDeTarefas *lt, char *arquivo){
  FILE *fp = fopen(arquivo, "wb"); /* Função para salvar as tarefas em um arquivo. Recebe um ponteiro para uma lista de tarefas e um nome de arquivo. */
  if(fp == NULL) {
    printf("Não foi possível abrir o arquivo para escrita.\n");
    return 1;
  }

  fwrite(&lt->qtd, sizeof(int), 1, fp);
  fwrite(lt->tarefas, sizeof(Tarefa), lt->qtd, fp);

  fclose(fp);

  return 0;
}

int carregarTarefas(ListaDeTarefas *lt, char *arquivo){ /* Função para carregar as tarefas de um arquivo. Recebe um ponteiro para uma lista de tarefas e um nome de arquivo. */
  FILE *fp = fopen(arquivo, "rb");
  if(fp == NULL) {
    printf("Não foi possível abrir o arquivo para leitura pois:\n\n");
    return 1;
  }

  fread(&lt->qtd, sizeof(int), 1, fp);
  fread(lt->tarefas, sizeof(Tarefa), lt->qtd, fp);

  fclose(fp);

  return 0;
}

/*---------------------------------*/

int alterarTarefas(ListaDeTarefas *lt){
  if(lt->qtd == 0) {
    printf("Não há tarefas para alterar.\n\n");
    return 1;
  }
  int indice;
  printf("Digite o número da tarefa a ser alterada: ");
  scanf("%d", &indice);
  while ((getchar()) != '\n');

  if(indice < 0 || indice >= lt->qtd) {
    printf("\nÍndice inválido.\n\n");
    return 1;
  }

  printf("\nEscolha o campo a ser alterado:\n\n");
  printf("1. Descrição\n");
  printf("2. Prioridade\n");
  printf("3. Categoria\n");
  printf("4. Estado\n\n");

  int opcao;
  scanf("%d", &opcao);
  while ((getchar()) != '\n');

  switch(opcao) {
    case 1:
      printf("\nDigite a nova descrição da tarefa: ");
      fgets(lt->tarefas[indice].descricao, 300, stdin);
      lt->tarefas[indice].descricao[strcspn(lt->tarefas[indice].descricao, "\n")] = 0;
      while ((getchar()) != '\n');
      printf("\nDescrição alterada!\n\n");
      break;
    
    case 2:
      printf("Digite a nova prioridade da tarefa (Sugerimos definir valores de 0-10): ");
      scanf("%d", &lt->tarefas[indice].prioridade);
      while ((getchar()) != '\n');
      printf("\nPrioridade alterada!\n\n");
      break;
    
    case 3:
      printf("Digite a nova categoria da tarefa: ");
      fgets(lt->tarefas[indice].categoria, 100, stdin);
      lt->tarefas[indice].categoria[strcspn(lt->tarefas[indice].categoria, "\n")] = 0;
      while ((getchar()) != '\n');
      printf("\nCategoria alterada!\n\n");
      break;
    
    case 4:
      printf("Digite o novo estado da tarefa (0 para completo, 1 para em andamento, 2 para não iniciado): ");
      int estado;
      scanf("%d", &estado);
      while ((getchar()) != '\n');
      if(estado < 0 || estado > 2) {
        printf("\nEstado inválido!\n\n");
        return 1;
      }
      lt->tarefas[indice].estado = estado;
      printf("\nEstado alterado!\n\n");
      break;
    default:
      printf("\nOpção inválida!\n\n");
      return 1;
  }

  printf("\nTarefa alterada!\n\n\n");
  return 0;
}