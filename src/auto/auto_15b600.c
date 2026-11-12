#include "common.h"

/* func_0015B600 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0015B600\n.type func_0015B600, @function\nfunc_0015B600:\n\tjmp BtlTask_SetDead\n");
