#ifndef SYSCALLS_H
#define SYSCALLS_H

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
#define STDDATA 1

void write(unsigned int channel, const void * source, unsigned int size);
void read(unsigned int channel, const void * dest, unsigned int size);
void video(void);
void paintPixel(unsigned int x, unsigned int y, unsigned long color);

#endif //SYSCALLS_H
