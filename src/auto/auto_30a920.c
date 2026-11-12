#include "common.h"

/* func_0030A920 */
/* asm: pure tail jump (j func_00307998): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0030A920\n.type func_0030A920, @function\nfunc_0030A920:\n\tjmp func_00307998\n");
