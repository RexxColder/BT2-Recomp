#include "common.h"

/* func_002B9408 */
u32 func_002B9408(void *a0) { return *(u32 *)((u8 *)a0 + 0xa8); }
/* func_002B9410 */
void func_002B9410(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0xa8) = a1; }
/* func_002B9418 */
/* asm: pure tail jump (j func_002B9430): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002B9418\n.type func_002B9418, @function\nfunc_002B9418:\n\tjmp func_002B9430\n");
