
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

//Jump Instruction
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

            printf("Performing Code Injection\n");
            
            unsigned long addr = (unsigned long) &&once_start;
            addr -= (unsigned long)addr % page_size;
            printf("Starting point %ld\n", addr);
            unsigned int result = mprotect((void*)addr, page_size, PROT_WRITE | PROT_READ | PROT_EXEC);
            printf("MProtect Result %d\n", result);

            void* start_address = &&once_start + 10;
            void*   end_address = &&once_end;
            unsigned int difference = end_address - start_address; 

            jmp j;
            j.mem[0] = 0xE9;
            *((unsigned int*)(&j.mem[1])) = difference;

            printf("Start Address %p\n", start_address);
            printf("End Address %p\n", end_address);
            printf("Difference %x\n", difference);
            printf("Jump Instruction %x %x %x %x %x\n", j.mem[0], j.mem[1], j.mem[2], j.mem[3],j.mem[4]);

            jmp* start_ptr = (jmp*) &&once_start;
            *start_ptr = j;
   
            printf("Done Performing Code Injection\n");

        }
        once_end: asm("nop");
        printf("");

    }

    // printf("Done\n");

   
}
        
