#include "common.h"

/* func_002EFFD8 */
/* asm: pure tail jump (j func_003038E0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFFD8\n.type func_002EFFD8, @function\nfunc_002EFFD8:\n\tjmp func_003038E0\n");
