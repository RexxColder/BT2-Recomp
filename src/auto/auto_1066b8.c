#include "common.h"

/* func_001066B8 */
/* asm: pure tail jump (j func_001076B0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001066B8\n.type func_001066B8, @function\nfunc_001066B8:\n\tjmp func_001076B0\n");
