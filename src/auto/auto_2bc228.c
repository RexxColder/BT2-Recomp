#include "common.h"

/* func_002BC228 */
/* asm: pure tail jump (j func_00307B38): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BC228\n.type func_002BC228, @function\nfunc_002BC228:\n\tjmp func_00307B38\n");
