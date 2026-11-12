#include "common.h"

/* func_002A3310 */
/* asm: pure tail jump (j func_002A3170): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002A3310\n.type func_002A3310, @function\nfunc_002A3310:\n\tjmp func_002A3170\n");
