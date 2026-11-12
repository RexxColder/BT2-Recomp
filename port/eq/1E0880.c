#include "common.h"

void func_001E0A70(s32 arg0, f32 farg0);
void func_001E0EA0(s32 arg0);
void func_001E1E28(s32 arg0, s32 arg1);

s32 func_001E0880(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 a3;
    s32 var;
    s32 src;
    s32 dst;
    s32 end;
    s32 s0;
    s32 s2;
    s64 last;

    a3 = arg3 & 0xFF;
    var = 0;
    if (a3 < *(u8 *)(arg1 + 0x21D8)) {
        src = arg1 + (a3 * 0x21E0);
        dst = arg0;
        end = src + 0x21E0;
        do {
            last = *(s64 *)(src + 0x00);
            *(s64 *)(dst + 0x00) = last;
            *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
            *(s64 *)(dst + 0x10) = *(s64 *)(src + 0x10);
            *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
            src += 0x20;
            dst += 0x20;
        } while (src != end);
        *(u8 *)(arg0 + 0x21E4) = a3;
        s0 = arg0 + 0x10;
        *(f32 *)(arg0 + 0x21E0) = 1.0f;
        s2 = 0;
        *(s32 *)(arg0 + 0x21E8) = arg2;
        *(s8 *)(arg0 + 0x21E5) = 0;
        *(s32 *)(arg0 + 0x21D0) = 0;
        func_001E0A70(arg0, farg0); /* f12 passes through unchanged */
        var = 1;
        if (*(s32 *)(arg0 + 0x1B0) > 0) {
            *(s32 *)(s0 + 0x194) = 0;
            for (;;) {
                *(s32 *)(s0 + 0x198) = 0;
                s2 += 1;
                func_001E0EA0(s0);
                func_001E1E28(s0 + 0x10, s0 + 0x60);
                s0 += 0x1B0;
                if (!(s2 < *(s32 *)(arg0 + 0x1B0))) {
                    break;
                }
                *(s32 *)(s0 + 0x194) = 0;
            }
        }
    }
    return var;
}
