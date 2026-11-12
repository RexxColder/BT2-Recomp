#include "common.h"

/* func_002DA408 */
/* asm: pure tail jump (j func_002DA3A8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002DA408\n.type func_002DA408, @function\nfunc_002DA408:\n\tjmp func_002DA3A8\n");
