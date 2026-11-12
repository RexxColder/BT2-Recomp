#include "common.h"

extern u32 D_00353F78[];

/* func_002F1768 */
u32 func_002F1768(u32 a0) { return a0 + 0x58; }
/* func_002F1770 */
u32 func_002F1770(u32 a0) { return func_002E7C08(*(u32 *)((u8 *)a0 + 0x4)); }
/* func_002F1788 */
u32 func_002F1788(u32 a0) { return func_002E7C48(*(u32 *)((u8 *)a0 + 0x4)); }
/* func_002F17A0 */
void func_002F17A0(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0xa8) = a1; }
/* func_002F17A8 */
u32 func_002F17A8(void *a0) { return *(u32 *)((u8 *)a0 + 0xa8); }
/* func_002F17B0 */
void func_002F17B0(u32 a0, u32 a1, u32 a2, u32 a3) { D_00353F78[0] = a0; }
