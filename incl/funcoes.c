#include "server.h"

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