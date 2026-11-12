#include "common.h"

/* func_002EFCD0 */
u32 func_002EFCD0(u32 a0) { return func_00302770(*(u32 *)((u8 *)a0 + 0xc)); }
/* func_002EFCE8 */
/* asm: pure tail jump (j func_003028B0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFCE8\n.type func_002EFCE8, @function\nfunc_002EFCE8:\n\tjmp func_003028B0\n");
