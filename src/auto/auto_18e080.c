#include "common.h"

/* func_0018E080 */
/* asm: pure tail jump (j func_0018E098): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0018E080\n.type func_0018E080, @function\nfunc_0018E080:\n\tjmp func_0018E098\n");
