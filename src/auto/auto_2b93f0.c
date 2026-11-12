#include "common.h"

/* func_002B93F0 */
/* asm: pure tail jump (j func_002D6C40): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B93F0\n.type func_002B93F0, @function\nfunc_002B93F0:\n\tjmp func_002D6C40\n");
