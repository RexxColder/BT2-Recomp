#include "common.h"

/* func_002BC630 */
/* asm: pure tail jump (j func_003070D0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BC630\n.type func_002BC630, @function\nfunc_002BC630:\n\tjmp func_003070D0\n");
