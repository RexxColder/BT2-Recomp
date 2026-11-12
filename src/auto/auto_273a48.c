#include "common.h"

/* func_00273A48 */
/* asm: pure tail jump (j func_00272070): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00273A48\n.type func_00273A48, @function\nfunc_00273A48:\n\tjmp func_00272070\n");
