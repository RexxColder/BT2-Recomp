#include "common.h"

void Mtx_InverseRT(s32 *m, s32 cam);
void Vu0Screen_StoreMtx(s32 *m);
void func_00129C50(s32 *out, u8 *a, u8 *b);
void func_00129B28(s32 *out, s32 *a, s32 *b);
void func_00129B58(s32 *out, s32 *a, s32 *b);
void Vec3_Normalize(s32 *out, s32 *a);
void func_00129BB8(s32 *a, s32 *b, f32 f);
void func_001DAA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
extern void *D_00387E9C;
extern s32 gBtlCamView;

void func_001D6868(void) {
    s32 sp[16];
    s32 m40[16];
    s32 v70[4];
    s32 v80[4];
    s32 v90[4];
    s32 spA0;
    s32 spA4;
    s32 spA8;
    s32 spAC;
    u8 *G;
    u8 *var_s1;
    s32 var_s3;

    G = (u8 *)D_00387E9C;
    if (*(s32 *)(G + 0x1438) != 0) {
        Vu0Screen_StoreMtx(sp);
        var_s3 = 0x1D;
        Mtx_InverseRT(m40, gBtlCamView);
        var_s1 = *(u8 **)(G + 0x1414);
        do {
            if ((var_s1[0x6F] != 0) && (var_s1[0x70] != 0)) {
                func_00129C50(v80, G + 0x1450, var_s1 + 0x10);
                func_00129B28(v80, (s32 *)var_s1, v80);
                func_00129B58(v90, v70, v80);
                Vec3_Normalize(v90, v90);
                func_00129BB8(v90, v90, 20.0f);
                func_00129B28(v80, v80, v90);
                spA0 = (s32)(*(f32 *)(G + 0x14A0) * *(f32 *)(var_s1 + 0x64));
                spA4 = (s32)(*(f32 *)(G + 0x14A4) * *(f32 *)(var_s1 + 0x64));
                spA8 = (s32)(*(f32 *)(G + 0x14A8) * *(f32 *)(var_s1 + 0x64));
                spAC = (s32)(*(f32 *)(var_s1 + 0x50) * (*(f32 *)(G + 0x14AC) * 0.0078125f));
                if ((f32)spAC < 0.0f) {
                    spAC = 0;
                }
                if ((f32)spAC > 255.0f) {
                    spAC = 0xFF;
                }
                func_001DAA60((s32)v80, (s32)sp, (u8)spA0, (u8)spA4, (u8)spA8, (u8)spAC,
                              (s32)(G + 0x14B0 + (var_s1[0x6D] << 4)), (s32)var_s1[0x6E],
                              *(f32 *)(var_s1 + 0x44), *(f32 *)(var_s1 + 0x3C),
                              0.0f, 0.0f, 1.0f, 1.0f);
            }
            var_s3 -= 1;
            var_s1 += 0x80;
        } while (var_s3 >= 0);
    }
}
