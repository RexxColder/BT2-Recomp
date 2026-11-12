#include "common.h"

/* func_002B9D40 */
u32 func_002B9D40(u32 a0, u32 a1, u32 a2) { return func_002B9D70(a0, a1, a2, 0); }
/* func_002B9D58 */
/* asm: pure tail jump (j func_002B9CC0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B9D58\n.type func_002B9D58, @function\nfunc_002B9D58:\n\tjmp func_002B9CC0\n");
