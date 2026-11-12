#include "common.h"

/* func_0025B9B0 */
/* asm: pure tail jump (j func_0025AAF0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0025B9B0\n.type func_0025B9B0, @function\nfunc_0025B9B0:\n\tjmp func_0025AAF0\n");
