#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
s32 sceVu0InversMatrix(s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_001AFED8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 farg0, f32 farg1);
extern s32 gBtlCamView;
extern u8 *D_00387858;

void func_001AF780(s32 arg0, s32 arg1) {
    s32 m1[16];
    s32 m2[16];
    s32 buf[4];
    s32 s1;
    s32 t2;
    s32 t3;
    s32 i;
    f32 f0;
    f32 x;
    u8 v0;

    s1 = arg0;
    Vu0Screen_StoreMtx((s32)m1);
    sceVu0InversMatrix((s32)m2, gBtlCamView);
    m2[12] = 0; /* swc1 $f0(0.0) at sp+0x80/0x84/0x88: the translation row is cleared */
    m2[13] = 0;
    m2[14] = 0;
    if (s1 == 0) {
        return;
    }
    v0 = *(u8 *)(s1 + 0x58);
    for (;;) {
        if (v0 != 0) {
            func_00312638((s32)buf, s1, arg1);
            f0 = *(f32 *)(s1 + 0x38);
            if (f0 >= 2147483648.0f) {
                /* cvt.w.s (truncates toward zero) of f0 - 2^31, then | 0x80000000 */
                x = f0 - 2147483648.0f;
                i = (s32)x;
                t2 = i | (s32)0x80000000;
            } else {
                /* cvt.w.s (truncates toward zero) of f0 */
                x = f0;
                i = (s32)x;
                t2 = i;
            }
            t2 = t2 & 0xFF;
            t3 = *(s32 *)(D_00387858 + 0x170) + (*(s32 *)(s1 + 0x4C) << 4) + 0x40;
            func_001AFED8((s32)buf, (s32)m1, (s32)m2, *(u8 *)(s1 + 0x50), *(u8 *)(s1 + 0x51),
                          *(u8 *)(s1 + 0x52), t2, t3, *(u8 *)(s1 + 0x56),
                          *(f32 *)(s1 + 0x2C), 0.0f);
        }
        s1 = *(s32 *)(s1 + 0x60);
        if (s1 == 0) {
            break;
        }
        v0 = *(u8 *)(s1 + 0x58);
    }
}
