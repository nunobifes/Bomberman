#include "incl/server.h"


int main(){



    signal(SIGINT, trataSinal);
    signal(SIGTSTP, trataSinal);

    //initscr();
    //clear();
    //raw();

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

    // TParede mapa[54][24]; //forma 1 de criar o array de structs

    //forma 2 de criar o array de strcuts
    /*TParede** mapa;
    mapa = (TParede**)malloc(sizeof(TParede*) * 24);
    for(int i = 0; i<24; i++){
        mapa[i] = (TParede*)malloc(sizeof(TParede)*54);
    }*/
    // a shell

    //system("clear");
    char comando[50];
    char username[15], password[15], cmd[15], argum[30];
    
    while(1) {
        
        printf("bomberman@server $ ");
        scanf(" %49[^\n]", comando);
        sscanf(comando, "%14s %29[^\n]", cmd, argum);
        //scanw(comando, "%14s %29[^\n]", cmd, argum);
        // adiciona jogador novo
        if(strcmp(cmd, "add") == 0) {
            sscanf(argum, "%14[^ ] %14[^\n]", username, password);
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
                    addUser(username, password);
                    *username = 0;
                    *password = 0;
                }
            }                
        }
        // sai do servidor
        if(strcmp(cmd, "shutdown") == 0){
            exit(0);
        }
        // apago o ecrã
        if(strcmp(cmd, "clear") == 0){
            system("clear");
        }
        // mostra todos os jogadores registados
        if(strcmp(cmd, "users") == 0){
            allUsers();
        }
        // mostra jogador passado por argumento
        if(strcmp(cmd, "user") == 0){
            if(sscanf(argum, "%29[^\n]", username) != EOF)
                procuraUser(username);
                *username = 0;
        }
        if(strcmp(cmd, "kick") == 0){
            if(sscanf(argum, "%29[^\n]", username) != EOF)
            //kickUser(username);
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        }
        if(strcmp(cmd, "game") == 0){
            //showGame();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        }
        if(strcmp(cmd, "shutdown") == 0){
            //shutdown();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        }
        if(strcmp(cmd, "map") == 0){
            //mudaMap();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        }
        
    }
    //clrtoeol();
	//refresh();
	//endwin();
    return 0;
}