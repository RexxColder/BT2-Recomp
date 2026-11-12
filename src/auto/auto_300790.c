#include "common.h"

/* func_00300790 */
void func_00300790(void) {  }
/* func_00300798 */
void func_00300798(void) {  }
/* func_003007A0 */
/* asm: pure tail jump (j BtlFacade_BeginWait): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_003007A0\n.type func_003007A0, @function\nfunc_003007A0:\n\tjmp BtlFacade_BeginWait\n");
