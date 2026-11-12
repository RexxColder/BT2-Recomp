#include "common.h"

extern f32 D_00384C94;
extern f32 D_00384C98;
extern f32 D_00384C9C;

void sceVu0UnitMatrix(void *m);
void sceVu0TransMatrix(void *out, void *in, void *trans);
void func_001EC328(u8 *a0, s32 a1);
void func_001EC310(u8 *a0, void *a1);
f32 EftMath_WrapAngle(f32 farg0);
s32 rand(void);

/* 0x001966D0: fills a per-object transform block at obj+0xA10 (matrix build, random angles,
 * then the flag-selected scale/offset words). Floats f12..f16 are farg0..farg4. */
void func_001966D0(s32 arg0, u8 *arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4) {
    f32 mtx[4][4];
    u8 *s1;

    s1 = arg1 + 0xA10;
    sceVu0UnitMatrix(mtx);
    func_001EC328(s1, *(s32 *)(arg1 + 0xAF8));
    sceVu0TransMatrix(mtx, mtx, arg1 + 0xB30);
    func_001EC310(s1, mtx);
    *(f32 *)(s1 + 0x8C) = farg1;
    *(f32 *)(s1 + 0x9C) = EftMath_WrapAngle((f32)rand() / D_00384C94 * D_00384C98);
    *(f32 *)(s1 + 0xA0) = 1.0f;
    *(f32 *)(s1 + 0xA4) = EftMath_WrapAngle((f32)rand() / D_00384C94 * D_00384C98);
    *(f32 *)(s1 + 0xA8) = D_00384C9C;
    *(f32 *)(s1 + 0xAC) = farg4 * 30.0f;
    *(s32 *)(s1 + 0xB0) = arg2;

    if (arg2 & 0x80) {
        *(f32 *)(s1 + 0x88) = farg0;
        *(s32 *)(s1 + 0x80) = 0;
        *(f32 *)(s1 + 0x84) = farg0 / (farg3 * 30.0f);
    } else {
        *(f32 *)(s1 + 0x80) = farg0;
        if (arg2 & 0x100) {
            *(s32 *)(s1 + 0x88) = 0;
            *(f32 *)(s1 + 0x84) = farg0 / (farg3 * 30.0f);
        } else {
            *(s32 *)(s1 + 0x84) = 0;
            *(s32 *)(s1 + 0x88) = 0;
        }
    }

    if (arg2 & 0x200) {
        *(f32 *)(s1 + 0x98) = farg2;
        *(s32 *)(s1 + 0x90) = 0;
        *(f32 *)(s1 + 0x94) = farg2 / (farg3 * 30.0f);
    } else if (arg2 & 0x400) {
        *(s32 *)(s1 + 0x98) = 0;
        *(f32 *)(s1 + 0x90) = farg2;
        *(f32 *)(s1 + 0x94) = farg2 / (farg3 * 30.0f);
    } else {
        *(f32 *)(s1 + 0x90) = farg2;
        *(s32 *)(s1 + 0x98) = 0;
        *(s32 *)(s1 + 0x94) = 0;
    }
}
