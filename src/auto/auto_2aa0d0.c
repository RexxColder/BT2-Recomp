#include "common.h"

/* func_002AA0D0 */
/* asm: pure tail jump (j func_00259F80): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002AA0D0\n.type func_002AA0D0, @function\nfunc_002AA0D0:\n\tjmp func_00259F80\n");
