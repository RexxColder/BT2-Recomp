#include "common.h"

/* func_00182368 */
/* asm: pure tail jump (j func_0014F0A8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00182368\n.type func_00182368, @function\nfunc_00182368:\n\tjmp func_0014F0A8\n");
