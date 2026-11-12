#include "common.h"

void func_001E0C80(s32 arg0, s32 arg1, f32 farg0, f32 farg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void memset(void *arg0, s32 arg1, u32 arg2);

void func_001DF940(s32 arg0, s32 arg1, f32 farg0, f32 farg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *o;
    u8 *src;
    s32 s1;
    s32 s3;
    u8 v;

    o = (u8 *)arg0;
    src = (u8 *)arg1;
    memset((void *)arg0, 0, 0x21E0);
    *(f32 *)(o + 0x21C4) = *(f32 *)(src + 0x1A4);
    v = *(u8 *)(src + 0x1A0);
    *(s32 *)(o + 0x21C8) = 0;
    *(u8 *)(o + 0x21CC) = v;
    *(f32 *)(o + 0x21D0) = 1.0f;
    *(u8 *)(o + 0x21D9) = *(u8 *)(src + 0x19C);
    *(s8 *)(o + 0x21DA) = 1;
    *(s32 *)(o + 0x21C0) = 0;
    if ((v & 0xFF) != 0) {
        s1 = 0;
        s3 = 0;
        do {
            func_001E0C80((s32)(o + s1), (s32)(src + s1), farg0, farg1, arg2, arg3, arg4, arg5);
            s3 += 1;
            s1 += 0x1B0;
        } while (s3 < *(u8 *)(o + 0x21CC));
    }
}
