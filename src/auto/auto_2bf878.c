#include "common.h"

/* func_002BF878 */
u32 func_002BF878(void) { return 0; }
/* func_002BF880 */
/* asm: pure tail jump (j func_002C0FE8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002BF880\n.type func_002BF880, @function\nfunc_002BF880:\n\tjmp func_002C0FE8\n");
