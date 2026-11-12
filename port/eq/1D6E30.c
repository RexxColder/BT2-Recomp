#include "common.h"

void Vu0Screen_StoreMtx(s32 *m);
void func_00129B28(u8 *out, u8 *a, u8 *b);
void func_001DB4B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0, f32 farg1);
extern void *D_00387E9C;

void func_001D6E30(void) {
    s32 sp[16];
    u8 sp40[16];
    s32 w50;
    s32 w54;
    s32 w58;
    s32 w5C;
    u8 *G;
    u8 *var_s1;
    s32 var_s2;

    G = (u8 *)D_00387E9C;
    if (*(s32 *)(G + 0x143C) != 0) {
        var_s2 = 0x18;
        Vu0Screen_StoreMtx(sp);
        var_s1 = *(u8 **)(G + 0x1418);
        do {
            if ((var_s1[0x4B] != 0) && (var_s1[0x4C] != 0)) {
                func_00129B28(sp40, var_s1, var_s1 + 0x10);
                w50 = (s32)(*(f32 *)(G + 0x14A0) * *(f32 *)(var_s1 + 0x40));
                w54 = (s32)(*(f32 *)(G + 0x14A4) * *(f32 *)(var_s1 + 0x40));
                w58 = (s32)(*(f32 *)(G + 0x14A8) * *(f32 *)(var_s1 + 0x40));
                w5C = (s32)(*(f32 *)(var_s1 + 0x2C) * (*(f32 *)(G + 0x14AC) * 0.0078125f));
                if ((f32)w5C < 0.0f) {
                    w5C = 0;
                }
                if ((f32)w5C > 0.0f) {
                    w5C = 0xFF;
                }
                func_001DB4B8((s32)sp40, (s32)sp, (u8)w50, (u8)w54, (u8)w58, (u8)w5C,
                              (s32)(G + 0x14B0 + (var_s1[0x49] << 4)), (s32)var_s1[0x4A],
                              *(f32 *)(var_s1 + 0x20), *(f32 *)(var_s1 + 0x38));
            }
            var_s2 -= 1;
            var_s1 += 0x50;
        } while (var_s2 >= 0);
    }
}
