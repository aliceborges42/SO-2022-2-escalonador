#include <signal.h>
#include "structures.h"

int QUANTUM_VALUE = 10;

int quantum (process *process) {
  signterrupt(1); //Habilita interrupção
  signal(SIGALRM, handleQuantum(process));
  alarm(QUANTUM_VALUE);
}

int handleQuantum(process *process){
  // Função que será chamada quando atingir o quantum
  // Atualiza o processo atual e muda a posição na fila
  // Temos 3 filas: prioridade 1, 2 e 3
  // Se o processo 1 terminar, ele vai para o final da próxima fila

  process->state = "ready";
  if (process->priority != 3)
    process->priority = process->priority + 1;

  push(filaReady, process);
}
