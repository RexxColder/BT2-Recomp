#include "common.h"

s32 strcmp(s32 arg0, s32 arg1);

void func_00270568(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    f32 f20;
    f32 f21;
    u8 *s2;
    u8 *s0;
    s32 s1;
    u32 s3;
    s32 v0;

    f21 = (f32)arg2;
    f20 = (f32)arg3;
    s2 = (u8 *)(*(s32 *)arg0 + (*(s32 *)arg1) * 0xC0);
    *(f32 *)(s2 + 0x4C) = f21;
    *(f32 *)(s2 + 0x50) = f20;
    *(s32 *)(s2 + 0x48) = *(s32 *)(s2 + 0x48) | 2;

    s1 = *(s32 *)((u8 *)arg1 + 4);
    s3 = 1;
    if (s1 != 0) {
        if ((u32)(*(s32 *)((u8 *)arg0 + 4) - *(s32 *)arg1) > 1U) {
            s0 = s2 + 0xC0;
            while (1) {
                if (strcmp((s32)s0, (s32)s2) == 0) {
                    v0 = *(s32 *)(s0 + 0x48);
                    s1 -= 1;
                    *(f32 *)(s0 + 0x4C) = f21;
                    v0 = v0 | 2;
                    *(f32 *)(s0 + 0x50) = f20;
                    *(s32 *)(s0 + 0x48) = v0;
                    if (s1 == 0) {
                        break;
                    }
                }
                s3 += 1;
                s0 += 0xC0;
                if (!(s3 < (u32)(*(s32 *)((u8 *)arg0 + 4) - *(s32 *)arg1))) {
                    break;
                }
            }
        }
    }
}
