#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037A530[] __attribute__((section(".data")));

s32 func_002D21A0(u8 *arg0, s32 *arg1) {
    s32 v;
    s32 v1;

    *arg1 = -1;
    v = func_002C3210((s32)arg0);
    if (v != 0) {
        return func_002C2FF0(0, (s32)0xFF000118);
    }
    v1 = *(s32 *)(arg0 + 0x920);
    if (v1 != 0) {
        *arg1 = func_002E0A98(*(s32 *)(D_0037A530 + v1 * 4), *(s32 *)(arg0 + 0xD30 + 0x2AC), 0x3E8);
        v = 0;
    }
    return v;
}
