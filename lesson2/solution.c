#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int(*lib_func)(int);

int main(int argc, char ** argv)
{

    if(argc < 4) exit(1);

    void * hdl = dlopen(argv[1], RTLD_LAZY);
    if(!hdl)  exit(1);
    
    lib_func func = (lib_func)dlsym(hdl, argv[2]);
    if(!func) exit(1);

    printf("%d\n", func(atoi(argv[3])));
}
