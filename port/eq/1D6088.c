#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void Mtx_InverseRT(s32 arg0, s32 arg1);
void func_001DBCB8(void);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129BB8(f32 farg0, s32 arg0, s32 arg1);
void func_001DAA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
extern u8 *D_00387E9C;
extern u8 *gBtlCamView;

/* 0x001D6088: 30 entries of 0xA0 from g+0x1410; each live, flagged entry is transformed and drawn via func_001DAA60. */
void func_001D6088(void) {
    u8 fr[0xB0];
    u8 *g;
    u8 *e;
    s32 k;
    s32 v9;
    s32 c2;
    s32 c3;
    s32 c4;
    s32 c5;
    f32 x;

    g = D_00387E9C;
    if (*(s32 *)(g + 0x1434) == 0) {
        return;
    }
    func_001DBCB8();
    Vu0Screen_StoreMtx((s32)fr);
    Mtx_InverseRT((s32)(fr + 0x40), (s32)gBtlCamView);
    e = *(u8 **)(g + 0x1410);

    for (k = 29; k >= 0; k--, e += 0xA0) {
        if (e[0x90] == 0) {
            continue;
        }
        if (e[0x91] == 0) {
            continue;
        }
        func_00129C50((s32)(fr + 0x90), (s32)(g + 0x1450), (s32)(e + 0x10));
        func_00129B28((s32)(fr + 0x80), (s32)e, (s32)(fr + 0x90));
        func_00129B58((s32)(fr + 0xA0), (s32)(fr + 0x70), (s32)(fr + 0x80));
        Vec3_Normalize((s32)(fr + 0xA0), (s32)(fr + 0xA0));
        func_00129BB8(3.0f, (s32)(fr + 0xA0), (s32)(fr + 0xA0));
        func_00129B28((s32)(fr + 0x80), (s32)(fr + 0x80), (s32)(fr + 0xA0));

        v9 = e[0x8D];
        if ((signed char)e[0x8E] != -1) {
            v9 += (signed char)e[0x8E];
        }

        x = *(f32 *)(e + 0x30);
        c2 = (s32)x;
        if (x >= 2147483648.0f) {
            c2 = (s32)(x - 2147483648.0f) | (s32)0x80000000u;
        }
        c2 &= 0xFF;

        x = *(f32 *)(e + 0x34);
        c3 = (s32)x;
        if (x >= 2147483648.0f) {
            c3 = (s32)(x - 2147483648.0f) | (s32)0x80000000u;
        }
        c3 &= 0xFF;

        x = *(f32 *)(e + 0x38);
        c4 = (s32)x;
        if (x >= 2147483648.0f) {
            c4 = (s32)(x - 2147483648.0f) | (s32)0x80000000u;
        }
        c4 &= 0xFF;

        x = *(f32 *)(e + 0x3C);
        c5 = (s32)x;
        if (x >= 2147483648.0f) {
            c5 = (s32)(x - 2147483648.0f) | (s32)0x80000000u;
        }
        c5 &= 0xFF;

        func_001DAA60((s32)(fr + 0x80), (s32)fr, c2, c3, c4, c5,
                      (s32)(g + 0x14B0 + (v9 << 4)), e[0x8F],
                      *(f32 *)(e + 0x68), *(f32 *)(e + 0x74), 0.0f, 0.0f, 1.0f, 1.0f);
    }
}
