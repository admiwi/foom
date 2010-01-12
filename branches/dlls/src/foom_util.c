#include "foom.h"

char * resize_string(char * str, int sz) {
  char * buf = malloc(sz);
  memset(str, 0, sz);
  strcpy(buf, str);
  return buf;
}
