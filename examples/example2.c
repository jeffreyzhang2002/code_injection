
#include <stdio.h>
#include <sys/mman.h>

#include "../lib.h"


int main(int argc, char** argv) {   

    if(argc == 0) {
        
        End:

        printf("Ran\n");

        return 0;
    }

    long page_size = getpagesize();

    __jmp_inject(Start, End, page_size);

    printf("Performed Injection\n");

    __jmp_inject_target(Start);


    printf("This should never be ran\n");

     

   
}
        
