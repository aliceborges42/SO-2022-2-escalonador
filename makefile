# the compiler to use.
all: execprocd execproc child_process termina cancela

execprocd: execprocd.c
	cc execprocd.c -o execprocd

execproc: execproc.c
	cc execproc.c -o execproc

termina: termina_execprocessod.c
	cc termina_execprocessod.c -o termina_execprocessod

cancela: cancela_proc.c
	cc cancela_proc.c -o cancela_proc

child_process: child_process.c
	cc child_process.c -o child_process

execprocd-run: execprocd
	./execprocd &

run: execprocd execproc child_process
	./execproc child_process MEDIUM &

run10: execprocd execproc child_process
	./execproc child_process MEDIUM &
	./execproc child_process LOW &
	./execproc child_process MEDIUM &
	./execproc child_process MEDIUM &
	./execproc child_process HIGH &
	./execproc child_process MEDIUM &
	./execproc child_process LOW &
	./execproc child_process LOW &
	./execproc child_process MEDIUM &
	./execproc child_process HIGH &

termina_proc: termina
	./termina_execprocessod

clean:
	rm -rf *.o *~ execprocd execproc child_process cancela_proc termina_execprocessod
