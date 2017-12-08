#ifndef STRUCTS
#define STRUCTS

typedef struct
{
    pid_t userpid;
    char username[15];
    char password[15];
} login;

typedef struct
{

    pid_t userpid;
    char resposta[50];
    int tipo;

} respCliente;

typedef struct{

    int tipo; // 0 - erro; 1 - sucesso; .....
    char aviso[100];

} mensagem;

typedef struct
{

    char username[15];
    char password[15];
    int userID;

} utilizador;

typedef struct
{

    char nome[15];
    int vidas; // 3 vidas base
    int pontuacao;
    int mbomba;
    int items;
    int x, y;

} player;

typedef struct
{

    int vivo;
    int drop;
    int x, y;

} npc;

typedef struct
{

    int tipo_parede; //0 -> vazio, 1 -> parede não destrutivel, 2 -> parede destrutivel -> 3 vazio c/ drop
    int explosao;
    int x, y;

} TParede;

typedef struct
{

    int tempo;
    int items;
    int npcs;

} info;

#endif