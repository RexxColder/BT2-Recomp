#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CDA00(s32 arg0) {
    u8 *s0;
    s32 obj;
    s32 (*fn)(s32, s32);
    s32 r;
    s32 a2v;

    s0 = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x1FC8) * 0x74 + 0x1320;
    obj = *(s32 *)(s0 + 4);
    fn = (s32 (*)(s32, s32))(*(s32 *)(*(s32 *)obj + 0x24));
    r = fn(obj, 1);
    a2v = *(s32 *)(s0 + 0xC);
    if (r >= (a2v * 0x50) / 100) {
        return 1;
    }
    if (r < func_002D07B0(arg0, 0x46, a2v)) {
        return 0;
    }
    return 1;
}
