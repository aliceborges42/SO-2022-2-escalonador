#include <stdio.h>
#include <sys/time.h>

timeval time;
timeval timeInitProgram;
timeval timeInitQuantum;

typedef struct {
  // long int delay
  char nomeExecutavel[50];
  int pid;
  int priority;
  int state; //ready, block, running, end
  int processTime;
  int currentTime;
  int initialTime;
  int finalTime;
} process;

typedef struct  {
  int priority;
  process *process;
} processQueue;

int isProcessExecuting = 0;

int rascunhuMain(int argc, char *argv[]){
  // Pega a data atual para saber o tempo de execução do programa todo

  for(int i = 0; argc; i++) {
    push(filaDeProcessos, argv[i])
  }

  gettimeofday(&time, nullptr);
  timeInitProgram = time

  // filaDeProcessos

  // filaReady
  // fileExecutando
  // filaBloqueado

  while(1) {
    gettimeofday(&tempo, nullptr);
    //VerificaDelay();
    
    //execproc
    if(!isProcessExecuting) {
        for(int i = 0; i < filaDeProcessos.size(); i++) {
          if(filaDeProcessos[i]->process->state == "ready") {
            push(filaReady, filaDeProcessos[i]);
            filaDeProcessos[i]->process->state == "running"
            imprimeDados(filaDeProcessos[i]->process->pid);
            execprocd();
          }
        }
        ExecuteProcess(/*filaDeProcessos*/);
    } else {
        VerifyQuantum();
    }
  }


  return 0;
}

int execprocd (process Process) {
  // irá iterar em um tempo fixo o time
  restoreContext();

  // loop com clock sendo iterado 1x por segundo
  // se o valor do clock atinge o quantum -> condição
  // de parada do loop, ele chama saveContext, atualiza os
  // atributos do processo e muda a posição na fila
  // de processos
  if(process.currentTime != process.processTime){
    // irá iterar em um tempo fixo o time
    saveContext();
  }

  // Processo finalizado, atributos de processo atualizados
  if(process.currentTime == process.processTime){
    process.state = "end";
    process.finalTime = time;
    isProcessExecuting = false;
  }
  
}

int main()
{

  struct timeval tv;
  // tv_sec
  // tv_usec 

  struct timezone tz;
  // tz_minuteswest
  // tz_dsttime

  gettimeofday(&tv, &tz);

  printf("Seconds since 1/1/1970: %lu\n", tv.tv_sec);
  printf("Microseconds: %d\n", tv.tv_usec);
  printf("Minutes west of Greenwich: %d\n", tz.tz_minuteswest);
  printf("Daylight Saving Time adjustment: %d\n", tz.tz_dsttime);

  return (0);

  // while (1)
  // {
  //   int time = gettimeofday();
  //   printf(&time)
  // }
}

// void execproc(<arquivo - executável><prioridade>[<param1><param2>...<paramn>])
// {
//   // solicita a execução dos programas e imprime o identificador na tela
// }

// void cancelaproc()
// {
//   // solicita o cancelamento da execução dos processos
// }

// void execprocd()
// {
//   // processo em background que controla a execução de processos
// }

// void terminaexecprocessod()
// {
//   // termina a execução dos processos
// }

// // oi
// // oi
