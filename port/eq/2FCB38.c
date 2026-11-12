#include "common.h"

s32 sceSifCallRpc(void *client, s32 fno, s32 mode, void *send, s32 sendSize, void *recv, s32 recvSize,
                  void *endFn, s32 endParam);
extern u8 D_00355C70[] __attribute__((section(".data")));
extern u8 D_0039DD80[] __attribute__((section(".data")));
extern s32 D_0039DC80 __attribute__((section(".data")));

void func_002FCB38(s32 arg0) {
    D_0039DC80 = arg0;
    sceSifCallRpc(D_00355C70, 3, 0, &D_0039DC80, 4, D_0039DD80, 0, 0, 0);
}
