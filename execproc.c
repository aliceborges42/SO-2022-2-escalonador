/*
Grupo:
José Vinícius Garreto Costa - 180123734
Bruno Couto Marino -
Alice da Costa Borges -
Caio Mendes -
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define HIGH_PRIORITY	"HIGH"
#define MEDIUM_PRIORITY	"MEDIUM"
#define LOW_PRIORITY	"LOW"

#define HIGH_PRIORITY_KEY	0x8551
#define MEDIUM_PRIORITY_KEY 0x8552
#define LOW_PRIORITY_KEY	0x8553

int high_priority_queue_id;
int medium_priority_queue_id;
int low_priority_queue_id;

int get_queue(key_t key);
int get_queue_id(char * priority);

struct msgbuf {
	long mtype;
	char mtext[10];
};

int main(int argc, char **argv) {
	int i, pid;

	if (argc < 3) {
		printf("Error: Wrong number of arguments\n");
		exit(5);
	}

	// Getting priority queues
	high_priority_queue_id = get_queue(HIGH_PRIORITY_KEY);
	medium_priority_queue_id = get_queue(MEDIUM_PRIORITY_KEY);
	low_priority_queue_id = get_queue(LOW_PRIORITY_KEY);

	struct msgbuf msg_send;

	// Creating child process
	pid = fork();

	if (pid < 0) {
		printf("Error in fork\n");
		exit(1);
	}

	if (pid == 0) {
		// Child process
		if (execl(argv[1], argv[1], argv[2], (char *) 0) < 0) {
			printf("Error in execl = %d\n", errno);
			exit(3);
		}
	}
	// Stop child process
	kill(pid, SIGSTOP);

	// Sending child process to queue
	msg_send.mtype = pid;
	strcpy(msg_send.mtext, argv[2]);

	if ((msgsnd(get_queue_id(argv[2]), &msg_send, sizeof(msg_send), IPC_NOWAIT)) < 0) {
		printf("Error sending message\n");
		exit(4);
	}
}

int get_queue(key_t key) {
	int id;

	if ((id = msgget(key, 0x1FF)) < 0) {
		printf("Error getting queue\n");
		exit(2);
	}

	return id;
}

int get_queue_id(char * priority) {
	if (strcmp(HIGH_PRIORITY, priority) == 0) {
		return high_priority_queue_id;
	}

	if (strcmp(MEDIUM_PRIORITY, priority) == 0) {
		return medium_priority_queue_id;
	}

	if (strcmp(LOW_PRIORITY, priority) == 0) {
		return low_priority_queue_id;
	}

	return -1;
}
