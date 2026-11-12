#include "common.h"

void Vec4_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec4_Clamp(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
s32 func_001B1380(s32 arg0, s32 arg1);
void func_001B0D88(s32 arg0);

s32 func_001B26B8(u8 *arg0) {
    s32 s4 = (s32)arg0;
    s32 s3 = *(s32 *)(s4 + 0x38);
    s32 s2 = *(s32 *)(s3 + 0x38);
    s32 e = s3 + 0x40;
    s32 count = 15;
    s32 result = 0;

    do {
        s32 flags = *(s32 *)(e + 0x8);
        s32 s0;

        result = flags & 8;
        if ((flags & 1) != 0) {
            if ((flags & 8) != 0) {
                func_001B0D88(e);
                *(s32 *)(e + 0x8) = 0;
                result = *(s32 *)(s3 + 0xA48) - 1;
                *(s32 *)(s3 + 0xA48) = result;
            } else {
                /* 0x2 bit: position advances by the step from s2+0x14, clamps to the target in (e+0x4) */
                if ((flags & 2) == 0) {
                    f32 target = (f32)*(s32 *)(e + 0x4);
                    f32 cur = *(f32 *)(e + 0xC) + *(f32 *)(s2 + 0x14);

                    *(f32 *)(e + 0xC) = cur;
                    if (target <= cur) {
                        *(f32 *)(e + 0xC) = target;
                        flags = flags | 2;
                        *(s32 *)(e + 0x8) = flags;
                    }
                }
                if ((flags & 4) == 0 && *(f32 *)(e + 0x18) <= *(f32 *)(e + 0x10)) {
                    f32 v = *(f32 *)(e + 0xC) - *(f32 *)(s2 + 0x18);

                    *(f32 *)(e + 0xC) = v;
                    if (v <= 0.0f) {
                        *(f32 *)(e + 0xC) = 0.0f;
                        flags = flags | 4;
                        *(s32 *)(e + 0x8) = flags;
                    }
                }
                if ((flags & 0x10) == 0 && *(f32 *)(s2 + 0x6C) <= *(f32 *)(e + 0x10)) {
                    *(s32 *)(e + 0x9C) = 0;
                    flags = flags | 0x10;
                    *(s32 *)(e + 0x8) = flags;
                }
                if ((flags & 0x20) == 0 && *(f32 *)(e + 0x24) <= *(f32 *)(e + 0x10)) {
                    f32 denom = *(f32 *)(e + 0x14) - *(f32 *)(e + 0x10);
                    f32 num = -*(f32 *)(e + 0x8C);

                    flags = flags | 0x20;
                    *(s32 *)(e + 0x8) = flags;
                    *(f32 *)(e + 0x9C) = num / denom;
                }
                if ((flags & 0x40) == 0 && *(f32 *)(e + 0x1C) <= *(f32 *)(e + 0x10)) {
                    flags = flags | 0x40;
                    *(s32 *)(e + 0x8) = flags;
                }
                if ((flags & 0x80) != 0) {
                    *(f32 *)(e + 0x38) = 1.0f;
                    *(f32 *)(e + 0x3C) = 1.0f;
                    s0 = e + 0x80;
                } else {
                    s0 = e + 0x80;
                    if (*(f32 *)(e + 0x20) <= *(f32 *)(e + 0x10)) {
                        *(f32 *)(e + 0x38) = *(f32 *)(s2 + 0x34);
                        flags = flags | 0x80;
                        *(s32 *)(e + 0x8) = flags;
                        *(f32 *)(e + 0x3C) = *(f32 *)(s2 + 0x38);
                    }
                }
                Vec4_Add((u8 *)s0, (u8 *)s0, (u8 *)(e + 0x90));
                Vec4_Clamp((f32 *)s0, (f32 *)s0, 0.0f, 255.0f);
                result = func_001B1380(s4, e);
                {
                    f32 limit = *(f32 *)(e + 0x14);
                    f32 pos = *(f32 *)(e + 0x10) + 1.0f;

                    *(f32 *)(e + 0x10) = pos;
                    if (limit <= pos) {
                        result = *(s32 *)(e + 0x8) | 8;
                        *(s32 *)(e + 0x8) = result;
                    }
                }
            }
        }
        count = count - 1;
        e = e + 0xA0;
    } while (count >= 0);
    return result;
}
