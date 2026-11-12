#include "common.h"

s32 FlushCache(s32 arg0);
s32 sceSifCallRpc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
extern u8 *gSndRpc;

s32 func_002974F8(s32 arg0, s32 arg1) {
    FlushCache(0);
    sceSifCallRpc((s32)(gSndRpc + 0x40), arg0, 0, arg1, 0x100, (s32)gSndRpc, 0x40, 0, 0);
    return *(s32 *)gSndRpc;
}
