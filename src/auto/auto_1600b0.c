#include "common.h"

/* func_001600B0 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001600B0\n.type func_001600B0, @function\nfunc_001600B0:\n\tjmp BtlTask_SetDead\n");
