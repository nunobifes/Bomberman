#include "incl/server.h" // server.h inclui as estruturas e os prototipos das funções em incl/funcoes.c




int main(){

    

    signal(SIGINT, trataSinal); // manda o sinal SIGINT(ctr+c) para a função trataSinal
    signal(SIGTSTP, trataSinal); // manda o sinal SIGINT(ctr+z) para a função trataSinal
    
    //utilizador* utilizadores;
    //utilizadores = (utilizador*)malloc(sizeof(utilizador) *10);
    leficheiro();
    //initscr();
    //clear();
    //nobreak();
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
    leficheiro();
    system("clear"); // função de sistema para limpar  o ecrã
    char comando[50]; // buffer para escrever o comando completo (cmd + argum)
    char username[15], password[15], cmd[15], argum[30]; // strings para guardar o username, password, o comando(cmd) e os argumentos(argum)
    while(1) { // enquanto estiver a correr vai fazer ...
        
        
        printf("bomberman@server $ "); // imprime 'bomberman@server $ ' no ecrã
        scanf(" %49[^\n]", comando); // lê o comando completo (cmd + argum)
        sscanf(comando, "%14s %29[^\n]", cmd, argum); // lê de comando uma string com um maximo de 14 bytes(cmd) e uma string com um maximo de 29 bytes e espera por um enter'\n'(argum) no formato "%14s %29[^\n] e guarda cada um nas suas variaveis
        
        
        // adiciona jogador novo
        if(strcmp(cmd, "add") == 0) { // se cmd for igual a "add" continua
            sscanf(argum, "%14[^ ] %14[^\n]", username, password); // lê de argum uma string com um maximo de 14 bytes ate um espaço e escreve em username e lê uma string com um maximo de 14 bytes até um enter'\n' e escreve em password
            
            if(strlen(username) < 1 || strlen(password) < 1){  // compara se o tamanho de username ou de password for inferior a 1 devolve erro de sintaxe
                perror("Erro de sintaxe, por favor escreva 'add <username> <password>'!\n");
                *username = 0; // dá clear ao username
                *password = 0; // "" "" "" "" password
            
            }else{
                
                if(verificaUser(username) == 1){ // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                    perror("Erro username já está a ser utilizado, porfavor escolhe outro!\n");
                    *username = 0; // dá clear ao username
                    *password = 0; // "" "" "" "" password
                
                }else{
                    addUser(username, password); // chama a função addUser(username, password) (ver funcoes.c) para adicionar o username e a password ao ficheiro
                    *username = 0; // dá clear ao username
                    *password = 0; // "" "" "" "" password

                }
            }                
        
        
        // sai do servidor
        }else if(strcmp(cmd, "shutdown") == 0){ // se cmd for igual a "shutdown" continua
            fechaFich();
            exit(0); // sai do servidor
        
        
        // apago o ecrã
        }else if(strcmp(cmd, "clear") == 0){ // se cmd for igual a "clear" continua
            system("clear"); // limpa o ecrã
        
        
        // mostra todos os jogadores registados
        }else if(strcmp(cmd, "users") == 0){ // se cmd for igual a "users" continua
            allUsers(); // chama a função allUsers() (ver funcoes.c) e mostra o username de todos os users registados
        
        
        // mostra jogador passado por argumento
        }else if(strcmp(cmd, "user") == 0){ // se cmd for igual a "user" continua
            if(sscanf(argum, "%29[^\n]", username) != EOF) // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua
                if(strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'user <username>'!\n");
                else {
                    if(verificaUser(username) == 0 ){ // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                        perror("Erro username não existe, use <users> para ver os utilizadores registados!\n");
                        *username = 0; // dá clear ao username
                    }else{
                        procuraUser(username); // chama a função procuraUSer(username) (ver funcoes.c) e devolve uma string com informação desse user
                        *username = 0; // dá clear ao username
                    }
                }
        // dá kick ao jogador user        
        }else if(strcmp(cmd, "kick") == 0){ // se cmd for igual a "kick" continua
            if(sscanf(argum, "%29[^\n]", username) != EOF){ // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua
                
                if(strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'kick <username>'!\n");
                else {
                    if(verificaUser(username) == 0 ){ // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                        perror("Erro username não existe, use <users> para ver os utilizadores registados!\n");
                        *username = 0; // dá clear ao username
                    }else{
                        //kickUser(username);
                        printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
                        *username = 0; // dá clear ao username
                    }
        
                }
            }
    
        // mostra a informação sobre o jogo a decorrer
        }else if(strcmp(cmd, "game") == 0){ // se cmd for igual a "game" continua
            //showGame();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        
        
        // muda o mapa do jogo para um escolhido por o user
        }else if(strcmp(cmd, "map") == 0){ // se cmd for igual a "map" continua
            //mudaMap();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        
        
        }else if(strcmp(cmd, "help") == 0){ // se cmd for igual a "help" continua
            printf("os comandos disponiveis são:\n add <username> <password>\n remove <username>\n users\n user <username>\n kick <username>\n shutdown\n clear\n game\n map\n help\n");
        
        
        }else if(strcmp(cmd, "remove") == 0){ // se cmd for igual a "help" continua
            if(sscanf(argum, "%29[^\n]", username) != EOF) // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua
                if(strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'remove <username>'!\n");
                else{
                    removeUser(username);
                }
    
        } else { 
            printf("server: comando não encontrado: %s (Para ajuda execute 'help')\n", cmd);
        }
    }
    //clrtoeol();
	//refresh();
	//endwin();

    return 0;
}