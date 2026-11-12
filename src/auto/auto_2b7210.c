#include "common.h"

/* func_002B7210 */
/* asm: pure tail jump (j func_002B7228): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B7210\n.type func_002B7210, @function\nfunc_002B7210:\n\tjmp func_002B7228\n");
