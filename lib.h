// copyright 2023
// small library for performing personal code injection optimizations

#ifndef INJECT_CODE_H
#define INJECT_CODE_H

#include <sys/mman.h>
#include <unistd.h>

typedef struct jmp_inst{
    unsigned char op;
    unsigned char dest[4];
} jmp_start;


#define __jmp_inject_target(target_label) target_label: asm("nop \n nop \n nop \n nop \nop") 

#define __inject(target_label, destination_label, page_size) do { \
        unsigned long page_size = getpagesize(); \
        if(mprotect((void*)(((unsigned long) &&target_label) & ~((page_size)-1)), (page_size), PROT_WRITE | PROT_READ | PROT_EXEC)) { \
            *((jmp_inst*) &&target_label) = (jmp_inst){.op = 0xE9, .dest = (unsigned char[4])(&&destination_label - &&target_label - sizeof(jmp_inst) - 5)}; \
        } \
    } while(0) 


#endif