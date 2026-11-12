#include "common.h"

/* func_001651F8 */
void func_001651F8(void) {  }
/* func_00165200 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00165200\n.type func_00165200, @function\nfunc_00165200:\n\tjmp BtlTask_SetDead\n");
