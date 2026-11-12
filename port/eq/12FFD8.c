#include "common.h"

void EftBubble_EmitBody(s32 arg0, s32 arg1, s32 arg2);
void func_0012FC88(s32 arg0);
s32 func_0013B350(f32 *out);
s32 func_0020B268(s32 arg0);
s32 rand(void);

extern f32 D_003841EC;
extern f32 D_003841F0;
extern u8 *D_003876A0;
extern u8 *gBtlCam;
extern u8 *gEftBubble;

void EftBubble_UpdateAmbient(void) {
    s32 sp[4];
    u8 *temp_s0;
    u8 *temp_v0_2;
    u8 *var_s1;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 var_f1;
    s32 temp_s6;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s64 temp_v0;

    temp_v0 = *(s64 *)(D_003876A0 + 0x4D8);
    if (!(temp_v0 & 0x100) && !(temp_v0 & 2)) {
        sp[0] = 0;
        func_0013B350(sp);
        var_s2 = 0;
        temp_s6 = !(*(s64 *)(D_003876A0 + 0x4D8) & 2) ? 1 : 2;
        if (temp_s6 != 0) {
            temp_f22 = D_003841EC;
            var_s1 = *(u8 **)gEftBubble;
            temp_f21 = D_003841F0;
            var_s5 = 0x60;
            var_s4 = 0;
            var_s3 = 0;
            do {
                if (!(*(f32 *)(gBtlCam + var_s3 + 0x274) < *(f32 *)sp)) {
                    temp_s0 = gEftBubble + (var_s4 + 0x60);
                    temp_f20 = *(f32 *)temp_s0;
                    if ((rand() & 3) != 0) {
                        var_f1 = temp_f20 + temp_f22;
                    } else {
                        var_f1 = temp_f20 + temp_f21;
                    }
                    *(f32 *)temp_s0 = var_f1;
                    temp_v0_2 = gEftBubble + var_s5;
                    temp_f0 = *(f32 *)temp_v0_2;
                    if (temp_f0 > 1.0f) {
                        *(f32 *)temp_v0_2 = temp_f0 - 1.0f;
                        func_0012FC88(var_s2);
                    }
                    if (!(*(u8 *)(var_s1 + 0xC) & 1) && (func_0020B268(*(s32 *)var_s1) != 0)) {
                        EftBubble_EmitBody(*(s32 *)var_s1, 0x78, var_s2);
                    }
                }
                var_s3 += 0x300;
                var_s2 += 1;
                var_s1 += 0x10;
                var_s5 += 4;
                var_s4 += 4;
            } while (var_s2 < temp_s6);
        }
    }
}
