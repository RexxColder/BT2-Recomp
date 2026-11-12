#include "common.h"

/* func_002EFB38 */
/* asm: pure tail jump (j func_003019D8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFB38\n.type func_002EFB38, @function\nfunc_002EFB38:\n\tjmp func_003019D8\n");
