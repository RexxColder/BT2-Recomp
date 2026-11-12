#include "common.h"

/* func_002B6F88 */
/* asm: pure tail jump (j func_002B6FA0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B6F88\n.type func_002B6F88, @function\nfunc_002B6F88:\n\tjmp func_002B6FA0\n");
