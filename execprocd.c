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

#define HIGH_PRIORITY	"HIGH"
#define MEDIUM_PRIORITY	"MEDIUM"
#define LOW_PRIORITY	"LOW"

#define HIGH_PRIORITY_KEY	0x8551
#define MEDIUM_PRIORITY_KEY 0x8552
#define LOW_PRIORITY_KEY	0x8553
#define END_TIME_KEY		0x8554
#define PROCESS_PID_KEY		0x8555

int high_priority_queue_id;
int medium_priority_queue_id;
int low_priority_queue_id;
int end_time_queue_id;
int process_pid_queue_id;

int is_process_running = 0; // 0 is false, 1 is true
long running_process_pid;
char running_process_priority[10];

void quantum();
int create_queue(key_t key);
int get_queue_id(char * priority);

int is_first_process = 1;

struct msgbuf {
	long mtype;
	char mtext[100];
} msg_send, msg_rec;

time_t start, end;

int main() {
	// Creating priority queues
	high_priority_queue_id = create_queue(HIGH_PRIORITY_KEY);
	medium_priority_queue_id = create_queue(MEDIUM_PRIORITY_KEY);
	low_priority_queue_id = create_queue(LOW_PRIORITY_KEY);
	end_time_queue_id = create_queue(END_TIME_KEY);
	process_pid_queue_id = create_queue(PROCESS_PID_KEY);

	// Treat alarm signal
	signal(SIGALRM, quantum);
	msg_send.mtype = getpid();

	if (msgsnd(process_pid_queue_id, &msg_send, sizeof(msg_send), IPC_NOWAIT) < 0) {
		printf("Error sending execprocd pid message\n");
		exit(4);
	}

	while (1) {
		while(is_process_running);

		if ((msgrcv(high_priority_queue_id, &msg_rec, sizeof(msg_rec), 0, IPC_NOWAIT)) >= 0) {
			// Set quantum time
			alarm(10);

			// Continue process execution
			long pid = msg_rec.mtype;
			is_process_running = 1;
			running_process_pid = pid;
			strcpy(running_process_priority, msg_rec.mtext);

			printf("Iniciou: Processo Filho HIGH_PRIORITY | PID = %ld\n", pid);

			if(is_first_process){
				is_first_process = 0;
				time(&start);
			}

			kill(pid, SIGCONT);

			continue;
		}

		while(is_process_running);

		if ((msgrcv(medium_priority_queue_id, &msg_rec, sizeof(msg_rec), 0, IPC_NOWAIT)) >= 0) {
			// Set quantum time
			alarm(10);

			// Continue process execution
			long pid = msg_rec.mtype;
			is_process_running = 1;
			running_process_pid = pid;
			strcpy(running_process_priority, msg_rec.mtext);

			printf("Iniciou: Processo Filho MEDIUM_PRIORITY | PID = %ld\n", pid);

			if(is_first_process){
				is_first_process = 0;
				time(&start);
			}

			kill(pid, SIGCONT);

			continue;
		}

		while(is_process_running);

		if ((msgrcv(low_priority_queue_id, &msg_rec, sizeof(msg_rec), 0, IPC_NOWAIT)) >= 0) {
			// Set quantum time
			alarm(10);

			// Continue process execution
			long pid = msg_rec.mtype;
			is_process_running = 1;
			running_process_pid = pid;
			strcpy(running_process_priority, msg_rec.mtext);

			printf("Iniciou: Processo Filho LOW_PRIORITY | PID = %ld\n", pid);

			if(is_first_process){
				is_first_process = 0;
				time(&start);
			}

			kill(pid, SIGCONT);

			continue;
		}
	}
}

void quantum() {
	// Stop process
	printf("Quantum: Processo Filho | PID = %ld\n", running_process_pid);

	if ((kill(running_process_pid, SIGSTOP)) < 0) {
		if ((msgrcv(end_time_queue_id, &msg_rec, sizeof(msg_rec), 0, IPC_NOWAIT)) >= 0) {
			int time = atoi(msg_rec.mtext);
			double turnaround_time = difftime(time, start);
			printf("Turnaround Time: %f seconds\n", turnaround_time);
			printf("PID = %ld\n", running_process_pid);
		}
		is_process_running = 0;
		return;
	}

	is_process_running = 0;

	// Change priority
	if (strcmp(HIGH_PRIORITY, running_process_priority) == 0) {
		// If HIGH, change to MEDIUM
		strcpy(msg_send.mtext, MEDIUM_PRIORITY);
	} else if (strcmp(MEDIUM_PRIORITY, running_process_priority) == 0) {
		// If MEDIUM, change to LOW
		strcpy(msg_send.mtext, LOW_PRIORITY);
	} else {
		// IF LOW, change to HIGH
		strcpy(msg_send.mtext, HIGH_PRIORITY);
	}

	// Sending process to the end of the queue
	msg_send.mtype = running_process_pid;

	if ((msgsnd(get_queue_id(msg_send.mtext), &msg_send, sizeof(msg_send), IPC_NOWAIT)) < 0) {
		printf("Error sending message\n");
		exit(4);
	}

	return;
}

int create_queue(key_t key) {
	int id;

	if ((id = msgget(key, IPC_CREAT | 0x1FF)) < 0) {
		printf("Error creating queue\n");
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
