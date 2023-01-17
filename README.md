# SO-2022-2-escalonador

Trabalho de Sistemas Operacionais do Grupo:
 - Alice Borges - 18/0011855
 - Bruno Couto Mariño - 19/0011106
 - Caio Mendes - 19/0011211
 - José Garreto -  18/0123734

## Como rodar o projeto

```
make all
```

ou compilar os arquivos separadamente com:

```
cc execprocd.c -o execprocd
cc execproc.c -o execproc
cc child_process.c -o child_process
cc termina_execprocessod.c -o termina_execprocessod
cc cancela_proc.c -o cancela_proc
```

Antes de executar os processos, é necessário rodar o execprocd em background, para isso utilize o comando:
````
make execprocd-run
```
Executar o programa com um processo:

```
make run
```

Executar o programa com dez processos:

```
make run10
```

Executar o programa manualmente
```
./execprocd & \
./execproc child_process MEDIUM &
```
OBS: A prioridade pode ser alterada para LOW, MEDIUM ou HIGH e a segunda linha pode ser executada diversas vezes para aumentar o número de processos.

Para cancelar os processos, utilize o comando
```
./cancela_proc PID
```
Em seguida pode se conferir com o comando ps -l que o processo foi cancelado

Para terminar os processos
```
make termina_proc
```
