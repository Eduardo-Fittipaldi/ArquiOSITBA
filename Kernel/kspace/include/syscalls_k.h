#ifndef SYSCALLS_K_H
#define SYSCALLS_K_H

#include <types.h>

#define FRACTAL_DATA 0x500000

#define SYS_EXIT 	0
#define SYS_READ 	1
#define SYS_WRITE 	2
#define SYS_VIDEO	3
#define SYS_PAINT   4

//OUTPUT CHANNELS
#define STDOUT 0
#define STDERR 1
#define STDDBG 2

//INPUT CHANNELS
#define STDIN 0
#define STDFRACTAL 1

void syscallHandler(qword mode, qword arg1, qword arg2, qword arg3);
void sys_write(unsigned int channel, char * source, unsigned int size);
void sys_read(unsigned int channel,char * dest, unsigned int size);
void sys_paint(int x, int y, qword color);
void sys_video(qword arg1, qword arg2, qword arg3);


#endif /* SYSCALLS_K_H */
