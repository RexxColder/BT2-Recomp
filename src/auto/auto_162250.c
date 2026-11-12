#include "common.h"

/* func_00162250 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00162250\n.type func_00162250, @function\nfunc_00162250:\n\tjmp BtlTask_SetDead\n");
