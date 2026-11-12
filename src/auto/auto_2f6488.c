#include "common.h"

/* func_002F6488 */
/* asm: pure tail jump (j func_002F0030): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F6488\n.type func_002F6488, @function\nfunc_002F6488:\n\tjmp func_002F0030\n");
