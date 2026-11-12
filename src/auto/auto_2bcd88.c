#include "common.h"

/* func_002BCD88 */
/* asm: pure tail jump (j func_002BCCE0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BCD88\n.type func_002BCD88, @function\nfunc_002BCD88:\n\tjmp func_002BCCE0\n");
