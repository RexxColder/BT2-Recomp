#include "common.h"

extern f32 D_00383E14;
extern f32 D_00383E18;

s32 func_00109960(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
s32 func_002A0C10(void);
s32 func_002A1340();
void func_002A15B0(s32 arg0);
void func_002A14B0(f32 farg0);
s32 Font_SetScaleXY(f32 farg0, f32 farg1);
s32 func_002A15D0(s32 arg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002A1678(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002A1590(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
s32 func_002A13E8();
s32 BattleSetup_FinishEx(s32 arg0);
s32 Dma_AddZbuf();

void func_00109A20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    f32 scale;
    f32 t;
    s32 s1;
    s32 s2;
    s32 alpha;

    scale = farg0;
    s1 = func_00109960(arg2, arg1, arg2, arg3, farg0);
    s2 = func_002A0C10();
    func_002A1340();
    func_002A15B0(1);
    func_002A14B0(D_00383E14);
    Font_SetScaleXY(D_00383E18, 1.0f);

    t = scale * 128.0f;
    if (t < 2147483648.0f) {
        alpha = (s32)t & 0xFF;
    } else {
        alpha = ((s32)(t - 2147483648.0f) | (s32)0x80000000u) & 0xFF;
    }
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, alpha);
    func_002A15D0(2);

    t = scale * 64.0f;
    if (t < 2147483648.0f) {
        alpha = (s32)t & 0xFF;
    } else {
        alpha = ((s32)(t - 2147483648.0f) | (s32)0x80000000u) & 0xFF;
    }
    func_002A1678(0x20, 0x20, 0xFF, alpha);

    if (arg3 == 0) {
        func_002A1590(0);
    } else if (arg3 == 1) {
        func_002A1590(2);
    } else {
        func_002A1590(1);
    }
    Font_PrintAt(arg0, arg1, s1);
    func_002A13E8();
    BattleSetup_FinishEx(s2);
    Dma_AddZbuf(0xE0, 1);
}
