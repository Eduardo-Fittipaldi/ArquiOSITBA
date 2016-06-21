#ifndef STRING_H
#define STRING_H

//TODO: add missing functions
int strlen(const char * str);
int strcmp(const char * s1, const char * s2);
int strncmp(const char * s1, const char * s2, int n);
int strcpy(const char * source, char * dest);
int strncpy(const char * source, char * dest, int n);
int prefix(const char * str1, const char * str2);

#endif //STRING_H
