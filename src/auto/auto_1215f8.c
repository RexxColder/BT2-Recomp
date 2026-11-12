#include "common.h"

/* func_001215F8 */
/* asm: pure tail jump (j func_00122F28): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001215F8\n.type func_001215F8, @function\nfunc_001215F8:\n\tjmp func_00122F28\n");
