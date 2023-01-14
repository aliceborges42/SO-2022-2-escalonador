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

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Error: Wrong number of arguments\n");
		exit(5);
	}

	kill(atoi(argv[1]), SIGKILL);
}