#include "common.h"

/* func_002AB170 */
/* asm: pure tail jump (j func_002AAC58): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002AB170\n.type func_002AB170, @function\nfunc_002AB170:\n\tjmp func_002AAC58\n");
