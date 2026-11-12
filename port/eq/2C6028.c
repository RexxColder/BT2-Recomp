#include "common.h"

s32 func_002C71D8(s32 arg0);
s32 func_002C06B0();
s32 func_002C0670();
s32 func_002D3078(s32 arg0, s32 arg1, s32 arg2);
void func_002DE188(s32 arg0, s32 arg1);

s32 func_002C6028(s32 arg0) {
    s32 out[4];
    s32 s1;
    s32 s3;
    s32 r;
    s32 t0;
    s32 r2;

    s3 = *(s32 *)(arg0 + 0x1FC0);
    s1 = *(s32 *)(s3 + 0);
    if (func_002C71D8(arg0) == 1) {
        return 1;
    }
    if (*(s32 *)(arg0 + 0x78) != 0) {
        if (*(s32 *)(arg0 + 0x7C) == 0) {
            return 1;
        }
    }

    func_002DE188(s1, (s32)out);
    if (out[0] == 0x3FFFF) {
        return 1;
    }
    r = func_002C06B0(arg0, 1, out[0]);
    if (!(r < *(s32 *)(s3 + 0x114))) {
        return 1;
    }
    s1 = func_002D3078(arg0, 1, 1) == 0;
    t0 = func_002C06B0(arg0, s1);
    r2 = func_002C0670(arg0, s1);
    return !(t0 < r2);
}
