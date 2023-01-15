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

#define PROCESS_PID_KEY		0x8555
#define HIGH_PRIORITY_KEY	0x8551
#define MEDIUM_PRIORITY_KEY 0x8552
#define LOW_PRIORITY_KEY	0x8553
#define END_TIME_KEY		0x8554

int get_queue(key_t key);
int get_queue_id(char * priority);

int process_pid_queue_id;
int high_priority_queue_id;
int medium_priority_queue_id;
int low_priority_queue_id;
int end_time_queue_id;

struct msgbuf {
	long mtype;
	char mtext[100];
} msg_rec;

int main (){
    high_priority_queue_id = get_queue(HIGH_PRIORITY_KEY);
    medium_priority_queue_id = get_queue(MEDIUM_PRIORITY_KEY);
    low_priority_queue_id = get_queue(LOW_PRIORITY_KEY);
    process_pid_queue_id = get_queue(PROCESS_PID_KEY);
    end_time_queue_id = get_queue(END_TIME_KEY);

    while(1){
        if ((msgrcv(process_pid_queue_id, &msg_rec, sizeof(msg_rec), 0, IPC_NOWAIT)) < 0) {
            break;
        }
        long pid = msg_rec.mtype;
        printf("KILL PROCESS: %ld\n", pid);
        kill(pid, SIGKILL);

    }
    msgctl(high_priority_queue_id, IPC_RMID, NULL);
    msgctl(medium_priority_queue_id, IPC_RMID, NULL);
    msgctl(low_priority_queue_id, IPC_RMID, NULL);
    msgctl(process_pid_queue_id, IPC_RMID, NULL);
    msgctl(end_time_queue_id, IPC_RMID, NULL);
}

int get_queue(key_t key) {
	int id;

	if ((id = msgget(key, 0x1FF)) < 0) {
		printf("Error getting queue\n");
		exit(2);
	}

	return id;
}
