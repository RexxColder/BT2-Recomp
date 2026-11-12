#include "common.h"

/* func_002C22D8 */
/* asm: pure tail jump (j func_002D43F8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C22D8\n.type func_002C22D8, @function\nfunc_002C22D8:\n\tjmp func_002D43F8\n");
