#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

typedef int (*command_fn)(char * arg);

//RECORDAR CAMBIAR COMMANDS_AMOUNT O SE VA TODO AL CARAJO
typedef enum{
    ECHO,
    HELP,
    FRACTAL
} command_id;

typedef struct{
    command_id id;
    command_fn fnc;
    const char* name;
    const char* desc;
} command_t;

#define COMMANDS_AMOUNT 3

int echo(char * arg);
int help(char * arg);
int fractal(char * arg);

#endif //SHELL_COMMANDS_H
