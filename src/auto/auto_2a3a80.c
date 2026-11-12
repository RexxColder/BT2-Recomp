#include "common.h"

/* func_002A3A80 */
/* asm: pure tail jump (j func_002A3430): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002A3A80\n.type func_002A3A80, @function\nfunc_002A3A80:\n\tjmp func_002A3430\n");
