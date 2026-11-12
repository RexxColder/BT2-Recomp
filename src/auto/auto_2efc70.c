#include "common.h"

/* func_002EFC70 */
/* asm: pure tail jump (j func_00302830): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFC70\n.type func_002EFC70, @function\nfunc_002EFC70:\n\tjmp func_00302830\n");
