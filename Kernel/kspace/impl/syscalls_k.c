#include <include/syscalls_k.h>
#include <types.h>
#include <vga_funcs.h>
#include <Kernel/video/include/vga_funcs.h>
#include <Kernel/kspace/include/keyboard_k.h>

void sys_write(char channel, char * string, unsigned int size){
    char foreground;
    char background;
    unsigned int curr = 0;

    switch(channel){
        case O_DEF_CNL:
            foreground = WHITE;
            background = BLACK;
            break;
        case O_ERR_CNL:
            foreground = BLACK;
            background = RED;
            break;
        case O_DBG_CNL:
            foreground = GREEN;
            background = BLACK;
            break;
        default:
            return;
    }

    while(curr < size && string[curr] != 0){
        putchar(string[curr],foreground,background);
    }
}

void sys_read(char channel, char * dest, unsigned int size){
    unsigned int curr = 0;
    switch(channel){
        case I_DEF_CNL:
            while(curr < size && isEmpty()){
                dest[curr++] = getKey();
            }
    }
}