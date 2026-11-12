#include "common.h"

/* func_00130E10 */
/* asm: pure tail jump (j func_00131080): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00130E10\n.type func_00130E10, @function\nfunc_00130E10:\n\tjmp func_00131080\n");
