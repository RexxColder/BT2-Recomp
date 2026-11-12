#include "common.h"

/* func_002F5E28 */
/* asm: pure tail jump (j func_002F5D10): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F5E28\n.type func_002F5E28, @function\nfunc_002F5E28:\n\tjmp func_002F5D10\n");
