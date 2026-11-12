#include "common.h"

/* func_002FDE08 */
u32 func_002FDE08(void) { return 0; }
/* func_002FDE10 */
/* asm: pure tail jump (j func_002FDD40): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002FDE10\n.type func_002FDE10, @function\nfunc_002FDE10:\n\tjmp func_002FDD40\n");
