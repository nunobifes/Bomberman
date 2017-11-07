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
//#include <termios.h>
//#include <ncursesw/ncurses.h>
//#include <sys/mman.h>

//--------------------------------------------------------------------------ESTRUTURAS-------------------------------------------------------------------------

typedef struct{

    char *username;
    char *password;

}login;


typedef struct {
    
    char *nome;
    int vidas; // 3 vidas base
    int pontuacao;
    
}infoPlayer;

typedef struct{
    
    infoPlayer infoplayer;

    int mbomba;
    int items; 
    int x, y;
        
}player;
    
typedef struct{
    
    int hit;
    int drop;
    int x, y;
            
}npc;
    
typedef struct{
        
    int tipo_parede;  //0 -> vazio, 1 -> parede não destrutivel, 2 -> parede destrutivel -> 3 vazio c/ drop
    int explosao;

}TParede;

typedef struct{

    int tempo;
    int items;
    int npcs;

}info;


//--------------------------------------------------------------------------FUNÇÔES----------------------------------------------------------------------------


void trataSinal(int s);
int abreFich();
void allUsers();
int verificaUser(char *user);
char procuraUser(char *user);
void addUser(char *user, char *pass);
void kickUSer(char *user);
void showGame();
void shutdown();
void mudaMap();
void removeUser();

#endif