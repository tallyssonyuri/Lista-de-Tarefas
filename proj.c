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

/*---------------------------------*/

void filtrarTarefas(ListaDeTarefas lt){
  /* Imprime as opções de filtro para o usuário. */
  printf("Escolha o tipo de filtro:\n\n");
  printf("1. Filtrar tarefas por prioridade\n");
  printf("2. Filtrar tarefas por estado\n");
  printf("3. Filtrar tarefas por categoria\n");
  printf("4. Filtrar tarefas por prioridade e categoria\n\n");

  /* Lê a opção de filtro escolhida pelo usuário. */
  int opcao;
  scanf("%d", &opcao);
  printf("\n");
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  /* Executa a função de filtro correspondente à opção escolhida pelo usuário. */
  switch(opcao) {
    case 1:
      /* Filtra tarefas por prioridade. */
      filtrarTarefasPorPrioridade(lt);
      break;
    case 2:
      /** Filtra tarefas por estado. */
      filtrarTarefasPorEstado(lt);
      break;
    case 3:
      /* Filtra tarefas por categoria. */
      filtrarTarefasPorCategoria(lt);
      break;
    case 4:
      /* Filtra tarefas por prioridade e categoria. */
      filtrarTarefasPorPrioridadeECategoria(lt);
      break;
    default:
      /* Imprime uma mensagem de erro se o usuário escolher uma opção inválida. */
      printf("Opção inválida!\n\n");
  }
}

int filtrarTarefasPorPrioridade(ListaDeTarefas lt){ /* Função para filtrar tarefas por prioridade em uma lista de tarefas. */
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("\nNão há tarefas para listar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a prioridade das tarefas a serem listadas. */
  int prioridade;
  printf("\nDigite a prioridade das tarefas a serem listadas: ");
  scanf("%d", &prioridade);
  while ((getchar()) != '\n');

  /* Variável para verificar se uma tarefa com a prioridade especificada foi encontrada. */
  int encontrou = 0;
  printf("\n\nTarefas com prioridade %d:\n\n", prioridade);

  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a prioridade especificada. */
    if(lt.tarefas[i].prioridade == prioridade) {
      /* Imprime os detalhes da tarefa. */
      printf("Tarefa %d\n", i);
      printf("Descricao: %s\n", lt.tarefas[i].descricao);
      printf("Prioridade: %d\n", lt.tarefas[i].prioridade);   
      printf("Categoria: %s\n", lt.tarefas[i].categoria);
      printf("Estado: %d\n", lt.tarefas[i].estado);
      printf("\n");
      encontrou = 1;
    }
  }

  /* Se nenhuma tarefa com a prioridade especificada foi encontrada, imprime uma mensagem. */
  if(!encontrou) {
    printf("\nNão há tarefas com a prioridade %d.\n\n", prioridade);
  }

  return 0;
}

