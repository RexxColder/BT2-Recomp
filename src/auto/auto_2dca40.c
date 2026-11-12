#include "common.h"

/* func_002DCA40 */
/* asm: pure tail jump (j func_002DCA58): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002DCA40\n.type func_002DCA40, @function\nfunc_002DCA40:\n\tjmp func_002DCA58\n");
