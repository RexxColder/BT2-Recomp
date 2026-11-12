#include "common.h"

/* func_002B7C08 */
/* asm: pure tail jump (j func_002B7828): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B7C08\n.type func_002B7C08, @function\nfunc_002B7C08:\n\tjmp func_002B7828\n");
