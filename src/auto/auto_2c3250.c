#include "common.h"

/* func_002C3250 */
/* asm: pure tail jump (j func_003046E0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C3250\n.type func_002C3250, @function\nfunc_002C3250:\n\tjmp func_003046E0\n");
