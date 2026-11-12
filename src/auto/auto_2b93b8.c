#include "common.h"

/* func_002B93B8 */
/* asm: pure tail jump (j func_002D69B8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B93B8\n.type func_002B93B8, @function\nfunc_002B93B8:\n\tjmp func_002D69B8\n");
