#include <stdarg.h>

#ifndef STDIO_H
#define STDIO_H

void putchar(char c);
void fputc(unsigned int channel, char c);
int puts(char * str);
int fputs(unsigned int channel, char * str);
int fputsn(unsigned int channel, char * str, unsigned int n);
int printf(const char * fmt, ...);
int fprintf(unsigned int channel, const char * fmt, ...);
int vfprintf(unsigned int channel, const char * fmt, va_list ap);

int getchar(void);
int fgetc(unsigned int channel);
char * gets(char * str, int n);
char * fgets(unsigned int channel, char * str, int n);
int scanf(const char * fmt, ...);
int fscanf(unsigned int channel, const char * fmt, ...);
int sscanf(const char * str, const char * fmt, ...);
int vfscanf(unsigned int channel, const char * fmt, va_list ap);


#endif //STDIO_H
