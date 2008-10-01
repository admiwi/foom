/*
 ============================================================================
 Name        : foom.c
 Author      : Adam Wilson
 Version     :
 Copyright   : MIT
 Description : Foom, the programming language
 ============================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 4096

int main(int argc, char** argv) {
  struct stat sb;
  FILE *file;
	char cbuf[BUFSZ];
	char lbuf[BUFSZ];
  int line = 0;

  if(argc < 2) {
    printf("Usage: %s <source file>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (stat(argv[1], &sb) == -1) {
    perror("error");
    exit(EXIT_SUCCESS);
  }


	file = fopen(argv[1],"r");
  int i = 0;
  int cnt = 0;
  do {
    cnt = fread(cbuf, 1, BUFSZ, file);
    memcpy(lbuf, cbuf, BUFSZ);
    i = 0;
    do {
      putc(cbuf[i], stdout);
      if(cbuf[i] == '\n') {
        line++;
        printf("%04d ",line);
      }
    } while(i++<cnt);
  } while(cnt == BUFSZ);

  putc('\n', stdout);

	return EXIT_SUCCESS;
}


