#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj.h"

int main() {
  printf("\nBem vindo ao app --FACA HOJE!--\n\n");

  printf("Desenvolvemos esse aplicativo com o objetivo de te ajudar com suas metas do dia-a-dia, definir a sua prioridade e conseguir organizar melhor a sua vida\n\n");

  printf("Aqui você poderá criar tarefas, lista-las, definir niveis de prioridade e deleta-las quando quiser!\n\n");

  printf("Este programa possui capacidade de armazenar até 100 tarefas, esperamos que você goste :)\n\n\n");

  printf("Vamos comecar? Digite a opcao desejada abaixo:\n\n");

  int cod; /* Variável para armazenar códigos de retorno */
  char arquivo[100] = "tarefas"; /* Nome do arquivo para armazenar as tarefas */
  ListaDeTarefas lt; /* Estrutura para armazenar a lista de tarefas */

  cod = carregarTarefas(&lt, arquivo); /* Tenta carregar as tarefas do arquivo */
  if (cod != 0){ /* Se o arquivo não pôde ser aberto ele informa ao usuario */
    printf("Arquivo ainda nao carregado, prossiga.\n\n\n");
    lt.qtd = 0; /* E aqui ele inicializa a quantidade de tarefas como zero */
  }

  int opcao; /* Variavel onde o usuario vai escolher a função */
  do{ /* Neste loop, o menu ficará rodando infinitamente após o fim de cada função, até o usuario digitar 4 para sair */
    printMenu();
    scanf("%d",&opcao);
    printf("\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer de entrada, pois será preciso para não atrapalhar na execução das demais funções no programa */

    switch(opcao) { /*Este Switch case será responsável por chamar as funções principais do programa e executa-las*/
      case 1:
        cadastrarTarefas(&lt);
        break;
      case 2:
        deletarTarefas(&lt);
        break;
      case 3:
        listarTarefas(lt);
        break;
      case 4:
        alterarTarefas(&lt);
        break;
      case 5:
        filtrarTarefas(lt);
        break;
      case 6:
        exportarTarefas(lt);
        break;
      case 7:
        printf("Saindo...\n\n");
        break;
      default:
        printf("Opcao invalida!\n\n");
    }
  } while (opcao != 7);

  cod = salvarTarefas(&lt, arquivo); /* Salva as tarefas no arquivo */
  if (cod != 0){ /* Se houve um problema ao salvar, informará ao usuario */
    printf("Problema ao salvar o arquivo\n");
  }

  printf("Fim!\n");
  return 0;
}
