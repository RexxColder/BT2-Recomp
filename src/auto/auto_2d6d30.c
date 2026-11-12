#include "common.h"

/* BtlObjXf_SetMtx */
void BtlObjXf_SetMtx(void *a0, u32 a1, u32 a2, u32 a3) { *(u32 *)((u8 *)a0 + 0x4) = a1; }
/* func_002D6D38 */
u32 func_002D6D38(void *a0) { return *(u32 *)((u8 *)a0 + 0x4); }
/* func_002D6D40 */
void func_002D6D40(u32 a0, u32 a1, u32 a2) { *(u32 *)((u8 *)a0 + 0x8) = a1; *(u32 *)((u8 *)a0 + 0xc) = a2; }
