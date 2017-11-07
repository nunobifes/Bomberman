#include "server.h"



void trataSinal(int s){ // se receber o sinal SIGINT ou SIGTSTP a função trataSinal faz com que esses sinais não façam nada
    if(s == SIGINT || s == SIGTSTP);
}

int abreFich(){ // função para abrir o ficheiro
    
    int fo;
    // Abrir ficheiro users para leitura e escrita e verifica se ele existe
    fo = open("users.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG); // abre o ficheiro users.txt com as flags para lere e escrever e se não existir criar o ficheiro e com os modos de permisão para ler, escrever e exucutar para o USER, o GROUP e o OTHERS
    if (fo == -1) { // se retornar erro(-1)
        perror("ERRO!!!"); 
        return -1;
    }
    return fo;
}
// estas funções ainda não estão implementadas
void kickUser(char *user);
void showGame();
void shutdown();
void mudaMap();
// -------------------------------------------

void allUsers(){ // função mostra todos os usernames registados
    

    //outra maneira para apresentar os users e passwords usando api unix
    /*int fich = abreFich();
    off_t ret;
    ret = lseek(fich, 0, SEEK_END);
    char *content = mmap(NULL, ret, PROT_READ | PROT_WRITE, MAP_PRIVATE, fich, 0);
    
    printf("%s", content);
    close(fich);*/
    
    int fich = abreFich(); // guarda 
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

    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        sscanf(line, "%s %s\n", userC, passC);
        if(strcmp(userC, user) == 0){
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
    static char ret[50];
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
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

void removeUser(char *user){
    
    int fich = abreFich();
    FILE *fo = fdopen(fich, "r+");
    int fd = open("users-temp.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    char userC[15], passC[15], line[50], BUFFER[50]="";
    static char ret[50];
    while (1) {
        if(fgets(line,150, fo) == NULL)
            break;       
        sscanf(line, "%s %s\n", userC, passC);
            
        if(strcmp(userC, user) != 0){
            sprintf(BUFFER, "%s %s\n", userC, passC);
            close(fich);
        }
        printf("%s", BUFFER);
        //for(int i = 0; i != nUsers; i++){
            //addUser(userC, passC);
        //}
    }
    close(fich);
}

void addUser(char *user, char *pass){

    int fich = abreFich();
    char userPass[50];
    sprintf(userPass, "%s %s\n", user, pass);
        
    off_t ret;
    ret = lseek(fich, 0, SEEK_END);
    
    if(ret != (off_t) -1)
        write(fich, userPass, strlen(userPass));
        
    close(fich);
}