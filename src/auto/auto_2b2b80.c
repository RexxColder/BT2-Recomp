#include "common.h"

/* func_002B2B80 */
/* asm: pure tail jump (j func_002B2B98): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B2B80\n.type func_002B2B80, @function\nfunc_002B2B80:\n\tjmp func_002B2B98\n");
