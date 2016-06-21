#include "ctype.h"

int isalnum(int c){
    return (isalpha(c) || isdigit(c));
}
int isalpha(int c){
    return (islower(c) || isupper(c));
}
int isdigit(int c){
    return IS_DIGIT(c);
}
int islower(int c){
    return BETWEEN(c,'a','z');
}
int isprint(int c){
    return (isalnum(c) || isspace(c) || ispunct(c));
}
int isspace(int c){
    return (c == ' ' || c =='\t' || c == '\n');
}
int isupper(int c){
    return BETWEEN(c,'A','Z');
}
int isxdigit(int c){
    return (isdigit(c) || (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'));
}

int tolower(int c){
    if(isupper(c)){
        c += 'a' - 'A';
    }
    return c;
}
int toupper(int c){
    if(islower(c)){
        c -= 'a' - 'A';
    }
    return c;
}

//This function checks whether the passed character has graphical representation using locale.
int isgraph(int c){
    return (isalnum(c) || ispunct(c));
}
//This function checks whether the passed character is a punctuation character.
int ispunct(int c){
    return IS_PUNCT(c);
}
//This function checks whether the passed character is control character.
int iscntrl(int c){
    return (BETWEEN(c,0,31) || c == 127);
}