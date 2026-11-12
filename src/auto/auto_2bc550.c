#include "common.h"

/* func_002BC550 */
/* asm: pure tail jump (j func_00307B90): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BC550\n.type func_002BC550, @function\nfunc_002BC550:\n\tjmp func_00307B90\n");
