#include "common.h"

void func_002F9300(s32 arg0);
s32 func_002F95C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_0037DB38[] __attribute__((section(".data")));
extern u8 D_0037DB60[] __attribute__((section(".data")));
extern u8 D_0037DB88[] __attribute__((section(".data")));
extern u8 D_0037DBB0[] __attribute__((section(".data")));

s32 func_002FADB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[5];
    s32 s0;
    s32 (*fn)(s32, s32, s32, s32);

    if (arg0 == 0) {
        func_002F9300((s32)D_0037DB38);
        return -1;
    }
    if (arg1 == 0) {
        func_002F9300((s32)D_0037DB60);
        return -1;
    }
    if (arg2 == 0) {
        func_002F9300((s32)D_0037DB88);
        return -1;
    }
    s0 = func_002F95C8(arg0, arg1, arg2, arg3);
    if (s0 == 0) {
        func_002F9300((s32)D_0037DBB0);
        return -1;
    }
    memset((void *)sp, 0, 0x14);
    sp[0] = arg2;
    sp[1] = arg1;
    sp[2] = arg3;
    fn = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(s0 + 0x60));
    if (fn == NULL) {
        return -1;
    }
    return fn((s32)sp, 2, 0, 0);
}
