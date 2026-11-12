#include "common.h"

#define FR_F32(off) (*(f32 *)(fr + (off)))
#define FR_S32(off) (*(s32 *)(fr + (off)))

void *memset(void *, s32, u32);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28();

void func_001C8F00(u8 *arg0) {
    u8 fr[0xb0];   /* tamano de locales del original (antes 0xa0) */
    u8 *s3;
    u8 *s7;
    u8 *s5;
    u8 *s1;
    u8 *var_s0;
    s32 s4;
    s32 s6;
    s32 fp;
    s32 s0v;
    s32 s2;
    s32 temp_v0;
    s32 k;

    s4 = 0;
    s6 = 0;
    fp = 0;
    s3 = *(u8 **)(arg0 + 0x38);
    s7 = *(u8 **)s3;
    s5 = s3;
    do {
        FR_F32(0x50) = *(f32 *)(s7 + s6);
        s0v = s4 + 0x10;
        FR_F32(0x54) = *(f32 *)(s7 + 0xC + s6);
        memset(fr + 0x60, 0, 0x10);
        memset(fr + 0x70, 0, 0x10);
        FR_S32(0x80) = *(u8 *)(s7 + 8 + s0v);
        FR_S32(0x84) = *(s32 *)(s3 + 4);
        FR_S32(0x88) = *(s32 *)(s3 + 8) + (s4 * 0x164);
        FR_S32(0x8C) = *(s32 *)(s3 + 0xC) + fp;
        FR_S32(0x90) = *(s32 *)(s3 + 0x90);

        /* copy the parameter block: dst 0x00..0x4F <- src 0x50..0x9F */
        for (k = 0; k < 0x40; k++) {
            fr[k] = fr[0x50 + k];
        }
        for (k = 0; k < 0x10; k++) {
            fr[0x40 + k] = fr[0x90 + k];
        }

        func_00129C28((s32)(fr + 0x20), (s32)(s3 + 0x80), (s32)(fr + 0x90), (s32)(fr + 0x40));

        s1 = s5 + 0x10;
        if (*(u8 *)(s7 + 0xB + s0v) == 0) {
            func_00129BD0((s32)(fr + 0x20), (s32)(fr + 0x20), -1.0f);
        }

        var_s0 = s3 + 0x60;
        s2 = 1;
        do {
            s2 -= 1;
            func_00129C28((s32)(fr + 0x10), (s32)var_s0);
            var_s0 += 0x10;
            temp_v0 = EftPtcl3_Create((s32)fr);
            *(s32 *)s1 = temp_v0;
            s1 += 0xC;
            EftPtcl3_SetType(temp_v0, 3);
        } while (s2 >= 0);

        s4 += 1;
        fp += 0x50;
        s5 += 4;
        s6 += 4;
    } while (s4 < 3);
}
