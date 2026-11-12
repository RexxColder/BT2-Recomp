#include "common.h"

/* func_001D2EA0 */
/* asm: pure tail jump (j func_001D40E0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001D2EA0\n.type func_001D2EA0, @function\nfunc_001D2EA0:\n\tjmp func_001D40E0\n");
