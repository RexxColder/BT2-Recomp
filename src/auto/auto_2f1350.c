#include "common.h"

/* func_002F1350 */
void func_002F1350(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0x34) = a1; }
/* func_002F1358 */
u32 func_002F1358(void *a0) { return *(u32 *)((u8 *)a0 + 0x34); }
/* func_002F1360 */
void func_002F1360(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0x9c) = a1; }
/* func_002F1368 */
u32 func_002F1368(void *a0) { return *(u32 *)((u8 *)a0 + 0x9c); }
/* func_002F1370 */
u32 func_002F1370(u32 a0) { return func_002E7C88(*(u32 *)((u8 *)a0 + 0x4)); }
/* func_002F1388 */
/* asm: pure tail jump (j func_002E7CF0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F1388\n.type func_002F1388, @function\nfunc_002F1388:\n\tjmp func_002E7CF0\n");
