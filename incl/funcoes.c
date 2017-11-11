#include "server.h"


void trataSinal(int s){ // se receber o sinal SIGINT ou SIGTSTP a função trataSinal faz com que esses sinais não façam nada
    if(s == SIGINT || s == SIGTSTP)
        ;//printf("");
}

FILE *abreFich(){ // função para abrir o ficheiro
    
    int fo;
    // Abrir ficheiro users para leitura e escrita e verifica se ele existe
    fo = open("users.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG); // abre o ficheiro users.txt com as flags para lere e escrever e se não existir criar o ficheiro e com os modos de permisão para ler, escrever e exucutar para o USER, o GROUP e o OTHERS
    if (fo == -1) { // se retornar erro(-1)
        perror("ERRO!!!"); 
        return NULL;
    }
    FILE *fd = fdopen(fo, "r+");
    return fd;
}

void leficheiro(){

    FILE* fich = abreFich();
    
    int j = 0;
   
    int size;

    struct stat st;
    stat("users.txt", &st);
    size = st.st_size;

            if(size > 1){
                while(!feof(fich)){
                    fscanf(fich, "%s %s", utilizadores[j].username, utilizadores[j].password);
                    utilizadores[j].userID = j+1;
                    j++;
                }       
            }

    fclose(fich);

}

// estas funções ainda não estão implementadas
void kickUser(char *user);
void showGame();
void shutdown();
void mudaMap();
// -------------------------------------------

void allUsers(){ // função mostra todos os usernames registados

    int j = 0;
    while(utilizadores[j].userID != 0)
       j++;

    printf("Utilizadores Registados:\n\n");
    
    if(utilizadores[0].userID == 0){
        printf("\tNão existem Utilizadores Registados\n\n");
        
    
    } else {

        for(int i = 0; i<j; i++)
            printf("\t%d: %s\n", utilizadores[i].userID, utilizadores[i].username);
        printf("\n");

    }
    
   
}


    
    
int verificaUser(char *user){

    int j = 0;
    while(utilizadores[j].userID != 0)
       j++;

    for(int i = 0; i<j; i++){
        if(strcmp(utilizadores[i].username, user) == 0){
            return 1;
        }
    }


    return 0;
}



char procuraUser(char *user){

    int j = 0;
    while(utilizadores[j].userID != 0)
       j++;

    for(int i = 0; i<j; i++){
        if(strcmp(utilizadores[i].username, user) == 0){
            printf("\n\tUserID: %d\n\tUsername: %s\n\tPassword: %s\n\n", utilizadores[i].userID, utilizadores[i].username, utilizadores[i].password);
        }
    }
}



void removeUser(char *user){
    
    int tam = 0;
    while(utilizadores[tam].userID != 0)
       tam++;

    int pos;

    for(int i = 0; i<tam; i++){
        if(strcmp(user, utilizadores[i].username) == 0)
            pos = i;
    }    
    
    if(pos == tam-1){
        

        strcpy(utilizadores[pos].password, "");
        strcpy(utilizadores[pos].username, "");
        utilizadores[pos].userID = 0;
        
    } else {
        for(int i = pos + 1; i != tam - 1; i++){
            utilizadores[i-1] = utilizadores[i];
            utilizadores[i-1].userID--;
        }
        utilizadores[tam-2] = utilizadores[tam-1];
        utilizadores[tam-2].userID--;
        strcpy(utilizadores[tam-1].password, "");
        strcpy(utilizadores[tam-1].username, "");
        utilizadores[tam-1].userID = 0;
    }
    
}

void addUser(char *user, char *pass){

    int j = 0;
    while(utilizadores[j].userID != 0)
       j++;
    
    strcpy(utilizadores[j].username, user);
    strcpy(utilizadores[j].password, pass);
    utilizadores[j].userID = j+1;
    printf("O Utilizador '%s' foi adicionado com sucesso!\n", utilizadores[j].username);

}

void fechaFich(){

    remove("users.txt");
    FILE *fich = abreFich();

    int j= 0;

    while(utilizadores[j].userID != 0)
       j++;

    for(int i = 0; i<j; i++){
        if(i+1 == j)
            fprintf(fich, "%s %s", utilizadores[i].username, utilizadores[i].password);
        else{
            fprintf(fich, "%s %s\n", utilizadores[i].username, utilizadores[i].password);
        }
    }   


    fclose(fich);


}