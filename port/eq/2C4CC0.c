#include "common.h"

s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002C06B0(u8 *arg0, s32 arg1);
s32 func_002D3030(u8 *arg0, s32 arg1);
s32 func_002D05E8(u8 *arg0, s32 arg1, s32 arg2);

/* 0x002C4CC0: two symmetric checks (pairs 6/0x50/2/6 and 5/0x4F/1/7); returns the last call's result. */
s32 func_002C4CC0(u8 *obj) {
    u8 *P = *(u8 **)(obj + 0x1F7C);
    s32 r;

    if (func_002D07B0(obj, 6) != 0 && func_002D07B0(obj, 0x50) != 0) {
        if (func_002C06B0(obj, 2) == 0 && *(s32 *)(P + 8) == 0) {
            if (func_002D3030(obj, 6) != 0) {
                func_002D05E8(obj, 6, 0);
            }
        }
    }
    r = func_002D07B0(obj, 5);
    if (r != 0) {
        r = func_002D07B0(obj, 0x4F);
        if (r != 0) {
            r = func_002C06B0(obj, 1);
            if (r == 0) {
                r = *(s32 *)(P + 4);
                if (r == 0) {
                    r = func_002D3030(obj, 7);
                    if (r != 0) {
                        return func_002D05E8(obj, 5, 0);
                    }
                }
            }
        }
    }
    return r;
}
