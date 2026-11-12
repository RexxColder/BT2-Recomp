#include "common.h"

void FlushCache(s32 arg0);
void sceGsPutDrawEnv(void *arg0);
void sceGsResetGraph(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void sceGsSetDefClear(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                      s32 arg8, s32 arg9, s32 arg10);
void sceGsSetDefDBuff(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void sceGsSwapDBuff(void *arg0, s32 arg1);
void sceGsSyncPath(s32 arg0, s32 arg1);
void sceGsSyncVCallback(void *arg0);
void func_001006D8(void);

void func_0024B898(void) {
    u8 sp[0x2C0];

    sceGsSetDefDBuff(sp + 0x20, 0, 0x200, 0x1C0, 2, 0x31, 1);
    FlushCache(0);
    sceGsPutDrawEnv(sp + 0x70);
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(sp + 0x160);
    sceGsSyncPath(0, 0);
    sceGsResetGraph(0, 1, 2, 1);
    sceGsSetDefClear(sp + 0x250, 0, 0, 0, 0x200, 0x1C0, 0, 0, 0, 0, 0);
    sceGsSetDefDBuff(sp + 0x20, 0, 0x200, 0x1C0, 2, 0x30, 1);
    FlushCache(0);
    sceGsSwapDBuff(sp + 0x20, 0);
    sceGsSyncVCallback((void *)func_001006D8);
}
