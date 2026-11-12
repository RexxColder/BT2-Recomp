#include "common.h"

/* func_00300E18 */
/* asm: pure tail jump (j func_00326950): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00300E18\n.type func_00300E18, @function\nfunc_00300E18:\n\tjmp func_00326950\n");
