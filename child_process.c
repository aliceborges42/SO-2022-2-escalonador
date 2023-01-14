#include <stdio.h>
#include <unistd.h>

int main(argc, argv)
int argc;
char **argv;
{
	long int i;

	// Busy Waiting on CPU
	for (i = 0; i < 30000000000; i++);
}