#include "common.h"

/* func_00190558 */
/* asm: pure tail jump (j func_00190570): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00190558\n.type func_00190558, @function\nfunc_00190558:\n\tjmp func_00190570\n");
