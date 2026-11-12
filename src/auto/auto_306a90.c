#include "common.h"

/* func_00306A90 */
/* asm: pure tail jump (j func_002FD258): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00306A90\n.type func_00306A90, @function\nfunc_00306A90:\n\tjmp func_002FD258\n");
