#include "common.h"

void FlushCache(s32 arg0);
s32 sceSifCallRpc(u8 *cd, s32 fno, s32 mode, s32 *send, s32 ssize, u8 *recv, s32 rsize, s32 cb, s32 cbdata);
extern s32 D_003B0E00 __attribute__((section(".data")));
extern u8 *gSndRpc;

s32 func_00297420(s32 arg0, s32 arg1) {
    D_003B0E00 = arg1;
    FlushCache(0);
    sceSifCallRpc(gSndRpc + 0x40, arg0, 0, &D_003B0E00, 0x100, gSndRpc, 0x40, 0, 0);
    return *(s32 *)gSndRpc;
}
