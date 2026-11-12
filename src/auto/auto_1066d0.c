#include "common.h"

/* func_001066D0 */
/* asm: pure tail jump (j ObjOutline_Term): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001066D0\n.type func_001066D0, @function\nfunc_001066D0:\n\tjmp ObjOutline_Term\n");
