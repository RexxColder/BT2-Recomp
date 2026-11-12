#include "common.h"

/* func_0015B6A0 */
u32 func_0015B6A0(u32 a0) { return func_0014E970(*(u32 *)((u8 *)a0 + 0x38)); }
/* func_0015B6B8 */
void func_0015B6B8(void) {  }
/* func_0015B6C0 */
/* asm: pure tail jump (j EftShot_GetAttrKind): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0015B6C0\n.type func_0015B6C0, @function\nfunc_0015B6C0:\n\tjmp EftShot_GetAttrKind\n");
