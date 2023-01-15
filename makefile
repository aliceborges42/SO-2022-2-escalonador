# the compiler to use.
all: execprocd execproc child_process

execprocd: execprocd.c
	cc execprocd.c -o execprocd

execproc: execproc.c
	cc execproc.c -o execproc

child_process: child_process.c
	cc child_process.c -o child_process

clean:
	rm -rf *.o *~ execprocd execproc child_process
