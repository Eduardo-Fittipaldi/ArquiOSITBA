#include <syscalls_k.h>
#include <types.h>
#include <vga_funcs.h>
#include <vga_funcs.h>
#include <keyboard_k.h>

void syscallHandler(qword mode, qword arg1, qword arg2, qword arg3){
    switch(mode){
        case SYS_WRITE:
            sys_write(arg1,arg2,arg3);
            break;
        case SYS_READ:
            sys_read(arg1,arg2,arg3);
            break;
        case SYS_VIDEO:
            break;
    }
}

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
    while(curr < size && string[curr]){
        putchar(string[curr++],foreground,background);
    }
}

void sys_read(char * dest, unsigned int size, qword arg3) {
    unsigned int curr = 0;
    while (curr < size && !kbBufferIsEmpty()) {
        dest[curr++] = getKey();
    }
}