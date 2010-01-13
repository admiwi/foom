#include "foom.h"
#include "foom_lib.h"
#include <windows.h>
#include <sys/stat.h>
typedef object * (__cdecl *NATIVE_LIB)(const char*, scope*);

object * init_native_lib(const char * l, const char * n, scope * scp){
  HINSTANCE hinstLib; 
  NATIVE_LIB n_init; 
  struct stat buf;
  int i = stat(l, &buf);
  if(i) {
    fprintf(stderr, "Library (%s) does not exists! (%d)\n", l, i);
    return NULL;
  } 
  
  hinstLib = LoadLibrary(l); 
 
  if(hinstLib) { 
    n_init = (NATIVE_LIB) GetProcAddress(hinstLib, "init_lib"); 
    if(n_init) 
       return (n_init)(n, scp);
    else return NULL;
  } else return NULL;
}

void init_libs(scope * cscope) {
  init_native_lib("dlls\\foom_foom.dll", "foom", cscope);
}
