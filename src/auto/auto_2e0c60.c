#include "common.h"

/* func_002E0C60 */
u32 func_002E0C60(u32 a0) { return func_002BF3F8(*(u32 *)((u8 *)a0 + 0x3c)); }
/* func_002E0C78 */
u32 func_002E0C78(u32 a0) { return func_002BF478(*(u32 *)((u8 *)a0 + 0x3c)); }
/* func_002E0C90 */
u32 func_002E0C90(u32 a0) { return func_002BF2F0(*(u32 *)((u8 *)a0 + 0x3c)); }
/* func_002E0CA8 */
u32 func_002E0CA8(u32 a0) { return func_002BF380(*(u32 *)((u8 *)a0 + 0x3c)); }
/* func_002E0CC0 */
/* asm: pure tail jump (j func_002E0CD8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002E0CC0\n.type func_002E0CC0, @function\nfunc_002E0CC0:\n\tjmp func_002E0CD8\n");
