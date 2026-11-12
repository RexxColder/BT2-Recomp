#include "common.h"

/* func_0016CA18 */
void func_0016CA18(void) {  }
/* func_0016CA20 */
/* asm: pure tail jump (j EftShot_GetAttrKind): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0016CA20\n.type func_0016CA20, @function\nfunc_0016CA20:\n\tjmp EftShot_GetAttrKind\n");
