#include "common.h"

s32 func_0032EB50(void);
s32 sceSifRegisterRpc(void *rd, s32 rpc_number, void *func, void *buf, void *cfunc, void *cbuf, void *q);
s32 sceSifRpcLoop(void *q);
s32 sceSifSetRpcQueue(void *q, s32 thread_id);
extern s32 D_003553D4 __attribute__((section(".data")));
extern s32 D_003553D8 __attribute__((section(".data")));
extern u8 D_00355C98[] __attribute__((section(".data")));
extern u8 D_00355CE0[] __attribute__((section(".data")));
extern u8 D_00355D00[] __attribute__((section(".data")));
extern void func_002FC998(void) __attribute__((section(".data")));

s32 func_002FCA48(void) {
    sceSifSetRpcQueue(D_00355CE0, func_0032EB50());
    sceSifRegisterRpc(D_00355C98, D_003553D4, (void *) func_002FC998, D_00355D00, 0, 0, D_00355CE0);
    D_003553D8 = 1;
    sceSifRpcLoop(D_00355CE0);
    return 0;
}
