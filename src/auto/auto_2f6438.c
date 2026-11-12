#include "common.h"

/* func_002F6438 */
/* asm: pure tail jump (j func_002F0018): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F6438\n.type func_002F6438, @function\nfunc_002F6438:\n\tjmp func_002F0018\n");
