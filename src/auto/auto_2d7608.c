#include "common.h"

/* func_002D7608 */
/* asm: pure tail jump (j func_002D7620): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002D7608\n.type func_002D7608, @function\nfunc_002D7608:\n\tjmp func_002D7620\n");
