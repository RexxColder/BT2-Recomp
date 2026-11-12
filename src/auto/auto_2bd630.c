#include "common.h"

/* func_002BD630 */
u32 func_002BD630(u32 a0) { return func_002F1B30(a0, 0); }
/* func_002BD648 */
/* asm: pure tail jump (j func_002F1BC0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BD648\n.type func_002BD648, @function\nfunc_002BD648:\n\tjmp func_002F1BC0\n");
