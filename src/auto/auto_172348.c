#include "common.h"

/* func_00172348 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00172348\n.type func_00172348, @function\nfunc_00172348:\n\tjmp BtlTask_SetDead\n");
