#include "incl/server.h"

int main(){

    //player jogador;
    //jogador.vidas = 3;
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
    char comando[30];
    char username[15], password[15];
    
    while(1) {
        
        printf("bomberman@server $ ");
        scanf(" %29[^\n]", comando);
        
        
        // adiciona jogador novo
        if(strncmp(comando, "add", strlen("add")) == 0) {
            sscanf(comando, "add %14[^ ] %14[^\n]", username, password);
            if(strlen(username) < 1 || strlen(password) < 1){
                printf("Erro de sintaxe, porfavor escreva 'add USERNAME PASSWORD'!\n");
                *username = 0;
                *password = 0;
            }else{
                if(verificaUser(username) == 1){
                    printf("Erro username já está a ser utilizado, porfavor escolhe outro!\n");
                    *username = 0;
                    *password = 0;
                }else{        
                    addUSer(username, password); //verificaUser(username, fo);
                    *username = 0;
                    *password = 0;
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
                *username = 0;
        }

    }       
    return 0;
}