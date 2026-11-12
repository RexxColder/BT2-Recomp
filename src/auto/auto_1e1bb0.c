#include "common.h"

/* func_001E1BB0 */
/* asm: pure tail jump (j func_001E1A70): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001E1BB0\n.type func_001E1BB0, @function\nfunc_001E1BB0:\n\tjmp func_001E1A70\n");
