#include "common.h"

/* func_002F0030 */
/* asm: pure tail jump (j func_00303170): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F0030\n.type func_002F0030, @function\nfunc_002F0030:\n\tjmp func_00303170\n");
