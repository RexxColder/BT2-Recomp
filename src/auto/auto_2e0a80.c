#include "common.h"

/* func_002E0A80 */
/* asm: pure tail jump (j func_002E0A98): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002E0A80\n.type func_002E0A80, @function\nfunc_002E0A80:\n\tjmp func_002E0A98\n");
