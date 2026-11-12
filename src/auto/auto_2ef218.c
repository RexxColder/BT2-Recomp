#include "common.h"

/* func_002EF218 */
/* asm: pure tail jump (j func_0030A770): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EF218\n.type func_002EF218, @function\nfunc_002EF218:\n\tjmp func_0030A770\n");
