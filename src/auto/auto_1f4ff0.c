#include "common.h"

/* func_001F4FF0 */
void func_001F4FF0(void) {  }
/* func_001F4FF8 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001F4FF8\n.type func_001F4FF8, @function\nfunc_001F4FF8:\n\tjmp BtlTask_SetDead\n");
