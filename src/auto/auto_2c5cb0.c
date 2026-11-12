#include "common.h"

/* func_002C5CB0 */
u32 func_002C5CB0(void) { return 0; }
/* func_002C5CB8 */
u32 func_002C5CB8(void) { func_002E0378(); return 0; }
/* func_002C5CD8 */
/* asm: pure tail jump (j func_002C5CF0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002C5CD8\n.type func_002C5CD8, @function\nfunc_002C5CD8:\n\tjmp func_002C5CF0\n");
