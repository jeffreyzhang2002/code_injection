/**
 * Example Code for Performing arbitary code injection
*/

#include <stdio.h>
#include <sys/mman.h>

//Include the code injection header
#include "../lib.h"

int main(int argc, char** argv) {   

    // Get the system wide pagesize usually 4096
    long page_size = getpagesize();

    printf("Starting the for loop\n");

    //Perform an arbitarty long for loop
    for(int i = 0; i < 30; ++i) {
        printf("Iteration %d\n", i);

        //We use this macro the location where our code should be injected into;
        __jmp_inject_target(Start);
  
        // After injection code will not below will no longer run until the End label

        printf("Performing Long Comparison\n");
        // Perform some really long work that is expensive here.


        if(i == 10) {
            // Perform our code injection here. 
            __jmp_inject(Start, End, page_size);
            printf("Done Performing Code Injection\n");
        }

        // Normal Code flow here again
        End:
        printf("Done With Iteration\n");
    }
}
        
