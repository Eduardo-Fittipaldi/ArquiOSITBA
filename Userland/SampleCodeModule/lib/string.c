#include "string.h"

int strlen(const char * str) {
    int i = 0;
    while (*str++) { i++; }
    return i;
}

int strcmp(const char * s1, const char * s2) {

    if(*s1 == 0) {
        return *s2 != 0 ? -1 : 0;
    }
    if(*s2 == 0) {
        return 1;
    }

    while(*s1 || *s2){
        if(*s1 > *s2){
            return 1;
        }else if(*s1 < *s2){
            return -1;
        }else{
            s1++;
            s2++;
        }
    }
    return 0;
}

int strncmp(const char * s1, const char * s2, int n) {
    if (n == 0) {
        return 0;
    }
    if(*s1 == 0) {
        return *s2 != 0 ? -1 : 0;
    }
    if(*s2 == 0) {
        return 1;
    }

    while((*s1 || *s2) && n){
        if(*s1 > *s2){
            return 1;
        }else if(*s1 < *s2){
            return -1;
        }else{
            s1++;
            s2++;
            n--;
        }
    }
    return 0;
}

int strcpy(const char * source, char * dest) {
    while(*source) {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = 0;
    return 0;
}

int strncpy(const char * source, char * dest, int n) {
    while(*source && n--) {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = 0;
    return 0;
}

int prefix(const char * str1, const char * str2) {
    int i = 0;

    while (str1[i]) {
        if(str1[i] == str2[i]){
            i++;
        }else{
            return 0;
        }
    }
    return i;
}

