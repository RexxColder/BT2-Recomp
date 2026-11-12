#include "common.h"

/* func_002EFFF0 */
/* asm: pure tail jump (j func_003039A0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFFF0\n.type func_002EFFF0, @function\nfunc_002EFFF0:\n\tjmp func_003039A0\n");
