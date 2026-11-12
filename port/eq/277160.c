#include "common.h"

s32 rand(void);
f32 StgAmb_Falloff(f32 farg0, f32 farg1, f32 farg2);
void func_00276FD0(f32 farg0, s32 arg0, s32 arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void sceVu0InversMatrix(void *arg0, s32 arg1);
extern f32 D_00387024;
extern f32 D_00387028;
extern f32 D_0038702C;
extern u8 *D_003876A0;
extern u8 D_00388D68[] __attribute__((section(".data")));
extern s32 gBtlCamView;

void func_00277160(void) {
    f32 sp[16];
    f32 f0;
    f32 fr;
    s32 cnt;
    s32 r;
    s32 t;
    s32 s0;

    cnt = *(s32 *)(D_00388D68 + 0xC);
    if (cnt == 0) {
        cnt = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = cnt;
    }
    cnt = cnt - 1;
    *(s32 *)(D_00388D68 + 0xC) = cnt;
    if (cnt <= 0) {
        cnt = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = cnt;
        r = rand();
        fr = ((f32)r / D_00387024) * 62.0f;
        /* cvt.w.s: truncates toward zero */
        t = (s32)fr;
        s0 = t;
        func_00297FE0(2, 0xA, s0 + 0x3F, rand() % 127, 0);
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        func_00276FD0(D_00387028, 0, gBtlCamView);
        return;
    }
    sceVu0InversMatrix(sp, gBtlCamView);
    if (sp[13] < 0.0f) {
        f0 = StgAmb_Falloff(-sp[13], 0.0f, 700.0f);
    } else {
        f0 = 1.0f;
    }
    func_00276FD0(f0 * D_0038702C, 0, 0);
}
