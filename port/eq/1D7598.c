#include "common.h"

void Vu0Screen_StoreMtx(s32 *m);
void func_001DAA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
extern void *D_00387E9C;

void func_001D7598(void) {
    s32 sp[16];
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
    u8 *G;
    u8 *var_s0;
    u32 var_s1;

    G = (u8 *)D_00387E9C;
    if (*(s32 *)(G + 0x1440) != 0) {
        var_s1 = 0;
        Vu0Screen_StoreMtx(sp);
        if (*(s32 *)(G + 0x16B8) != 0) {
            var_s0 = *(u8 **)(G + 0x141C);
            do {
                if ((var_s0[0x67] != 0) && (var_s0[0x68] != 0)) {
                    w40 = (s32)(*(f32 *)(G + 0x14A0) * *(f32 *)(var_s0 + 0x5C));
                    w44 = (s32)(*(f32 *)(G + 0x14A4) * *(f32 *)(var_s0 + 0x5C));
                    w48 = (s32)(*(f32 *)(G + 0x14A8) * *(f32 *)(var_s0 + 0x5C));
                    w4C = (s32)(*(f32 *)(var_s0 + 0x34) * (*(f32 *)(G + 0x14AC) * 0.0078125f));
                    if ((f32)w4C < 0.0f) {
                        w4C = 0;
                    }
                    if ((f32)w4C > 255.0f) {
                        w4C = 255;
                    }
                    func_001DAA60((s32)var_s0, (s32)sp, (u8)w40, (u8)w44, (u8)w48, (u8)w4C,
                                  (s32)(G + 0x14B0 + (var_s0[0x65] << 4)), (s32)var_s0[0x66],
                                  *(f32 *)(var_s0 + 0x28), *(f32 *)(var_s0 + 0x4C),
                                  *(f32 *)(var_s0 + 0x10), *(f32 *)(var_s0 + 0x14),
                                  *(f32 *)(var_s0 + 0x18), *(f32 *)(var_s0 + 0x1C));
                }
                var_s1 += 1;
                var_s0 += 0x70;
            } while (var_s1 < *(u32 *)(G + 0x16B8));
        }
    }
}
