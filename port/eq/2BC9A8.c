#include "common.h"

s32 func_002BD798(s32 arg0);
s32 func_002BD730(s32 arg0);
void func_002BD6B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002B6700(s32 arg0);
s32 Rand_Range(s32 arg0, s32 arg1);
void func_002B3190(s32 arg0);
extern u8 D_00379F10[] __attribute__((section(".data")));

s32 func_002BC9A8(s32 arg0) {
    u8 *obj;
    s32 vt;
    void (*fn)(s32);

    if (func_002BD798(*(s32 *)((u8 *)arg0 + 0x40)) != 2) {
        obj = *(u8 **)((u8 *)arg0 + 0x1BC);
        if (obj != 0) {
            vt = *(s32 *)obj;
            fn = (void (*)(s32))(*(s32 *)((u8 *)vt + 0x14));
            fn((s32)obj);
        }
        func_002BD6B8(*(s32 *)((u8 *)arg0 + 0x40), *(s32 *)((u8 *)arg0 + 0x1A4),
                      *(s32 *)((u8 *)arg0 + 0x1B0), *(s32 *)((u8 *)arg0 + 0x1B4),
                      *(s32 *)((u8 *)arg0 + 0x1B8));
        if (func_002BD730(*(s32 *)((u8 *)arg0 + 0x40)) == -1) {
            *(s32 *)((u8 *)arg0 + 0x04) = 4;
            func_002B6700(-0x66);
            Rand_Range((s32)D_00379F10, *(s32 *)((u8 *)arg0 + 0x1A4));
            *(s32 *)((u8 *)arg0 + 0x1AC) = 0;
            return -1;
        }
        func_002B3190(arg0);
        return 1;
    }
    return -1;
}
