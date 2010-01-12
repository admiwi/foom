#include "foom.h"
#include "foom_lib.h"
#include <windows.h>
typedef void (__cdecl *NATIVE_LIB)(scope*);
void init_sys_lib(scope*);

int init_native_lib(char * n, scope * scp){
  HINSTANCE hinstLib; 
  NATIVE_LIB n_init; 
  hinstLib = LoadLibrary(n); 
 
  if(hinstLib) { 
    n_init = (NATIVE_LIB) GetProcAddress(hinstLib, "init_lib"); 
    if(n_init) 
       (n_init)(scp);
    else return 0;
  } else return 0;
  return 1;
}

void init_libs(scope * cscope) {
  printf("%d\n", init_native_lib("dlls\\foom_sys.dll", cscope));
}
