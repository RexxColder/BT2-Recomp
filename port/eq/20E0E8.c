#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void ColSeg_Set(void *arg0, void *arg1, void *arg2);
s32 func_0011E1C8(void *arg0);

s32 func_0020E0E8(void) {
    u8 v3[32];
    u8 v4[16];
    u8 v5[16];
    s32 a;
    s32 b;
    s32 r;

    a = func_00211288(0);
    b = func_00211288(1);
    func_002113C0(a, 0, 0x400, 0);
    func_002113C0(b, 0, 0x400, 0);
    func_00208DE8(*(s32 *)((u8 *)a + 0x1534), v4, 0x2F);
    func_00208DE8(*(s32 *)((u8 *)b + 0x1534), v5, 0x2F);
    ColSeg_Set(v3, v4, v5);
    r = func_0011E1C8(v3);
    if (r == 0) {
        return r;
    }
    func_002113C0(a, 0, 0x400, 1);
    return func_002113C0(b, 0, 0x400, 1);
}
