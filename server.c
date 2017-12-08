#include "incl/server.h" // server.h inclui as estruturas e os prototipos das funções em incl/funcoes.c


int main()
{
    pi = 0;
    online = (login*)malloc(sizeof(login) * 10);
    utilizadores = (utilizador*)malloc(sizeof(utilizador) * 50);


    if(access("fifos/fifo_server", F_OK) != 0){
        if (mkfifo("fifos/fifo_server", 0777) == -1){
            perror("named pipe já existe");
            return -1;    
        }
    }
    if(pthread_create(&id, NULL, leituraPipe, NULL) != 0)
        perror("Erro na criação da thread");

    signal(SIGINT, trataSinal);  // manda o sinal SIGINT(ctr+c) para a função trataSinal
    signal(SIGTSTP, trataSinal); // manda o sinal SIGINT(ctr+z) para a função trataSinal
    

    // TParede mapa[54][24]; //forma 1 de criar o array de structs

    //forma 2 de criar o array de strcuts
    /*TParede** mapa;
    mapa = (TParede**)malloc(sizeof(TParede*) * 24);
    for(int i = 0; i<24; i++){
        mapa[i] = (TParede*)malloc(sizeof(TParede)*54);
    }*/

    // a shell
    shell();

    return 0;
}