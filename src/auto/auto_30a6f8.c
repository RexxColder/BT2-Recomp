#include "common.h"

/* func_0030A6F8 */
/* asm: pure tail jump (j func_0030A5F0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0030A6F8\n.type func_0030A6F8, @function\nfunc_0030A6F8:\n\tjmp func_0030A5F0\n");
