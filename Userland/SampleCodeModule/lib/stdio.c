#include "syscalls.h"
#include "stdio.h"
#include "limits.h"

#define EOF 0xFF
#define NULL -2
static int print_arg(unsigned int channel, va_list ap, char option);
static int print_hex(unsigned int channel, int hex);
static int print_dec(unsigned int channel, int dec);
static int print_oct(unsigned int channel, int oct);
static int print_bin(unsigned int channel, int bin);
static int num_to_base(unsigned int value, char * buffer, unsigned int base);

void putchar(char c) {
    fputc(STDOUT, c);
}

void fputc(unsigned int channel, char c) {
    write(channel, &c, 1);
}

int puts(char * str) {
    return fputs(STDOUT, str);
}

int fputs(unsigned int channel, char * str) {
    int written = 0;
    while(*str) {
        fputc(channel, *str++);
        written++;
    }
    return written;
}

int fputsn(unsigned int channel, char * str, unsigned int n) {
    int written = 0;
    while(*str && n--){
        fputc(channel, *str++);
        n--;
        written++;
    }
    return written;
}

int printf(const char * fmt, ...) {
    va_list ap;
    int written = 0;

    va_start(ap, fmt);
        written += vfprintf(STDOUT, fmt, ap);
    va_end(ap);

    return written;
}

int fprintf(unsigned int channel, const char * fmt, ...) {
    va_list ap;
    int written = 0;

    va_start(ap, fmt);
        written += vfprintf(channel, fmt, ap);
    va_end(ap);

    return written;
}

int vfprintf(unsigned int channel, const char * fmt, va_list ap) {

    int written = 0;
    char c;

    while ((c = *fmt++) != 0) {
        if (c == '%') {
            char option = *(fmt++);
            written += print_arg(channel, ap, option);
        }
        else {
            fputc(channel, c);
            written++;
        }
    }

    return written;
}

static int print_arg(unsigned int channel, va_list ap, char option) {
    int written = 0;

    switch (option) {
        case 's':
            written += fputs(channel, va_arg(ap, char *));
            break;
        case 'x':
            written += print_hex(channel, va_arg(ap, int));
            break;
        case 'd':
            written += print_dec(channel, va_arg(ap, int));
            break;
        case 'o':
            written = print_oct(channel, va_arg(ap, int));
            break;
        case 'b':
            written = print_bin(channel, va_arg(ap, int));
            break;
        case 'c':
            fputc(channel, va_arg(ap, int) & UCHAR_MAX);
            written++;
            break;
        default:
            return written;		// error de formato
    }

    return written;
}

static int print_hex(unsigned int channel, int num) {
    int digits, written;
    char buffer[20];
    digits =  num_to_base(num, buffer, 16);
    written = fputsn(channel, buffer, digits);
    // fputc(channel, 'h');
    // written++;
    return written;
}

static int print_dec(unsigned int channel, int num) {
    int digits;
    int negative = 0;
    char buffer[20];
    if (num < 0) {
        fputc(channel, '-');
        negative = 1;
        num *= -1;
    }
    digits = num_to_base(num, buffer, 10);
    return fputsn(channel, buffer, digits) + negative;
}

static int print_oct(unsigned int channel, int num) {
    int digits;
    char buffer[20];
    digits =  num_to_base(num, buffer, 8);
    return fputsn(channel, buffer, digits);
}

static int print_bin(unsigned int channel, int num) {
    int digits;
    char buffer[20];
    digits =  num_to_base(num, buffer, 2);
    return fputsn(channel, buffer, digits);
}

static int num_to_base(unsigned int value, char * buffer, unsigned int base) {
    char *p = buffer;
    char *p1, *p2;
    int digits = 0;

    //Calculate characters for each digit
    do {
        int remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    }
    while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}

/*****************************************************/

static int read_arg(unsigned int channel, va_list ap, char option);
static int read_dec(unsigned int channel, int * ptr);
static int read_str(unsigned int channel, char * ptr);

int getchar() {
    return fgetc(STDIN);
}

int fgetc(unsigned int channel) {
    char c;
    read(channel, &c, 1);
    return c;
}

char * gets(char * str, int n) {
    return fgets(STDIN, str, n);
}

char * fgets(unsigned int channel, char * str, int n) {
    char c;
    int read = 0;

    while ((c = fgetc(channel)) != EOF && c != '\n' && read < n) {
        if (c > 0) {
            str[read++] = c;
            fputc(STDOUT, c);
        }
    }

    if (read == 0 && c == EOF) {
        return NULL;
    }

    str[read] = 0;
    return str;
}

int scanf(const char * fmt, ...) {
    va_list ap;
    int read;

    va_start(ap, fmt);
    read = vfscanf(STDIN, fmt, ap);
    va_end(ap);

    return read;
}

int fscanf(unsigned int channel, const char * fmt, ...) {
    va_list ap;
    int read;

    va_start(ap, fmt);
    read = vfscanf(channel, fmt, ap);
    va_end(ap);

    return read;
}

//TODO
int sscanf(const char * str, const char * fmt, ...) {
    return -1;
}

//TODO
int vfscanf(unsigned int channel, const char * fmt, va_list ap) {
    int read = 0;
    char c;

    while ((c = *fmt++) != 0) {
        if (c == '%') {
            char option = *(fmt++);
            if (read_arg(channel, ap, option) == 0) {
                return read;
            }
            read++;
        }
    }

    return read;
}

#define MAX_SIZE 64

static int read_arg(unsigned int channel, va_list ap, char option) {
    int read = 0;
    char * arg;

    switch (option) {
        case 's':
            read = read_str(channel, va_arg(ap, char *));
            break;
        case 'd':
            read = read_dec(channel, va_arg(ap, int *));
            break;
        case 'c':
            read = 1;
            arg = va_arg(ap, char *);
            (*arg) = fgetc(channel);
            fputc(STDOUT, *arg);
            break;
        default:
            break;
    }

    return read;
}

// si hay mas de un espacio se rompe todo
static int read_str(unsigned int channel, char * ptr) {
    char c;
    int read = 0;

    while ((c = fgetc(channel)) != EOF && c != '\n' && c != ' ') {
        if (c > 0) {
            ptr[read++] = c;
        }
    }

    if (read == 0 && c == EOF) {
        return 0;
    }

    ptr[read] = 0;
    return 1;
}

static int read_dec(unsigned int channel, int * ptr) {
    int number = 0;
    int digits = 0;
    char c;

    while (digits < 9 && (c = fgetc(channel)) != '\n' && c != EOF && c != ' ') {
        if (c < '0' || c > '9') {
            return 0;
        }
        number = number * 10 + c - '0';
        digits++;
    }

    *ptr = number;
    return digits>0;
}