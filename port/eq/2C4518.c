#include "common.h"

void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

typedef s32 (*VFunc4)(s32, s32, s32, s32);
typedef void (*VFunc3)(s32, s32, s32);

s32 func_002C4518(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    u8 *vt;

    vt = *(u8 **)arg0;
    /* a0 (the object) and a2 are never written before the first virtual call: passed through */
    ((VFunc4)(*(s32 *)(vt + 0x18)))((s32)arg0, 0, arg2, (s32)sp);
    func_002DA3A8(sp[0], arg1, sp[1], (s32)sp);
    ((VFunc3)(*(s32 *)(vt + 0x20)))((s32)arg0, 1, (s32)sp);
    return sp[1];
}
