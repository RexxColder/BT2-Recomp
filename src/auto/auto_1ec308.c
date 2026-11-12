#include "common.h"

/* func_001EC308 */
void func_001EC308(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0x48) = a1; }
/* func_001EC310 */
/* asm: pure tail jump (j sceVu0CopyMatrix): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001EC310\n.type func_001EC310, @function\nfunc_001EC310:\n\tjmp sceVu0CopyMatrix\n");
