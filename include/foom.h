#ifndef _FOOM_
#define _FOOM_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 4096
#define ARB_LEN 64

#define SYMB_KEYWORD 1<<0
#define SYMB_LIT_NUM 1<<1
#define SYMB_LIT_STR 1<<2
#define SYMB_OPERAOR 1<<3

#define ATTR_EQ 1<<0
#define ATTR_LT 1<<1
#define ATTR_GT 1<<2
#define ATTR_LE 1<<3
#define ATTR_GE 1<<4
#define ATTR_NE 1<<5


#include "foom_typedefs.h"

#endif
