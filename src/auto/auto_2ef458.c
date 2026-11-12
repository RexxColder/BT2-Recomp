#include "common.h"

/* func_002EF458 */
/* asm: pure tail jump (j func_002EEAC0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EF458\n.type func_002EF458, @function\nfunc_002EF458:\n\tjmp func_002EEAC0\n");
