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
    
//--------------------------------------------------------------------------FUNÇÕES----------------------------------------------------------------------------

int abreFich(){
    
    int fo;
    // Abrir ficheiro users para leitura e escrita e verifica se ele existe
    fo = open("users.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    if (fo == -1) {
        printf("Erro ficheiro %s não existe!", "users.txt");
        return -1;
    }
    return fo;
}



void allUsers(){
    
    //int fich = abreFich();
    //off_t ret;
    //ret = lseek(fich, 0, SEEK_END);
    //char *content = mmap(NULL, ret, PROT_READ | PROT_WRITE, MAP_PRIVATE, fich, 0);
    
    //printf("%s", content);
    //close(fich);
    
    int fich = abreFich();
    FILE *fo = fdopen(fich, "r");
    char userC[15], passC[15], line[50];
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        sscanf(line, "%s %s\n", userC, passC);
        printf("%s\n", userC);
    }
    close(fich);
    
}
    
    
int verificaUser(char *user){

    int fich = abreFich();
    FILE *fo = fdopen(fich, "r");
    char userC[15], passC[15], line[50];
    int i;
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        i++;
        sscanf(line, "%s %s\n", userC, passC);
        if(strcmp(userC, user) == 0){
            //rewind(fo);
            close(fich);
            return 1;
        }
    }
    close(fich);
    return 0;
}

char procuraUser(char *user){

    int fich = abreFich();
    FILE *fo = fdopen(fich, "r");
    char userC[15], passC[15], line[50];
    int i;
    static char ret[50];
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        i++;
        sscanf(line, "%s %s\n", userC, passC);
        if(strcmp(userC, user) == 0){
            // rewind(fo);
            close(fich);
            *ret = printf("O Utilizador: %s tem a password: %s.\n", userC, passC);
            return *ret;
        }
    }
    close(fich);
}

void addUSer(char *user, char *pass){

    int fich = abreFich();
    char userPass[50];
    sprintf(userPass, "%s %s\n", user, pass);
        
    off_t ret;
    ret = lseek(fich, 0, SEEK_END);
    
    if(ret != (off_t) -1)
        write(fich, userPass, strlen(userPass));
    
    close(fich);
}

//--------------------------------------------------------------------------MAIN-------------------------------------------------------------------------------

int main(){

    // player jogador;
    // jogador.hp = 100;
    // jogador.pontuacao = 0;
    // jogador.x=1;
    // jogador.y=1;

    // npc enemy;
    // enemy.hit=0;
    // enemy.drop=1;
    // enemy.x= 20;
    // enemy.y= 30;

    // TParede mapa[54][24];

    // TParede** mapa;
    // mapa = (TParede**)malloc(sizeof(TParede*) * 24);
    // for(int i = 0; i<24; i++){
    //    mapa[i] = (TParede*)malloc(sizeof(TParede)*54);
    // }
    
    // a shell

    system("clear");
    char comando[30], username[15], password[15];
    
    while(1) {
        
        printf("bomberman@server $ ");
        scanf(" %29[^\n]", comando);
        
        
        // adiciona jogador novo
        if(strncmp(comando, "add", strlen("add")) == 0) {
            sscanf(comando, "add %14[^ ] %14[^\n]", username, password);
            if(strlen(username) < 1 || strlen(password) < 1){
                printf("Erro de sintaxe, porfavor escreva 'add USERNAME PASSWORD'!\n");
            }else{
                if(verificaUser(username) == 1){
                    printf("Erro username já está a ser utilizado, porfavor escolhe outro!\n");
                }else{        
                    addUSer(username, password); //verificaUser(username, fo);
                }
            }                
        }
        // sai do servidor
        if(strncmp(comando, "quit", strlen("quit")) == 0){
            exit(0);
        }
        // apago o ecrã
        if(strncmp(comando, "clear", strlen("clear")) == 0){
            system("clear");
        }
        // mostra todos os jogadores registados e passwords(TODO mostrar só os nomes de utilizador)
        if(strncmp(comando, "users", strlen("users")) == 0){
            allUsers();
        }
        // mostra jogador passado por argumento
        if(strncmp(comando, "user", strlen("user")) == 0){
            if(sscanf(comando, "user %14[^\n]", username) != EOF)
                procuraUser(username);
        }

    }       
    return 0;
}