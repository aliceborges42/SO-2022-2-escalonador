/*
Grupo:
- José Vinícius Garreto Costa - 180123734
 - Alice Borges - 18/0011855
 - Bruno Couto Mariño - 19/0011106
 - Caio Mendes - 19/0011211
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define END_TIME_KEY 0x8554

struct msgbuf {
	long mtype;
	char mtext[100];
} msg_send;

int get_queue(key_t key);

int main(int argc, char **argv)
{
	long int i;
	time_t end;
	char string_end[20];

	int end_time_queue_id = get_queue(END_TIME_KEY);

	// Busy Waiting on CPU
	for (i = 0; i < 30000000000; i++);
	//envia tempo de finalização para fila de processos
	time(&end);

	sprintf(string_end, "%ld", end);

	msg_send.mtype = getpid();

	strcpy(msg_send.mtext, string_end);

	if (msgsnd(end_time_queue_id, &msg_send, sizeof(msg_send), IPC_NOWAIT) < 0) {
		printf("Error sending message\n");
		exit(4);
	}

	printf("Processo PID = %d encerrou\n", getpid());
}

int get_queue(key_t key) {
	int id;

	if ((id = msgget(key, 0x1FF)) < 0) {
		printf("Error getting queue\n");
		exit(2);
	}

	return id;
}
