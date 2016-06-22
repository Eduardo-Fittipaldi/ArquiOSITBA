#include <shell_commands.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "stdio.h"

extern command_t command_list[COMMANDS_AMOUNT];

static char buffer[BUFFER_SIZE];
static char buffer_pos = 0;

static void emptyBuffer();
static void printLinestart();
static char bufferIsEmpty();
static char* formatBuffer();
static void addCommand(command_id, command_fn, char*, char*);
static void executeCommand();
static void setCommands();

void initShell(void){
    printf("WELCOME TO ARQUIOS.\n");
    emptyBuffer();
    setCommands();
    printLinestart();
}

void parseCommand() {
    int i = 0, found = 0;
    char * arg = formatBuffer();

    if (arg == buffer){
        return;
    }

    while(i < COMMANDS_AMOUNT && !found){
        if (!strcmp(command_list[i].name, buffer)) {
            found = 1;
        }else{
            i++;
        }
    }
    if(found){
        command_list[i].fnc(arg);
    }

}

void updateShell() {
    char key = getchar();

    if (key <= 0) return;

    switch (key) {
        case '\n':
            putchar('\n');
            parseCommand();
            printLinestart();
            emptyBuffer();
            break;
        case '\b':
            if (buffer_pos > 0) {
                putchar('\b');
                buffer[--buffer_pos] = 0;
            }
            break;
        case ' ':		// no imprimo ni agrego al buffer los espacios iniciales
        case '\t':
            if (buffer_pos == 0) {
                return;
            }
        default:
            putchar(key);
            if (buffer_pos == BUFFER_SIZE) {
                buffer_pos = 0;
            }
            buffer[buffer_pos++] = key;
            break;
    }
}

static void emptyBuffer(void){

    int i = 0;
    while(i < BUFFER_SIZE){
        buffer[i++] = 0;
    }
    buffer_pos = 0;
    return;

}

static void addCommand(command_id id, command_fn fnc, char* name, char* desc){
    command_list[id].id = id;
    command_list[id].fnc = fnc;
    command_list[id].name = name;
    command_list[id].desc = desc;
}

static void setCommands(){
    addCommand(ECHO,echo,"echo","echo [string] \n Prints a given string.");
    addCommand(HELP,help,"help","help [command] \n Gives information on a given command.");
    addCommand(FRACTAL,fractal,"fractal"," fractal [type] \n Types: sierp, julia \n Enters video mode and prints a fractal on screen");
}

static char* formatBuffer(){
    char command_read = 0;
    int read_pos = 0;
    int write_pos = 0;

    while(read_pos < BUFFER_SIZE && buffer[read_pos] != 0){
        switch(command_read){
            case 0:
                if(isspace(buffer[read_pos])){
                    command_read = 1;
                    buffer[write_pos++] = 0;
                }else{
                    buffer[write_pos++] = buffer[read_pos];
                }
                read_pos++;
                break;
            case 1:
                if(!isspace(buffer[read_pos])){
                    return &buffer[read_pos];
                }
                read_pos++;
                break;
        }
    }
    return buffer;
}

static char bufferIsEmpty(){
    return buffer[0] == 0;
}

static void printLinestart(void){
    printf("ArquiOS>");
}

