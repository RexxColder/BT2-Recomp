#include "common.h"

/* func_00181960 */
u32 func_00181960(u32 a0) { return func_001803E0(*(u32 *)((u8 *)a0 + 0x38)); }
/* func_00181978 */
/* asm: pure tail jump (j BtlTask_SetDead): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00181978\n.type func_00181978, @function\nfunc_00181978:\n\tjmp BtlTask_SetDead\n");
