#include "common.h"

/* func_00277E50 */
/* asm: pure tail jump (j func_00277B80): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00277E50\n.type func_00277E50, @function\nfunc_00277E50:\n\tjmp func_00277B80\n");
