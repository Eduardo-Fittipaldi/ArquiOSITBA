/*
 * types.h
 *
 *  Created on: Apr 17, 2010
 *      Author: anizzomc
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef struct {
	int x;
	int y;
} coord_t;



#pragma pack(push)
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de segmento */
typedef struct {
    word    limit,
            base_l;
    byte    base_m,
            access,
            attribs,
            base_h;
} DESCR_SEG;

/* Descriptor de interrupcion */
/* http://wiki.osdev.org/IDT - IDT in IA-32e Mode (64-bit IDT) */
typedef struct {
	byte	zero_1,
			access;
  	word	offset_l,
            selector,
  			offset_m;
  	dword	offset_h,
			zero_2;
} DESCR_INT;

#pragma pack(pop)

#endif /* TYPES_H_ */
