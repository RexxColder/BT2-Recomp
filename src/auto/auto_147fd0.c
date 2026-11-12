#include "common.h"

/* func_00147FD0 */
/* asm: pure tail jump (j func_0020CCC0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00147FD0\n.type func_00147FD0, @function\nfunc_00147FD0:\n\tjmp func_0020CCC0\n");
