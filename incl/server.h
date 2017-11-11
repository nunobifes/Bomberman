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

    char username[15];
    char password[15];

}login;

typedef struct{
    
    char username[15];
    char password[15];
    int userID;


}utilizador;


typedef struct{
    
    char nome[15];
    int vidas; // 3 vidas base
    int pontuacao;
    int mbomba;
    int items; 
    int x, y;
        
}player;
    
typedef struct{
    
    int vivo;
    int drop;
    int x, y;
            
}npc;
    
typedef struct{
        
    int tipo_parede;  //0 -> vazio, 1 -> parede não destrutivel, 2 -> parede destrutivel -> 3 vazio c/ drop
    int explosao;
    int x, y;
    
}TParede;

typedef struct{

    int tempo;
    int items;
    int npcs;

}info;


//--------------------------------------------------------------------------FUNÇÔES----------------------------------------------------------------------------

utilizador utilizadores[50];


void trataSinal(int s);
FILE * abreFich();
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

#endif