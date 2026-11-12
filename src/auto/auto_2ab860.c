#include "common.h"

/* func_002AB860 */
/* asm: pure tail jump (j func_002699C0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002AB860\n.type func_002AB860, @function\nfunc_002AB860:\n\tjmp func_002699C0\n");
