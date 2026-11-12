#include "common.h"

/* func_0030D5F8 */
/* asm: pure tail jump (j __ieee754_acosf): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0030D5F8\n.type func_0030D5F8, @function\nfunc_0030D5F8:\n\tjmp __ieee754_acosf\n");
