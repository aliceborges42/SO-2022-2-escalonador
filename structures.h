#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
  // long int delay
  char nomeExecutavel[50];
  int pid;
  int priority;
  int state; //ready, block, running, end
  int processTime; 
  int currentTime;
  int initialTime;
  int finalTime;
} process;

#endif