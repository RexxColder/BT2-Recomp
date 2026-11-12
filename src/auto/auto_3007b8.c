#include "common.h"

/* func_003007B8 */
/* asm: pure tail jump (j func_00306F10): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_003007B8\n.type func_003007B8, @function\nfunc_003007B8:\n\tjmp func_00306F10\n");
