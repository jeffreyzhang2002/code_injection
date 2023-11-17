// copyright 2023
// small library for performing personal code injection optimizations

#ifndef INJECT_CODE_H
#define INJECT_CODE_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

/*
This struct represents the memory footprint of a relative jmp instruction inside x86_64
*/
typedef struct __attribute__((__packed__)) __rjmp_inst{
    uint8_t op;
    int32_t dest;
} __rjmp_inst;

/*
This define is used to allocate space for assembly function. We allocate nops inside the code;
5 NOPs cause 5 bytes for relative_jmp.

target_l: Label name for where we want the injection to occurr

*/
#define __jmp_inject_target(target_l) target_l: __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop") 

/*
This instruction performs the actual jump injection. 

target_l: label name for where we want to inject code
dest_l: label name for the destination of the jump
page_size: Size of the page

*/
#define __jmp_inject(target_l, dest_l, page_size) if(!mprotect((void*)(((unsigned long) &&target_l) & ~((page_size)-1)), (page_size), PROT_WRITE|PROT_READ|PROT_EXEC)){ *((__rjmp_inst*) &&target_l) = (__rjmp_inst){.op=0xE9, .dest=(int32_t)(&&dest_l-&&target_l-sizeof(__rjmp_inst))}; } 
   
#endif

