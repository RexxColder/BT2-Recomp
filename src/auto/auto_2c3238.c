#include "common.h"

/* func_002C3238 */
/* asm: pure tail jump (j func_00304660): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C3238\n.type func_002C3238, @function\nfunc_002C3238:\n\tjmp func_00304660\n");
