#include "common.h"

f32 func_002693A0(f32 farg0, u8 *arg1, u8 **arg2);
extern f32 D_0038407C;
extern f32 D_00384080;

s32 func_0011E3B8(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 **temp_a1;
    u8 *temp_a0;
    u8 *v;
    f32 f;
    s32 cnt;
    s32 r;

    r = 0;
    temp_a1 = *(u8 ***)arg0;
    temp_a0 = *temp_a1;
    if ((u32)*(u32 *)(temp_a0 + 0x10) < 0x80U) {
        f = func_002693A0(((*(f32 *)(arg1 + 0x3C) - (*(f32 *)(arg1 + 0x30) * *(f32 *)(arg0 + 0x10)))
                           - (*(f32 *)(arg1 + 0x38) * *(f32 *)(arg0 + 0x18)))
                              / *(f32 *)(arg1 + 0x34)
                          - (*(f32 *)(arg0 + 0x20) - 5.0f),
                          temp_a0, temp_a1);
        r = 0;
        *(f32 *)(arg1 + 0xC) = f;
        if (!(f <= D_0038407C) && (!(arg2 & 0x01000000) || !(D_00384080 <= *(f32 *)(arg1 + 0x34)))) {
            r = 1;
            temp_a0 = *(*(u8 ***)arg0);
            cnt = *(s32 *)(temp_a0 + 0x10);
            v = temp_a0 + (cnt << 6) + 0xC0;
            *(s64 *)(v + 0x00) = *(s64 *)(arg1 + 0x00);
            *(s64 *)(v + 0x08) = *(s64 *)(arg1 + 0x08);
            *(s64 *)(v + 0x10) = *(s64 *)(arg1 + 0x10);
            *(s64 *)(v + 0x18) = *(s64 *)(arg1 + 0x18);
            *(s64 *)(v + 0x20) = *(s64 *)(arg1 + 0x20);
            *(s64 *)(v + 0x28) = *(s64 *)(arg1 + 0x28);
            *(s64 *)(v + 0x30) = *(s64 *)(arg1 + 0x30);
            *(s64 *)(v + 0x38) = *(s64 *)(arg1 + 0x38);
            *(s32 *)(temp_a0 + 0x10) = cnt + 1;
        }
    }
    return r;
}
