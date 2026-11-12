#include "common.h"

/* func_002EF4D8 */
/* asm: pure tail jump (j BtlFacade_BeginWait): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EF4D8\n.type func_002EF4D8, @function\nfunc_002EF4D8:\n\tjmp BtlFacade_BeginWait\n");
