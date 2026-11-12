#include "common.h"

/* func_0030B0A0 */
/* asm: pure tail jump (j func_002FC5D0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0030B0A0\n.type func_0030B0A0, @function\nfunc_0030B0A0:\n\tjmp func_002FC5D0\n");
