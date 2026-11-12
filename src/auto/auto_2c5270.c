#include "common.h"

/* func_002C5270 */
/* asm: pure tail jump (j func_002DCE00): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C5270\n.type func_002C5270, @function\nfunc_002C5270:\n\tjmp func_002DCE00\n");
