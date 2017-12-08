#include "incl/cliente.h" 



int main(){
    breake = 1;
    char username[15], password[15];

    signal(SIGINT, trataSinalCli);
    signal(SIGTSTP, trataSinalCli);
    fd = open("fifos/fifo_server", O_WRONLY);
    if (fd == -1){
        perror("Erro a abrir named pipe");
        return -1;
    }

    
    lgin.userpid = getpid();
    sprintf(fifo, "fifos/fifo_%d", lgin.userpid);
    if(access(fifo, F_OK) != 0){
        if (mkfifo(fifo, 0777) == -1){
            perror("named pipe já existe");
            return -1;    
        }
    }

    if(pthread_create(&id, NULL, trataCliente, NULL) != 0)
        perror("Erro na criação da thread");

    while(1){
        system("clear");
        lgin.tipo=0;
        sleep(1);
        if(breake == 0)
            break; 
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        sprintf(lgin.resposta, "%s %s", username, password);
        lgin.tipo=1;
        write(fd, &lgin, sizeof(lgin));
        
    }
    
    while(1){
        system("clear");
        printf("\n\t1 - Jogar\n\t2 - Jogar Online\n\t3 - Sair\n");
        printf("\n\nOpção: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                continue;
            case 2:
                continue;
            case 3:
                sprintf(lgin.resposta, " ");
                lgin.tipo=2;
                write(fd, &lgin, sizeof(lgin));
                sairCli();
            default:
                continue;
        }
    }
    sairCli();
    return 0;

}