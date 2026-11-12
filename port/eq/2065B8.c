#include "common.h"

s32 func_0020A9C0(s32 arg0);
s32 func_00212320(s32 arg0);
s32 func_00241C50(s32 arg0, s32 arg1);
s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_0020C9F8(s32 arg0, s32 arg1);

/* 0x002065B8(obj): when func_0020A9C0(*(obj+0x1534)) != 0: r = func_00212320(obj), v = func_00241C50(obj, r). When
 * v is 0x16 or 0x17 and func_0025FBE8(*(obj+0x1530), 0x400) != 0, func_0020C9F8(*(obj+0x1534), 1) is called. */
void func_002065B8(u8 *arg0) {
    s32 r;
    s32 v;

    if (func_0020A9C0(*(s32 *)(arg0 + 0x1534)) == 0) {
        return;
    }
    r = func_00212320((s32)arg0);
    v = func_00241C50((s32)arg0, r);
    if (v >= 0x16 && v < 0x18) {
        if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x400) != 0) {
            func_0020C9F8(*(s32 *)(arg0 + 0x1534), 1);
        }
    }
}
