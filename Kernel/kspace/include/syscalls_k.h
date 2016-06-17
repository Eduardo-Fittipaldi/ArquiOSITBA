#ifndef SYSCALLS_K_H
#define SYSCALLS_K_H

#define SYS_EXIT 	0
#define SYS_READ 	1
#define SYS_WRITE 	2
#define SYS_VIDEO	3

//OUTPUT CHANNELS
#define O_DEF_CNL 0
#define O_ERR_CNL 1
#define O_DBG_CNL 2

//INPUT CHANNELS
#define I_DEF_CNL 0

void sys_write(char channel, char * string, unsigned int size);
void sys_read(char channel, char * dest, unsigned int size);



#endif /* SYSCALLS_K_H */
