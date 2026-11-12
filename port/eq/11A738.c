#include "common.h"

s32 func_002605A0(s32 arg0, s32 arg1);
void StgAabb_SetEmpty(s32 arg0);
s32 func_00269B80(s32 arg0, s32 arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void ColSphere_Set(s32 arg0, s32 arg1, f32 farg0);
void ColBounds_OfSphere(s32 arg0, s32 arg1);
void ColBox_AddPointKeepW(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
void ColObb_Init(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
void func_0028D410(s32 arg0, s32 arg1);
void ColBounds_OfObb(s32 arg0, s32 arg1);
extern u8 D_00387A40[] __attribute__((section(".data")));

/* 0x0011A738: for each entry of the global list (stride 0x18580), add the
 * collision primitives of its object to the box at +0x1520. */
void func_0011A738(void) {
    u8 sp[0xC0];
    s32 g;
    s32 base;
    s32 count;
    s32 fp;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 v1;
    f32 f20;

    g = *(s32 *)D_00387A40;
    count = *(s32 *)(g + 4);
    if (count <= 0) {
        return;
    }
    fp = 0;
    do {
        g = *(s32 *)D_00387A40;
        base = *(s32 *)g;
        s0 = base + fp * 0x18580;
        *(s32 *)(s0 + 0x3550) = 0;
        *(s32 *)(s0 + 0x3554) = 0;
        *(s32 *)(s0 + 0xE50) = *(s32 *)(s0 + 0xE50) & 0xFFFFFF;
        func_002605A0(s0, 1);
        if ((s8)*(u8 *)(s0 + 0xD7D) >= 0) {
            s3 = s0 + 0x1520;
            StgAabb_SetEmpty(s3);
            f20 = 1.0f;
            s2 = s0 + 0xD60;
            s5 = 0;
            s7 = 1;
            s4 = (s32)&sp[0x30];
            s6 = (s32)&sp[0x40];
            v1 = *(s32 *)(s2 + 0xC);
            while (s5 < 0x13) {
                if (((s7 << s5) & v1) != 0) {
                    s1 = func_00269B80(s0, s5);
                    if (*(u8 *)(s2 + 0x1F) == 1) {
                        *(f32 *)&sp[0x20] = *(f32 *)(s2 + 0);
                        *(f32 *)&sp[0x24] = *(f32 *)(s2 + 4);
                        *(f32 *)&sp[0x28] = *(f32 *)(s2 + 8);
                        *(f32 *)&sp[0x2C] = f20;
                        sceVu0ApplyMatrix(s4, s1, (s32)&sp[0x20]);
                        ColSphere_Set(s0 + 0x1540 + *(s32 *)(s0 + 0x3550) * 32, s4, *(f32 *)(s2 + 0x10));
                        ColBounds_OfSphere((s32)&sp[0], s0 + 0x1540 + *(s32 *)(s0 + 0x3550) * 32);
                        *(s32 *)(s0 + 0x3550) = *(s32 *)(s0 + 0x3550) + 1;
                        ColBox_AddPointKeepW(s3, (s32)&sp[0]);
                        ColBox_AddPointKeepW(s3, (s32)&sp[0xC]);
                    } else {
                        *(f32 *)&sp[0x20] = *(f32 *)(s2 + 0);
                        *(f32 *)&sp[0x24] = *(f32 *)(s2 + 4);
                        *(f32 *)&sp[0x28] = *(f32 *)(s2 + 8);
                        *(f32 *)&sp[0x2C] = f20;
                        sceVu0ApplyMatrix(s4, s1, (s32)&sp[0x20]);
                        sceVu0CopyMatrix(s6, s1);
                        func_003126C8((s32)&sp[0x70], s4);
                        ColObb_Init(s0 + 0x17A0 + *(s32 *)(s0 + 0x3554) * 400, s4,
                                    *(f32 *)(s2 + 0x10), *(f32 *)(s2 + 0x14), *(f32 *)(s2 + 0x18));
                        func_0028D410(s0 + 0x17A0 + *(s32 *)(s0 + 0x3554) * 400, s6);
                        ColBounds_OfObb((s32)&sp[0], s0 + 0x17A0 + *(s32 *)(s0 + 0x3554) * 400);
                        *(s32 *)(s0 + 0x3554) = *(s32 *)(s0 + 0x3554) + 1;
                        ColBox_AddPointKeepW(s3, (s32)&sp[0]);
                        ColBox_AddPointKeepW(s3, (s32)&sp[0xC]);
                    }
                }
                s5 += 1;
                v1 = *(s32 *)(s2 + 0xC);
            }
        }
        fp += 1;
        g = *(s32 *)D_00387A40;
        count = *(s32 *)(g + 4);
    } while (fp < count);
}
