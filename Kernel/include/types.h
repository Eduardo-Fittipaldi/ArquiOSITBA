/*
 * types.h
 *
 *  Created on: Apr 17, 2010
 *      Author: anizzomc
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned int size_t;

typedef unsigned char byte;
typedef short int word;
typedef int dword;
typedef unsigned long qword;

typedef struct {
	int x;
	int y;
} coord_t;



#pragma pack(push)
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de segmento */
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;


/* Descriptor de interrupcion */
/* http://wiki.osdev.org/IDT - IDT in IA-32e Mode (64-bit IDT) */
typedef struct {
  word      offset_l,
            selector;
  byte      zero_1,
            access;
  word	    offset_m;
  dword	    offset_h;
  dword	    zero_2;
} DESCR_INT;

/* IDTR  */
typedef struct {
  word  limit;
  dword base;
} IDTR;

#pragma pack(pop)

#endif /* TYPES_H_ */
