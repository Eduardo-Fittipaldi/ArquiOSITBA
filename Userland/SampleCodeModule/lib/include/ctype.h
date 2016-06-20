#ifndef CTYPE_H
#define CTYPE_H

#define BETWEEN(x,y,z) (x >= y && x <= z)
#define IS_SPACE(x) (x == ' ')
#define IS_DIGIT(x) (BETWEEN(x,'0','9'))
#define IS_ALPHA(x) (IS_LETTER(x)|IS_DIGIT(x))
#define IS_PUNCT(x) (BETWEEN(x,33,47)|BETWEEN(x,58,64)|BETWEEN(x,91,96)|BETWEEN(x,123,126))
#define IS_CONTROL(x) (BETWEEN(x,0,31) && x != '\b' && x != '\t' && x != '\n')

int isalnum(int c);
int isalpha(int c);
int isdigit(int c);
int islower(int c);
int isprint(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

int tolower(int c);
int toupper(int c);

//This function checks whether the passed character has graphical representation using locale.
int isgraph(int c);
//This function checks whether the passed character is a punctuation character.
int ispunct(int c);
//This function checks whether the passed character is control character.
int iscntrl(int c);
#endif //CTYPE_H
