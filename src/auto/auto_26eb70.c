#include "common.h"

void func_0026E1F0(void *arg0, u8 *arg1);
void func_0026E238(void *arg0, u8 *arg1);

/* func_0026EB70 */
u32 func_0026EB70(void *a0) { return *(u32 *)((u8 *)a0 + 0x14); }
/* func_0026EB78 */
/* asm: a0 = obj->0x18; j 26E1F0 -- a1 (label) passes through (was dropped: script never jumped, UB result hang) */
u32 func_0026EB78(u32 a0, u32 a1) { func_0026E1F0((void *)(unsigned long)*(u32 *)((u8 *)(unsigned long)a0 + 0x18), (u8 *)(unsigned long)a1); return 0; }
/* func_0026EB90 */
u32 func_0026EB90(u32 a0, u32 a1) { func_0026E238((void *)(unsigned long)*(u32 *)((u8 *)(unsigned long)a0 + 0x18), (u8 *)(unsigned long)a1); return 0; }
/* func_0026EBA8 */
u32 func_0026EBA8(u32 a0) { return func_0026E288(*(u32 *)((u8 *)a0 + 0x18)); }
