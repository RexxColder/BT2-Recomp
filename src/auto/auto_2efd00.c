#include "common.h"

/* func_002EFD00 */
/* asm: pure tail jump (j func_00302940): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFD00\n.type func_002EFD00, @function\nfunc_002EFD00:\n\tjmp func_00302940\n");
