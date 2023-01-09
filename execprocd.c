/*A execução dos processos será feita por um processo em background (execprocd), que
implementará a política de escalonamento. Seu funcionamento é o seguinte. Para cada processo
P no início da fila de maior prioridade não vazia, o processo execprocd colocará em P execução
pelo tempo estipulado no seu quantum. Quando o quantum se esgotar, o processo terá sua
prioridade recalculada e irá para o final da respectiva fila e o processo no início da fila de maior
prioridade será colocado em execução. Quando o processo P terminar sua execução, é impresso
o tempo total de execução deste processo (wallclock time – tempo de turnaround), o número de
trocas de contexto e seu identificador.*/
