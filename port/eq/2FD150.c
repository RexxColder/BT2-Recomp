#include "common.h"

s32 BtlFacade_BeginWait(void);
void func_00306F10(void);
s32 sceSifCallRpc(u8 *cd, s32 fno, s32 mode, s32 *send, s32 ssize, u8 *recv, s32 rsize, s32 cb, s32 cbdata);
extern u8 D_00355C70 __attribute__((section(".data")));
extern s32 D_0039DC80[] __attribute__((section(".data")));
extern s32 D_0039DD80[] __attribute__((section(".data")));

/* 0x002FD150: BtlFacade_BeginWait(); copies arg2 words from arg1 to D_0039DC80; sceSifCallRpc(&D_00355C70, arg0+0x400,
 * 0, D_0039DC80, arg2*4, D_0039DD80, arg4*4, 0, 0); copies arg4 words from D_0039DD80 to arg3; func_00306F10(); returns
 * the first word of D_0039DD80. */
s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    s32 i;

    BtlFacade_BeginWait();
    for (i = 0; i < arg2; i++) {
        D_0039DC80[i] = arg1[i];
    }
    sceSifCallRpc(&D_00355C70, (s32)(arg0 + 0x400), 0, D_0039DC80, arg2 * 4, (u8 *)D_0039DD80, arg4 * 4, 0, 0);
    for (i = 0; i < arg4; i++) {
        arg3[i] = D_0039DD80[i];
    }
    func_00306F10();
    return D_0039DD80[0];
}
