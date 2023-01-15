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
```
Executar o programa execprocd:

```
./execprocd &
```

Colocar os programas a serem executados e sua prioridade, como:
```
./execproc child_process MEDIUM &
```
