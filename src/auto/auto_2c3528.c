#include "common.h"

/* func_002C3528 */
u32 func_002C3528(void) { return 0; }
/* func_002C3530 */
u32 func_002C3530(void) { func_002DC9C8(); return 0; }
/* func_002C3550 */
/* asm: pure tail jump (j func_002C3568): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C3550\n.type func_002C3550, @function\nfunc_002C3550:\n\tjmp func_002C3568\n");
