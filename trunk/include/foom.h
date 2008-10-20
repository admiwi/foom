#ifndef _FOOM_
#define _FOOM_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 4096
#define ARB_LEN 64

#define TOK_UNK (0)
#define TOK_KW  (1<<0)
#define TOK_NUM (1<<1)
#define TOK_STR (1<<2)
#define TOK_OP  (1<<3)
#define TOK_SYM (1<<4)

#define ATTR_NONE 0
#define ATTR_EQ 1
#define ATTR_LT 2
#define ATTR_GT 3
#define ATTR_LE 4
#define ATTR_GE 5
#define ATTR_NE 6

#define ATTR_ASSIGN (1<<6)
#define ATTR_INT (1<<7)
#define ATTR_FLOAT (1<<8)

#define ERR_WARN  0
#define ERR_ERROR 1

void add_error(int, char*, int, char*, char*);
void print_errors();

#include "foom_typedefs.h"
#include "foom_util.h"

#endif

