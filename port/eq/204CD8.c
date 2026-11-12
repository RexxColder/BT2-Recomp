#include "common.h"

s32 func_0020A758(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212320(s32 arg0);
s32 func_00212560(s32 arg0);
s32 func_002419C8(s32 arg0, s32 arg1);
s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_002822C8(s32 arg0, s32 arg1, f32 farg0);
extern f32 D_00385920;
extern f32 D_00385924;

void func_00204CD8(s32 arg0) {
    u8 *p = (u8 *)arg0;
    s32 temp_s0;
    s64 var_s2;
    s64 var_s3;
    s64 temp_v0;

    var_s3 = *(s64 *)(p + 0x338);
    var_s2 = *(s64 *)(p + 0x400);
    if (func_0020A758(*(s32 *)(p + 0x1534)) != 0) {
        if (func_0025FBE8(*(s32 *)(p + 0x1530), 0x200) != 0) {
            func_002113C0(arg0, 7, 0x80, 1);
        }
        if (func_00211310(arg0, 2, 2) != 0) {
            temp_s0 = func_002419C8(arg0, func_00212320(arg0));
            if (func_00212560(arg0) == temp_s0) {
                func_002113C0(arg0, 7, 0x80, 0);
            }
        }
    } else {
        func_002113C0(arg0, 7, 0x80, 0);
    }
    if (func_00211310(arg0, 7, 0x80) != 0) {
        var_s3 |= 0x8000;
    }
    if (func_00211328(arg0, 7, 0x80) != 0) {
        var_s2 |= 0x8000;
    }
    temp_v0 = var_s2 & 0x8000;
    if (var_s3 & 0x8000) {
        if (temp_v0 == 0) {
            func_002822C8(0, 0, D_00385920);
        }
    } else if (temp_v0 != 0) {
        func_002822C8(0, 1, D_00385924);
    }
}
