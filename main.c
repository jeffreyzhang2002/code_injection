
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

//Relative Jump Instruction in x86_64. Relative jumps always start with 0xE9 0x__ 0x__ 0x__ 0x__
typedef struct jmp{
    unsigned char mem[5];
} jmp;

int main(int argc, char** argv) {   

    long page_size = getpagesize();

    printf("Starting the for loop\n");

    for(int i = 0; i < 100; ++i) {

        printf("Iteration %d \n", i);

        //Allocating bytes for jump later
        once_start: 
        asm("nop #Here"); 
        asm("nop #Here");
        asm("nop #Here");
        asm("nop #Here");
        asm("nop #Here");
  
        printf("Performing Long Comparison\n");

        if(i == 10) {

            unsigned long page_size = getpagesize();
            unsigned long page = (((unsigned long) &&once_start) & ~(page_size-1));
            if(!mprotect((void*)page, page_size, PROT_WRITE | PROT_READ | PROT_EXEC)) {
                printf("mprotect failed!");
            }

            jmp j;
            j.mem[0] = 0xE9;
            *((unsigned int*)(&j.mem[1])) = (unsigned int) (&&once_end - &&once_start - sizeof(jmp) - 5); //Note sure why we need the 5? but I guess it works
            *((jmp*) &&once_start) = j;
        
   
            printf("Done Performing Code Injection\n");

        }
        once_end: asm("nop");
        printf("");

    }

    // printf("Done\n");

   
}
        
