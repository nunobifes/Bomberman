#include "server.h"
#include "cliente.h"
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------


//                        ______     ________    _______     __     __   ________    _______  
//                       /      \   |        \  |       \   |  \   |  \ |        \  |       \ 
//                      |  $$$$$$\  | $$$$$$$$  | $$$$$$$\  | $$   | $$ | $$$$$$$$  | $$$$$$$\
//                      | $$___\$$  | $$__      | $$__| $$  | $$   | $$ | $$__      | $$__| $$
//                       \$$    \   | $$  \     | $$    $$   \$$\ /  $$ | $$  \     | $$    $$
//                       _\$$$$$$\  | $$$$$     | $$$$$$$\    \$$\  $$  | $$$$$     | $$$$$$$\
//                      |  \__| $$  | $$_____   | $$  | $$     \$$ $$   | $$_____   | $$  | $$
//                       \$$    $$  | $$     \  | $$  | $$      \$$$    | $$     \  | $$  | $$
//                        \$$$$$$    \$$$$$$$$   \$$   \$$       \$      \$$$$$$$$   \$$   \$$


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------                                                             
void trataSinal(int s){ // se receber o sinal SIGINT ou SIGTSTP a função trataSinal faz com que esses sinais não façam nada
    if (s == SIGINT)
        ; //printf("");
    if( s == SIGTSTP)
        ;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
FILE *abreFich(){ // função para abrir o ficheiro

    int fo;
    // Abrir ficheiro users para leitura e escrita e verifica se ele existe
    fo = open("users.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG); // abre o ficheiro users.txt com as flags para lere e escrever e se não existir criar o ficheiro e com os modos de permisão para ler, escrever e exucutar para o USER, o GROUP e o OTHERS
    if (fo == -1)
    { // se retornar erro(-1)
        perror("ERRO!!!");
        return NULL;
    }
    FILE *fd = fdopen(fo, "r+");
    return fd;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void leficheiro(){

    FILE *fich = abreFich();

    int j = 0;

    int size;

    struct stat st;
    stat("users.txt", &st);
    size = st.st_size;

    if (size > 1)
    {
        while (!feof(fich))
        {
            fscanf(fich, "%s %s", utilizadores[j].username, utilizadores[j].password);
            utilizadores[j].userID = j + 1;
            j++;
        }
    }

    fclose(fich);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void removeUser(char *user){
    int tam = 0;
    while (utilizadores[tam].userID != 0)
        tam++;

    int pos;

    for (int i = 0; i < tam; i++)
    {
        if (strcmp(user, utilizadores[i].username) == 0)
            pos = i;
    }

    if (pos == tam - 1)
    {

        strcpy(utilizadores[pos].password, "");
        strcpy(utilizadores[pos].username, "");
        utilizadores[pos].userID = 0;
        printf("O Utilizador '%s' foi removido com sucesso!\n", user);
    }
    else
    {
        for (int i = pos + 1; i != tam - 1; i++)
        {
            utilizadores[i - 1] = utilizadores[i];
            utilizadores[i - 1].userID--;
        }
        utilizadores[tam - 2] = utilizadores[tam - 1];
        utilizadores[tam - 2].userID--;
        strcpy(utilizadores[tam - 1].password, "");
        strcpy(utilizadores[tam - 1].username, "");
        utilizadores[tam - 1].userID = 0;
        printf("O Utilizador '%s' foi removido com sucesso!\n", user);
    }
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
// estas funções ainda não estão implementadas
void showGame();
void mudaMap();
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------

void allUsers(){ // função mostra todos os usernames registados

    int j = 0;
    while (utilizadores[j].userID != 0)
        j++;

    printf("Utilizadores Registados:\n\n");

    if (utilizadores[0].userID == 0)
    {
        printf("\tNão existem Utilizadores Registados\n\n");
    }
    else
    {
        for (int i = 0; i < j; i++)
            printf("\t%d: %s\n", utilizadores[i].userID, utilizadores[i].username);
        printf("\n");
    }
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
int verificaUser(char *user){

    int j = 0;
    while (utilizadores[j].userID != 0)
        j++;

    for (int i = 0; i < j; i++)
    {
        if (strcmp(utilizadores[i].username, user) == 0)
        {
            return 1;
        }
    }

    return 0;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
char procuraUser(char *user){

    int j = 0;
    while (utilizadores[j].userID != 0)
        j++;

    for (int i = 0; i < j; i++)
    {
        if (strcmp(utilizadores[i].username, user) == 0)
        {
            printf("\n\tUserID: %d\n\tUsername: %s\n\tPassword: %s\n\n", utilizadores[i].userID, utilizadores[i].username, utilizadores[i].password);
        }
    }
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void kickUser(char *user){

    int tam = 0;
    while (online[tam].userpid != 0)
        tam++;

    int pos;

    for (int i = 0; i < tam; i++)
    {
        if (strcmp(user, online[i].username) == 0)
            pos = i;
    }
    posx = online[pos].userpid;
    
    if (pos == tam - 1)
    {
        
        strcpy(online[pos].password, "");
        strcpy(online[pos].username, "");
        online[pos].userpid = 0;
        pi--;
    }
    else
    {
        for (int i = pos + 1; i != tam - 1; i++)
        {
            online[i - 1] = online[i];
            pi--;
        }
        online[tam - 2] = online[tam - 1];
        pi--;
        strcpy(online[tam - 1].password, "");
        strcpy(online[tam - 1].username, "");
        online[tam - 1].userpid = 0;
    }
    
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void addUser(char *user, char *pass){

    int j = 0;
    while (utilizadores[j].userID != 0)
        j++;

    strcpy(utilizadores[j].username, user);
    strcpy(utilizadores[j].password, pass);
    utilizadores[j].userID = j + 1;
    printf("O Utilizador '%s' foi adicionado com sucesso!\n", utilizadores[j].username);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void fechaFich(){

    remove("users.txt");
    FILE *fich = abreFich();

    int j = 0;

    while (utilizadores[j].userID != 0)
        j++;

    for (int i = 0; i < j; i++)
    {
        if (i + 1 == j)
            fprintf(fich, "%s %s", utilizadores[i].username, utilizadores[i].password);
        else
        {
            fprintf(fich, "%s %s\n", utilizadores[i].username, utilizadores[i].password);
        }
    }

    fclose(fich);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void mostraLogados(){

    int j = 0;
    while (online[j].userpid != 0)
        j++;

    printf("Utilizadores Logados:\n\n");

    if (online[0].userpid == 0)
    {
        printf("\tNão existem Utilizadores Logados\n\n");
    }
    else
    {

        for (int i = 0; i < j; i++)
            printf("\t%d: %s\n", online[i].userpid, online[i].username);
        printf("\n");
    }

}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void sair(){
    pthread_cancel(id);
    fechaFich();
    close(fd);
    unlink("fifos/fifo_server");
    for(int i = 0; i < pi; i++)
        kill(online[i].userpid, SIGUSR1);
    //pthread_join(id, NULL);
    sleep(1);
    exit(EXIT_SUCCESS);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void* leituraPipe(void *p){
    
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    fd = open("fifos/fifo_server", O_RDONLY);
        if (fd == -1){
            perror("Erro a abrir named pipe");
            return NULL;
        }
    
    char buffer[50];

    int erro_username = 0;
    int erro_password = 0;
    
    char username[15], password[15];
    int pos = 0;
    while(1){    
        int erro_existe = 0;
        read(fd, &lgin, sizeof(lgin));
        
        if(lgin.tipo == 1){
            sscanf(lgin.resposta, "%s %s", username, password);
            sprintf(fifo_cliente, "fifos/fifo_%d", lgin.userpid);
            
            flc = open(fifo_cliente, O_WRONLY);        
            if (flc == -1){
                perror("Erro a abrir named pipe");
                return NULL;
            }

            int n;
            int ohh;
            int j = 0;
            while (utilizadores[j].userID != 0)
                j++;

            for(int i = 0; i < pi; i++){
                if(strcmp(username, online[i].username) == 0){
                    msg.tipo = 0;
                    strcpy(msg.aviso, "\tUtilizador já está online!");
                    write(flc, &msg, sizeof(msg));
                    erro_existe = 1;
                }
            }
            
            if(erro_existe == 0){
                for(int i = 0; i < j; i++){
                    if(strncmp(username, utilizadores[i].username, strlen(utilizadores[i].username)) != 0){
                        ohh = 1;
                       
                    }else{
                        n = i;
                        erro_username = 1;
                        break;
                    }
                    
                    
                }
                if(ohh == 1){
                         msg.tipo = 0;
                        strcpy(msg.aviso, "Username não existe!");
                        sprintf(msg.aviso, "\tUsername '%s' não existe!", username);
                        write(flc, &msg, sizeof(msg));
                    }
            }
        
            if(erro_username == 1){
                if(strncmp(password, utilizadores[n].password, strlen(utilizadores[n].password)) != 0){
                    msg.tipo = 0;
                    strcpy(msg.aviso, "\tPassword errada!");
                    write(flc, &msg, sizeof(msg));
                }else{
                    erro_password = 1;
                }
            }
        
            if(erro_password == 1){
                msg.tipo = 1;
                strcpy(msg.aviso, "\tSucesso, login efectuado!");
                write(flc, &msg, sizeof(msg));
                strcpy(online[pi].username, username);
                strcpy(online[pi].password, password);
                online[pi].userpid = lgin.userpid;
                pi++;
            }
        
            erro_username = 0;
            erro_password = 0;
            lgin.tipo = 0;
            close(flc);
        }

        if(lgin.tipo == 2){

            char username[15];
            for(int i = 0; i < pi; i++){
                if(lgin.userpid == online[i].userpid)
                    strcpy(username, online[i].username);
            }
            kickUser(username);
            lgin.tipo = 0;
        }
    }
    close(fd);
    return NULL;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void shell(){
    leficheiro();
    system("clear");                                     // função de sistema para limpar  o ecrã
    char comando[50];                                    // buffer para escrever o comando completo (cmd + argum)
    char username[15], password[15], cmd[15], argum[30]; // strings para guardar o username, password, o comando(cmd) e os argumentos(argum)
    while (1)
    { // enquanto estiver a correr vai fazer ...

        printf("bomberman@server $ ");                // imprime 'bomberman@server $ ' no ecrã
        scanf(" %49[^\n]", comando);                  // lê o comando completo (cmd + argum)
        sscanf(comando, "%14s %29[^\n]", cmd, argum); // lê de comando uma string com um maximo de 14 bytes(cmd) e uma string com um maximo de 29 bytes e espera por um enter'\n'(argum) no formato "%14s %29[^\n] e guarda cada um nas suas variaveis

        // adiciona jogador novo
        if (strcmp(cmd, "add") == 0)
        {                                                          // se cmd for igual a "add" continua
            sscanf(argum, "%14[^ ] %14[^\n]", username, password); // lê de argum uma string com um maximo de 14 bytes ate um espaço e escreve em username e lê uma string com um maximo de 14 bytes até um enter'\n' e escreve em password

            if (strlen(username) < 1 || strlen(password) < 1)
            { // compara se o tamanho de username ou de password for inferior a 1 devolve erro de sintaxe
                perror("Erro de sintaxe, por favor escreva 'add <username> <password>'!\n");
                *username = 0; // dá clear ao username
                *password = 0; // "" "" "" "" password
            }
            else
            {
                if (strlen(username) > 13 || strlen(password) > 13)
                {
                    perror("Erro de sintaxe, <username> e <password> só podem ter no maximo 13 caracteres!\n");
                    *username = 0; // dá clear ao username
                    *password = 0; // "" "" "" "" password
                }
                else
                {
                    if (verificaUser(username) == 1)
                    { // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                        perror("Erro username já está a ser utilizado, porfavor escolhe outro!\n");
                        *username = 0; // dá clear ao username
                        *password = 0; // "" "" "" "" password
                    }
                    else
                    {
                        addUser(username, password); // chama a função addUser(username, password) (ver funcoes.c) para adicionar o username e a password ao ficheiro
                        *username = 0;               // dá clear ao username
                        *password = 0;               // "" "" "" "" password
                    }
                }
            }

        // sai do servidor
        }
        else if (strcmp(cmd, "shutdown") == 0)
        { // se cmd for igual a "shutdown" continua
            sair();

        // apago o ecrã
        }
        else if (strcmp(cmd, "clear") == 0)
        {                    // se cmd for igual a "clear" continua
            system("clear"); // limpa o ecrã

            // mostra todos os jogadores registados
        }
        else if (strcmp(cmd, "users") == 0)
        {               // se cmd for igual a "users" continua
            allUsers(); // chama a função allUsers() (ver funcoes.c) e mostra o username de todos os users registados

            // mostra jogador passado por argumento
        }
         else if (strcmp(cmd, "logados") == 0)
        {               // se cmd for igual a "users" continua
            mostraLogados(); // chama a função allUsers() (ver funcoes.c) e mostra o username de todos os users registados

            // mostra jogador passado por argumento
        }
        else if (strcmp(cmd, "user") == 0)
        {                                                   // se cmd for igual a "user" continua
            if (sscanf(argum, "%29[^\n]", username) != EOF) // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua
                if (strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'user <username>'!\n");
                else
                {
                    if (verificaUser(username) == 0)
                    { // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                        perror("Erro username não existe, use <users> para ver os utilizadores registados!\n");
                        *username = 0; // dá clear ao username
                    }
                    else
                    {
                        procuraUser(username); // chama a função procuraUSer(username) (ver funcoes.c) e devolve uma string com informação desse user
                        *username = 0;         // dá clear ao username
                    }
                }
            // dá kick ao jogador user
        }
        else if (strcmp(cmd, "kick") == 0)
        { // se cmd for igual a "kick" continua
            if (sscanf(argum, "%29[^\n]", username) != EOF)
            { // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua

                if (strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'kick <username>'!\n");
                else
                {
                    if (verificaUser(username) == 0)
                    { // chama a função verificaUser(username)(ver funcoes.c) e compara com 1 e se for devolve erro de username já a ser utilizado
                        perror("Erro username não existe, use <users> para ver os utilizadores registados!\n");
                        *username = 0; // dá clear ao username
                    }
                    else
                    {
                        kickUser(username);
                        kill(posx, SIGTSTP);
                        //printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
                        *username = 0; // dá clear ao username
                    }
                }
            }

            // mostra a informação sobre o jogo a decorrer
        }
        else if (strcmp(cmd, "game") == 0)
        { // se cmd for igual a "game" continua
            //showGame();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);

            // muda o mapa do jogo para um escolhido por o user
        }
        else if (strcmp(cmd, "map") == 0)
        { // se cmd for igual a "map" continua
            //mudaMap();
            printf("O comando '%s' foi executado mas ainda não está implementado!\n", cmd);
        }
        else if (strcmp(cmd, "help") == 0)
        { // se cmd for igual a "help" continua
            printf("os comandos disponiveis são:\n add <username> <password>\n remove <username>\n users\n user <username>\n logados\n kick <username>\n shutdown\n clear\n game\n map\n help\n");
        }
        else if (strcmp(cmd, "remove") == 0)
        {                                                   // se cmd for igual a "help" continua
            if (sscanf(argum, "%29[^\n]", username) != EOF) // vai se(ler de argumento uma string de tamanho maximo de 29 bytes até receber um enter'\n' e guarda em username) devolver diferente de EOF continua
                if (strlen(username) < 1)
                    perror("Erro de sintaxe, por favor escreva 'remove <username>'!\n");
                else
                {
                    removeUser(username);
                }
        }
        else
        {
            printf("server: comando não encontrado: %s (Para ajuda execute 'help')\n", cmd);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------


//                        ______     __          ______      ________    __    __    ________    ________ 
//                       /      \   |  \        |      \    |        \  |  \  |  \  |        \  |        \
//                      |  $$$$$$\  | $$         \$$$$$$    | $$$$$$$$  | $$\ | $$   \$$$$$$$$  | $$$$$$$$
//                      | $$   \$$  | $$          | $$      | $$__      | $$$\| $$     | $$     | $$__    
//                      | $$        | $$          | $$      | $$  \     | $$$$\ $$     | $$     | $$  \   
//                      | $$   __   | $$          | $$      | $$$$$     | $$\$$ $$     | $$     | $$$$$   
//                      | $$__/  \  | $$_____    _| $$_     | $$_____   | $$ \$$$$     | $$     | $$_____ 
//                       \$$    $$  | $$     \  |   $$ \    | $$     \  | $$  \$$$     | $$     | $$     \
//                        \$$$$$$    \$$$$$$$$   \$$$$$$     \$$$$$$$$   \$$   \$$      \$$      \$$$$$$$$
                                                                    
                                                                    
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------                                                                    
void *trataCliente(void *p){
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    fcl = open(fifo, O_RDONLY);
    if (fcl == -1){
            perror("Erro a abrir named pipe");
            return NULL;
        } 
    int n;
    while(1){

        read(fcl, &msg, sizeof(msg));
        
            if(msg.tipo == 0){
                //printf("%s", msg.aviso);
                puts(msg.aviso);
                msg.tipo = 2;
            }

            if(msg.tipo == 1){
                breake = 0;
                msg.tipo = 2;
            }
       
        
    }
    close(fcl);
    return NULL;

}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void sairCli(){

    pthread_cancel(id);
    close(fd);
    unlink(fifo);
    exit(EXIT_SUCCESS);

}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void trataSinalCli(int s){
    
    if(s == SIGINT){
        sairCli();
    }
    if(s == SIGUSR1){
        sairCli();
    }
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------