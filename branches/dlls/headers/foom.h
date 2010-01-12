#ifndef _FOOM_
#define _FOOM_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 4096
#define ARB_LEN 64
#define ARB_SLEN 16

#define ERR_WARN  0
#define ERR_ERROR 1

void add_error(int, char*, int, char*, char*);
void print_errors();
#include "foom_symbols.h"
#include "foom_typedefs.h"
#include "foom_util.h"


#endif

