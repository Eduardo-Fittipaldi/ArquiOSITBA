#ifndef SYSCALL_INTERFACE_H
#define SYSCALL_INTERFACE_H

typedef unsigned long qword;

qword _syscall(qword id, qword arg1, qword arg2, qword arg3);

#endif //SYSCALL_INTERFACE_H
