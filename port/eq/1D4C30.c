#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_001DAA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
void func_00208798(s32 arg0, s32 arg1);
extern u8 *D_00387E9C;

void func_001D4C30(void) {
    u8 fr[0x80];
    u8 *g;
    u8 *s0;
    u8 *out;
    s32 i;
    s32 c50;
    s32 c54;
    s32 c58;
    s32 c5c;

    g = D_00387E9C;
    if (*(s32 *)(g + 0x1428) != 0) {
        out = fr + 0x40;
        Vu0Screen_StoreMtx((s32)fr);
        s0 = *(u8 **)(g + 0x1404);
        for (i = 0; i < (s32)*(u32 *)(g + 0x16C0); i++) {
            if (s0[0x90] != 0 && s0[0x91] != 0) {
                if (s0[0x8D] == 0) {
                    func_00129C28((s32)out, (s32)(s0 + 0x10));
                } else if (s0[0x8D] == 1) {
                    func_00208798(*(s32 *)s0, (s32)out);
                    func_00129B28((s32)out, (s32)out, (s32)(s0 + 0x10));
                }
                c50 = (s32)(*(f32 *)(g + 0x14A0) * *(f32 *)(s0 + 0x88));
                c54 = (s32)(*(f32 *)(g + 0x14A4) * *(f32 *)(s0 + 0x88));
                c58 = (s32)(*(f32 *)(g + 0x14A8) * *(f32 *)(s0 + 0x88));
                c5c = (s32)(*(f32 *)(g + 0x14AC) * 0.0078125f * *(f32 *)(s0 + 0x3C));
                if ((f32)c5c < 0.0f) {
                    c5c = 0;
                }
                if (128.0f < (f32)c5c) {
                    c5c = 128;
                }
                func_001DAA60((s32)out, (s32)fr, (u8)c50, (u8)c54, (u8)c58, (u8)c5c,
                              (s32)(g + 0x14B0 + (s0[0x8E] << 4)), s0[0x8F],
                              *(f32 *)(s0 + 0x68), *(f32 *)(s0 + 0x74), 0.0f, 0.0f, 1.0f, 1.0f);
            }
            s0 += 0xA0;
        }
    }
}
