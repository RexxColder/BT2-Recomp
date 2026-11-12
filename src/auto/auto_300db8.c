#include "common.h"

/* func_00300DB8 */
/* asm: pure tail jump (j func_00306F10): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00300DB8\n.type func_00300DB8, @function\nfunc_00300DB8:\n\tjmp func_00306F10\n");
