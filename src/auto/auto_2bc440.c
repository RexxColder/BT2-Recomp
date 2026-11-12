#include "common.h"

/* func_002BC440 */
/* asm: pure tail jump (j func_002B7BF0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BC440\n.type func_002BC440, @function\nfunc_002BC440:\n\tjmp func_002B7BF0\n");