int filtrarTarefasPorEstado(ListaDeTarefas lt){ /* Função para filtrar tarefas por estado em uma lista de tarefas. */
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("Não há tarefas para listar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira o estado das tarefas a serem listadas. */
  int estado;
  printf("\nDigite o estado das tarefas a serem listadas (0 para completo, 1 para em andamento, 2 para não iniciado): ");
  scanf("%d", &estado);
  while ((getchar()) != '\n');

  /* Verifica se o estado inserido pelo usuário é válido. */
  if(estado < 0 || estado > 2) {
    printf("\nEstado inválido.\n\n");
    return 1;
  }

  /* Variável para verificar se uma tarefa com o estado especificado foi encontrada. */
  int encontrou = 0;
  printf("\n\nTarefas com estado %d:\n\n", estado);

  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem o estado especificado. */
    if(lt.tarefas[i].estado == estado) {
      /* Imprime os detalhes da tarefa. */
      printf("Tarefa %d\n", i);
      printf("Descricao: %s\n", lt.tarefas[i].descricao);
      printf("Prioridade: %d\n", lt.tarefas[i].prioridade);   
      printf("Categoria: %s\n", lt.tarefas[i].categoria);
      printf("Estado: %d\n", lt.tarefas[i].estado);
      printf("\n");
      encontrou = 1;
    }
  }

  /* Se nenhuma tarefa com o estado especificado foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com o estado %d\n\n", estado);
  }

  return 0;
}

int filtrarTarefasPorCategoria(ListaDeTarefas lt){ /* Função para filtrar tarefas por categoria em uma lista de tarefas. */
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("Não há tarefas para listar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a categoria das tarefas a serem listadas. */
  char categoria[100];
  printf("\nDigite a categoria das tarefas a serem listadas: ");
  fgets(categoria, 100, stdin);
  categoria[strcspn(categoria, "\n")] = 0;
  while ((getchar()) != '\n');

  /* Variável para verificar se uma tarefa com a categoria especificada foi encontrada. */
  int encontrou = 0;
  printf("\n\nTarefas na categoria %s:\n\n", categoria);

  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a categoria especificada. */
    if(strcmp(lt.tarefas[i].categoria, categoria) == 0) {
      /* Imprime os detalhes da tarefa. */
      printf("Tarefa %d\n", i);
      printf("Descricao: %s\n", lt.tarefas[i].descricao);
      printf("Prioridade: %d\n", lt.tarefas[i].prioridade);   
      printf("Categoria: %s\n", lt.tarefas[i].categoria);
      printf("Estado: %d\n", lt.tarefas[i].estado);
      printf("\n");
      encontrou = 1;
    }
  }

  /* Se nenhuma tarefa com a categoria especificada foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com a categoria informada\n\n");
  }

  return 0;
}

int filtrarTarefasPorPrioridadeECategoria(ListaDeTarefas lt){ /* Função para filtrar tarefas por prioridade e categoria em uma lista de tarefas. */
  
  if(lt.qtd == 0) { /* Verifica se a lista de tarefas está vazia. */
    printf("Não há tarefas para listar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a prioridade das tarefas a serem listadas. */
  int prioridade;
  printf("\nDigite a prioridade das tarefas a serem listadas: ");
  scanf("%d", &prioridade);
  while ((getchar()) != '\n');

  /* Solicita ao usuário que insira a categoria das tarefas a serem listadas. */
  char categoria[100];
  printf("\n\nDigite a categoria das tarefas a serem listadas: ");
  fgets(categoria, 100, stdin);
  categoria[strcspn(categoria, "\n")] = 0;
  while ((getchar()) != '\n');

  /* Variável para verificar se uma tarefa com a prioridade e categoria especificadas foi encontrada. */
  int encontrou = 0;
  printf("\nTarefas com prioridade %d na categoria %s:\n\n", prioridade, categoria);

  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a prioridade e categoria especificadas. */
    if(lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) {
      /* Imprime os detalhes da tarefa. */
      printf("Tarefa %d\n", i);
      printf("Descricao: %s\n", lt.tarefas[i].descricao);
      printf("Prioridade: %d\n", lt.tarefas[i].prioridade);   
      printf("Categoria: %s\n", lt.tarefas[i].categoria);
      printf("Estado: %d\n", lt.tarefas[i].estado);
      printf("\n");
      encontrou = 1;
    }
  }

  /* Se nenhuma tarefa com a prioridade e categoria especificadas foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com a prioridade e categoria selecionadas\n\n");
  }

  return 0;
}

/*---------------------------------*/

/* Função para exportar tarefas em uma lista de tarefas. */
void exportarTarefas(ListaDeTarefas lt){
  /* Imprime as opções de exportação para o usuário. */
  printf("Escolha o tipo de exportação:\n");
  printf("1. Exportar tarefas por prioridade\n");
  printf("2. Exportar tarefas por categoria\n");
  printf("3. Exportar tarefas por prioridade e categoria\n");

  /* Lê a opção de exportação escolhida pelo usuário. */
  int opcao;
  scanf("%d", &opcao);
  printf("\n");
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  /* Executa a função de exportação correspondente à opção escolhida pelo usuário. */
  switch(opcao) {
    case 1:
      /* Exporta tarefas por prioridade. */
      exportarTarefasPorPrioridade(lt);
      break;
    case 2:
      /* Exporta tarefas por categoria. */
      exportarTarefasPorCategoria(lt);
      break;
    case 3:
      /* Exporta tarefas por prioridade e categoria. */
      exportarTarefasPorPrioridadeECategoria(lt);
      break;
    default:
      /* Imprime uma mensagem de erro se o usuário escolher uma opção inválida. */
      printf("Opção inválida!\n\n");
  }
}

/* Função para exportar tarefas por prioridade em uma lista de tarefas. */
int exportarTarefasPorPrioridade(ListaDeTarefas lt){
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("Não há tarefas para exportar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a prioridade das tarefas a serem exportadas. */
  int prioridade;
  printf("Digite a prioridade das tarefas a serem exportadas: ");
  scanf("%d", &prioridade);
  while ((getchar()) != '\n');

  /* Abre o arquivo para escrita. */
  FILE *fp = fopen("tarefas_por_prioridade.txt", "w");
  /* Verifica se o arquivo foi aberto com sucesso. */
  if(fp == NULL) {
    printf("Não foi possível abrir o arquivo para escrita.\n");
    return 1;
  }

  /* Variável para verificar se uma tarefa com a prioridade especificada foi encontrada. */
  int encontrou = 0;
  /* Escreve no arquivo as tarefas com a prioridade especificada. */
  fprintf(fp, "Tarefas com prioridade %d:\n\n", prioridade);
  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a prioridade especificada. */
    if(lt.tarefas[i].prioridade == prioridade) {
      /* Escreve os detalhes da tarefa no arquivo. */
      fprintf(fp, "Tarefa %d\n", i);
      fprintf(fp, "Descricao: %s\n", lt.tarefas[i].descricao);
      fprintf(fp, "Prioridade: %d\n", lt.tarefas[i].prioridade);   
      fprintf(fp, "Categoria: %s\n", lt.tarefas[i].categoria);
      fprintf(fp, "Estado: %d\n", lt.tarefas[i].estado);
      fprintf(fp, "\n");
      encontrou = 1;
    }
  }

  /* Se nenhuma tarefa com a prioridade especificada foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com a prioridade %d\n\n", prioridade);
  }
  /* Fecha o arquivo. */
  fclose(fp);

  /* Informa ao usuário que as tarefas foram exportadas. */
  printf("\nTarefas exportadas para o arquivo tarefas_por_prioridade.txt!\n\n\n");
  return 0;
}

/* Função para exportar tarefas por categoria em uma lista de tarefas. */
int exportarTarefasPorCategoria(ListaDeTarefas lt){
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("Não há tarefas para exportar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a categoria das tarefas a serem exportadas. */
  char categoria[100];
  printf("Digite a categoria das tarefas a serem exportadas: ");
  fgets(categoria, 100, stdin);
  categoria[strcspn(categoria, "\n")] = 0;
  while ((getchar()) != '\n');

  /* Abre o arquivo para escrita. */
  FILE *fp = fopen("tarefas_por_categoria.txt", "w");
  /* Verifica se o arquivo foi aberto com sucesso. */
  if(fp == NULL) {
    printf("Não foi possível abrir o arquivo para escrita.\n");
    return 1;
  }

  /* Variável para verificar se uma tarefa com a categoria especificada foi encontrada. */
  int encontrou = 0;
  /* Escreve no arquivo as tarefas com a categoria especificada. */
  fprintf(fp, "Tarefas na categoria %s:\n\n", categoria);
  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a categoria especificada. */
    if(strcmp(lt.tarefas[i].categoria, categoria) == 0) {
      /* Escreve os detalhes da tarefa no arquivo. */
      fprintf(fp, "Tarefa %d\n", i);
      fprintf(fp, "Descricao: %s\n", lt.tarefas[i].descricao);
      fprintf(fp, "Prioridade: %d\n", lt.tarefas[i].prioridade);   
      fprintf(fp, "Categoria: %s\n", lt.tarefas[i].categoria);
      fprintf(fp, "Estado: %d\n", lt.tarefas[i].estado);
      fprintf(fp, "\n");
      encontrou = 1;
    }
  }

  /* Fecha o arquivo. */
  fclose(fp);

  /* Se nenhuma tarefa com a categoria especificada foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com a categoria informada\n\n");
  }

  /* Informa ao usuário que as tarefas foram exportadas. */
  printf("\nTarefas exportadas para o arquivo tarefas_por_categoria.txt!\n\n\n");
  return 0;
}

/* Função para exportar tarefas por prioridade e categoria em uma lista de tarefas. */
int exportarTarefasPorPrioridadeECategoria(ListaDeTarefas lt){
  /* Verifica se a lista de tarefas está vazia. */
  if(lt.qtd == 0) {
    printf("Não há tarefas para exportar.\n\n");
    return 1;
  }

  /* Solicita ao usuário que insira a prioridade das tarefas a serem exportadas. */
  int prioridade;
  printf("Digite a prioridade das tarefas a serem exportadas: ");
  scanf("%d", &prioridade);
  while ((getchar()) != '\n');

  /* Solicita ao usuário que insira a categoria das tarefas a serem exportadas. */
  char categoria[100];
  printf("Digite a categoria das tarefas a serem exportadas: ");
  fgets(categoria, 100, stdin);
  categoria[strcspn(categoria, "\n")] = 0;
  while ((getchar()) != '\n');

  /* Abre o arquivo para escrita. */
  FILE *fp = fopen("tarefas_por_prioridade_e_categoria.txt", "w");
  /* Verifica se o arquivo foi aberto com sucesso. */
  if(fp == NULL) {
    printf("Não foi possível abrir o arquivo para escrita.\n");
    return 1;
  }

  /* Variável para verificar se uma tarefa com a prioridade e categoria especificadas foi encontrada. */
  int encontrou = 0;
  /* Escreve no arquivo as tarefas com a prioridade e categoria especificadas. */
  fprintf(fp, "Tarefas com prioridade %d na categoria %s:\n\n", prioridade, categoria);
  /* Percorre a lista de tarefas. */
  for(int i = 0; i < lt.qtd; i++) {
    /* Verifica se a tarefa atual tem a prioridade e categoria especificadas. */
    if(lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) {
      /* Escreve os detalhes da tarefa no arquivo. */
      fprintf(fp, "Tarefa %d\n", i);
      fprintf(fp, "Descricao: %s\n", lt.tarefas[i].descricao);
      fprintf(fp, "Prioridade: %d\n", lt.tarefas[i].prioridade);   
      fprintf(fp, "Categoria: %s\n", lt.tarefas[i].categoria);
      fprintf(fp, "Estado: %d\n", lt.tarefas[i].estado);
      fprintf(fp, "\n");
      encontrou = 1;
    }
  }

  /* Fecha o arquivo. */
  fclose(fp);

  /* Se nenhuma tarefa com a prioridade e categoria especificadas foi encontrada, imprime uma mensagem. */
  if (!encontrou){
    printf("\nNão há tarefas com a categoria e prioridades informadas\n\n");
  }

  /* Informa ao usuário que as tarefas foram exportadas. */
  printf("\nTarefas exportadas para o arquivo tarefas_por_prioridade_e_categoria.txt!\n\n\n");

  return 0;
}