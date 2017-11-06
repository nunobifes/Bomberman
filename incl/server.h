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
//#include <sys/mman.h>

//--------------------------------------------------------------------------ESTRUTURAS-------------------------------------------------------------------------

typedef struct player{
    
    int vidas; // 3 vidas base
    int pontuacao;
    int bombas;
    int mbomba;
    int items; 
    int x, y;
        
}player;
    
typedef struct npc{
    
    int hit;
    int drop;
    int x, y;
            
}npc;
    
typedef struct tipoParede{
        
    int tipo_parede;  //0 -> vazio, 1 -> parede não destrutivel, 2 -> parede destrutivel -> 3 vazio c/ drop
    int explosao;
}TParede;

//--------------------------------------------------------------------------FUNÇÔES----------------------------------------------------------------------------

int abreFich();
void allUsers();
int verificaUser(char *user);
char procuraUser(char *user);
void addUSer(char *user, char *pass);

#endif