#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>

void allUsers(int fich){
    
    off_t ret;
    ret = lseek(fich, 0, SEEK_END);
    char *content = mmap(NULL, ret, PROT_READ | PROT_WRITE, MAP_PRIVATE, fich, 0);
    
    printf("%s", content);
    
    }
    
    
int verificaUser(char *user, int buffer){

    FILE *fo = fdopen(buffer, "r");
    char userC[15], passC[15], line[50];
    int i;
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        i++;
        //printf("%3d: %s", i, line);
        sscanf(line, "%s %s\n", userC, passC);
        //printf("%d %s\n", i, userC);
        if(strcmp(userC, user) == 0){
            rewind(fo);
            return 1;
        }
    }
    return 0;
}

char procuraUser(char *user, int buffer){
    
    FILE *fo = fdopen(buffer, "r");
    char userC[15], passC[15], line[50];
    int i;
    char ret[50];
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        i++;
        //printf("%3d: %s", i, line);
        sscanf(line, "%s %s\n", userC, passC);
        //printf("%d %s\n", i, userC);
        if(strcmp(userC, user) == 0){
            rewind(fo);
            *ret = printf("O Utilizador: %s tem a password: %s.\n", userC, passC);
            return *ret;
        }
    }
}

void addUSer(char *user, char *pass, int fich){

    char userPass[100];
    sprintf(userPass, "%s %s\n", user, pass);
        
    off_t ret;
    ret = lseek(fich, 0, SEEK_END);
    
    if(ret != (off_t) -1)
        write(fich, userPass, strlen(userPass));
    }

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
    int buffer = abreFich();
    
    while(1) {
        
        printf("bomberman@server $ ");
        scanf(" %29[^\n]", comando);
        
        
        // adiciona jogador novo
        if(strncmp(comando, "add", strlen("add")) == 0) {
            sscanf(comando, "add %14[^ ] %14[^\n]", username, password);
            //printf("'%s' -- '%s'\n", username, password);
            if(strlen(username) < 1 || strlen(password) < 1){
                printf("Erro de sintaxe, porfavor escreva 'add USERNAME PASSWORD'!\n");
            }else{
                if(verificaUser(username, buffer) == 1){
                    printf("Erro username já está a ser utilizado, porfavor escolhe outro!\n");
                }else{        
                    addUSer(username, password, buffer); //verificaUser(username, fo);
                }
            }
        // sai do servidor                
        } else if(strncmp(comando, "quit", strlen("quit")) == 0){
            close(buffer);
            exit(0);
        // apago o ecrã
        } else if(strncmp(comando, "clear", strlen("clear")) == 0){
            system("clear");
        // mostra todos os jogadores registados e passwords(TODO mostrar só os nomes de utilizador)
        } else if(strncmp(comando, "users", strlen("users")) == 0){
            allUsers(buffer);
        // mostra jogador passado por argumento
        } else if(strncmp(comando, "user", strlen("user")) == 0){
            if(sscanf(comando, "user %14[^\n]", username) != EOF)
                procuraUser(username, buffer);
                //printf("Função ainda não implementada!\n");
        }

    }       
    close(buffer);
    return 0;
}