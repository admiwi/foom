/*
 ============================================================================
 Name        : foom.c
 Author      : Adam Wilson
 Version     :
 Copyright   : MIT
 Description : Foom, the programming language
 ============================================================================
 */

#include "foom.h"
#include "foom_lex.h"

int main(int argc, char** argv) {
  struct stat sb;
  if(argc < 2) {
    printf("Usage: %s <source file>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (stat(argv[1], &sb) == -1) {
    perror("error");
    exit(EXIT_SUCCESS);
  }
  
  process_file(argv[1]);
  putc('\n', stdout);
	return EXIT_SUCCESS;
}


