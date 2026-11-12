#include "common.h"

/* func_00113830 */
/* asm: pure tail jump (j func_0029D5B0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00113830\n.type func_00113830, @function\nfunc_00113830:\n\tjmp func_0029D5B0\n");
