#include "common.h"

/* func_002EFF48 */
/* asm: pure tail jump (j func_00303750): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFF48\n.type func_002EFF48, @function\nfunc_002EFF48:\n\tjmp func_00303750\n");
