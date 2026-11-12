#include "common.h"

/* func_00260248 */
/* asm: pure tail jump (j func_003126C8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00260248\n.type func_00260248, @function\nfunc_00260248:\n\tjmp func_003126C8\n");
