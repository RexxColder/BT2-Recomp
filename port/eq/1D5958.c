#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void func_001DAA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
extern u8 *D_00387E9C;

void func_001D5958(void) {
    s32 sp[16];
    s32 c40;
    s32 c44;
    s32 c48;
    s32 c4c;
    s32 n;
    s32 i;
    u8 *s0;
    u8 *g;
    f32 f1;

    g = D_00387E9C;
    if (*(s32 *)(g + 0x1430) != 0) {
        Vu0Screen_StoreMtx((s32)sp);
        s0 = *(u8 **)(g + 0x140C);
        for (i = 0x11; i >= 0; i--) {
            if (s0[0x5B] != 0 && s0[0x5C] != 0) {
                c40 = (s32)(*(f32 *)(g + 0x14A0) * *(f32 *)(s0 + 0x4C));
                c44 = (s32)(*(f32 *)(g + 0x14A4) * *(f32 *)(s0 + 0x4C));
                c48 = (s32)(*(f32 *)(g + 0x14A8) * *(f32 *)(s0 + 0x4C));
                f1 = *(f32 *)(g + 0x14AC) * 0.0078125f;
                n = (s32)(*(f32 *)(s0 + 0x38) * f1);
                if ((f32)n < 0.0f) {
                    n = 0;
                }
                if (255.0f < (f32)n) {
                    n = 255;
                }
                c4c = n;
                func_001DAA60((s32)s0, (s32)sp, (u8)c40, (u8)c44, (u8)c48, (u8)c4c,
                              (s32)(g + 0x14B0 + (s0[0x58] << 4)), s0[0x59],
                              *(f32 *)(s0 + 0x28), *(f32 *)(s0 + 0x30), 0.0f, 0.0f, 1.0f, 1.0f);
            }
            s0 += 0x60;
        }
    }
}
