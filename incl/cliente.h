#ifndef CLIENTE
#define CLIENTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ncursesw/ncurses.h>
#include <pthread.h>

//--------------------------------------------------------------------------ESTRUTURAS-------------------------------------------------------------------------
#include "structs.h"

//--------------------------------------------------------------------------VARIAVEIS----------------------------------------------------------------------------

respCliente lgin;
pthread_t id;
mensagem msg;
int opcao;
char fifo[50];
int fd, fcl;
int breake;
//--------------------------------------------------------------------------FUNÇÔES----------------------------------------------------------------------------
void *trataCliente(void *p);
void trataSinalCli(int s);
void sairCli();
#endif