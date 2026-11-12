#include "common.h"

/* func_002CA340 */
/* asm: pure tail jump (j func_002E0528): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002CA340\n.type func_002CA340, @function\nfunc_002CA340:\n\tjmp func_002E0528\n");
