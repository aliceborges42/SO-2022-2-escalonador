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

int createQueue(key_t key);

struct msgbuf {
	long mtype;
	char mtext[10];
};

int main() {
	int i, pid;

	// Creating priority queues
	int high_priority_queue_id = createQueue(HIGH_PRIORITY_KEY);
	int medium_priority_queue_id = createQueue(MEDIUM_PRIORITY_KEY);
	int low_priority_queue_id = createQueue(LOW_PRIORITY_KEY);

	struct msgbuf msg_send;

	// Creating child processes
	for (int i = 0; i < 6; i++) {
		pid = fork();

		if (pid < 0) {
			printf("Error in fork\n");
			exit(1);
		}

		if (pid == 0) {
			// Child process

			if (execl("child_process", "child_process", HIGH_PRIORITY, (char *) 0) < 0) {
				printf("Error in execl = %d\n", errno);
				exit(3);
			}
		}

		// Sending child process to queue
		msg_send.mtype = pid;
		strcpy(msg_send.mtext, HIGH_PRIORITY);

		if ((msgsnd(high_priority_queue_id, &msg_send, sizeof(msg_send), IPC_NOWAIT)) < 0) {
			printf("Error sending message\n");
			exit(4);
		}

		// Stop child process
		kill(pid, SIGSTOP);
	}
}

int createQueue(key_t key) {
	int id;

	if ((id = msgget(key, IPC_CREAT | 0x1FF)) < 0) {
		printf("Error creating queue\n");
		exit(2);
	}

	return id;
}