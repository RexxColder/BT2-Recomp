#include "common.h"

void sceGsResetGraph(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void sceGsSetDefClear(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                      s32 arg8, s32 arg9, s32 arg10);
void sceGsSetDefDBuff(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void FlushCache(s32 arg0);
void sceGsSwapDBuff(s32 arg0, s32 arg1);
void sceGsSyncVCallback(s32 arg0);
extern u8 func_001006D8[] __attribute__((section(".data")));

void func_0024B800(void) {
    u8 sp20[0x230];
    u8 sp250[0x60];

    sceGsResetGraph(0, 1, 2, 0);
    sceGsSetDefClear((s32)sp250, 0, 0, 0, 0x200, 0x1C0, 0, 0, 0, 0, 0);
    sceGsSetDefDBuff((s32)sp20, 0, 0x200, 0x1C0, 2, 0x30, 1);
    FlushCache(0);
    sceGsSwapDBuff((s32)sp20, 0);
    sceGsSyncVCallback((s32)func_001006D8);
}
