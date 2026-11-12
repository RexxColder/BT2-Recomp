#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);

s32 func_001FD460(s32 arg0, s32 arg1) {
    u8 v6[16];
    u8 v7[16];
    u8 v8[16];
    f32 height;
    f32 dist;
    s32 r;

    r = func_00211310(arg0, 3, 0x10000);
    if (r == 0) {
        return r;
    }
    func_00208DE8(*(s32 *)((u8 *)arg0 + 0x1534), v6, 3);
    func_00208DE8(*(s32 *)((u8 *)arg1 + 0x1534), v7, 3);
    height = BtlCharApi_GetHeight(*(s32 *)((u8 *)arg0 + 0x1534)) * 5.0f;
    if (height < 20.0f) {
        height = 20.0f;
    }
    if (150.0f < height) {
        height = 150.0f;
    }
    func_00312650(v8, v6, v7);
    dist = func_0029DFD0(v8);
    if (dist < height) {
        func_002113C0(arg0, 4, 0x40, 1);
    }
    return 0;
}
