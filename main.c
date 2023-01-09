#include <stdio.h>
#include <sys/time.h>

int main()
{

  struct timeval tv;
  // tv_sec
  // tv_usec

  struct timezone tz;
  // tz_minuteswest
  // tz_dsttime

  gettimeofday(&tv, &tz);

  printf("Seconds since 1/1/1970: %lu\n", tv.tv_sec);
  printf("Microseconds: %d\n", tv.tv_usec);
  printf("Minutes west of Greenwich: %d\n", tz.tz_minuteswest);
  printf("Daylight Saving Time adjustment: %d\n", tz.tz_dsttime);

  return (0);

  // while (1)
  // {
  //   int time = gettimeofday();
  //   printf(&time)
  // }
}

// void execproc(<arquivo - executável><prioridade>[<param1><param2>...<paramn>])
// {
//   // solicita a execução dos programas e imprime o identificador na tela
// }

// void cancelaproc()
// {
//   // solicita o cancelamento da execução dos processos
// }

// void execprocd()
// {
//   // processo em background que controla a execução de processos
// }

// void terminaexecprocessod()
// {
//   // termina a execução dos processos
// }

// // oi
// // oi
