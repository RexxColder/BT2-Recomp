#include "common.h"

/* func_002EFD18 */
/* asm: pure tail jump (j func_003029C8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFD18\n.type func_002EFD18, @function\nfunc_002EFD18:\n\tjmp func_003029C8\n");
