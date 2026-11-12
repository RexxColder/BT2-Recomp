#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(u8 *arg0);
void func_002C32B0(s32 arg0);
void func_002C32C8(s32 arg0);
s32 func_002D13D0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C1440(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 sp[4];
    u8 *p;
    u8 *ea;
    s32 s0;
    s32 s2;
    s32 s6;
    s32 fp;
    s32 cnt;
    s32 t;

    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000162);
    }
    s6 = *(s32 *)(arg0 + 0xE70);
    p = arg0 + 0xD30;
    *arg3 = 0;
    fp = func_002D13D0((s32)arg0, (s32)arg1, (s32)arg2);
    s2 = 0;
    if (*(s32 *)(p + 0x164) != 0 && *arg2 != 1) {
        func_002C32B0((s32)sp);
        s0 = *(s32 *)(p + 0x168);
        cnt = 0;
        for (;;) {
            if (!(cnt < 0x20)) {
                break;
            }
            cnt += 1;
            ea = arg0 + 0xD3C + (s0 - (((s0 < 0 ? s0 + 0x1F : s0) >> 5) << 5)) * 4;
            s2 = func_002E0A98(*(s32 *)(ea + 0x160), *arg2, s6);
            if (!(*arg1 < s2)) {
                break;
            }
            s0 -= 1;
        }
        *arg3 = s0;
        t = *arg1 - s2;
        *arg1 = (t < 0) ? 0 : t;
        func_002C32C8((s32)sp);
    }
    return fp;
}
