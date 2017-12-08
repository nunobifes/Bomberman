#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

//--------------------------------------------------------------------------ESTRUTURAS-------------------------------------------------------------------------
#include "structs.h"

//--------------------------------------------------------------------------VARIAVEIS----------------------------------------------------------------------------
pid_t posx;
pthread_t id;
int pi;
int keep_alive, n, fd, flc;
char fifo_cliente[20];

respCliente lgin;
login* online;
mensagem msg;
utilizador* utilizadores;
//--------------------------------------------------------------------------FUNÇÔES----------------------------------------------------------------------------

void trataSinal(int s);
FILE *abreFich();
void leficheiro();
void allUsers();
int verificaUser(char *user);
char procuraUser(char *user);
void addUser(char *user, char *pass);
void kickUser(char *user);
void showGame();
void shutdown();
void mudaMap();
void removeUser();
void mostrauserstruct();
void fechaFich();
void mostraLogados();
void sair();
void* leituraPipe(void *p);
void shell();

#endif