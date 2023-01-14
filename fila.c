#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msg {
  long mtype;
  char mtext[1];
} msg;

int createQueue(key_t key, int msgflg) {
  int msqid = msgget(key, msgflg | IPC_CREAT);

  if (msqid < 0) {
    printf("deu ruim pra criar a fila\n");
    return -1;
  }
}

int sendMsg(int msqid, void *msgp, size_t msgsz, int msgflg) {
  msgsnd(msqid, msgp, msgsz, msgflg);
}