#include "common.h"

void BattleSetup_Finish(void);
s32 BtlCtrl_IsInterruptible(s32 arg0);
void BtlScene_DrawFrame(s32 arg0);
void Ot_Draw(void);
s32 func_00105860(void);
void func_00265BC8(void);
void func_00265D40(s32 arg0, s32 arg1, f32 farg0);
s32 func_00265EB8(s32 arg0);
void func_00273630(s32 arg0);
void func_00275068(s32 arg0);
void func_00280F18(void);
void func_002810B0(void);
void func_002810E8(void);
void func_00281360(void);
void func_002A2AF0(void);
extern u8 *gBtlCam;

s32 func_00102C40(void) {
    s32 v;
    u8 *t;

    func_00273630(*(s32 *)(gBtlCam + 0x600));
    func_00275068(*(s32 *)(gBtlCam + 0x600));
    func_00280F18();
    func_00265BC8();
    if (BtlCtrl_IsInterruptible(0) == 0 && BtlCtrl_IsInterruptible(1) == 0) {
        t = *(u8 **)(gBtlCam + 0x600);
        func_00265D40(0, *(s32 *)(t + 0x254), *(f32 *)(t + 0x2C4));
    } else {
        func_00265D40(0, -1, 0.0f);
    }
    func_00265EB8(0);
    func_002810B0();
    BtlScene_DrawFrame(1);
    Ot_Draw();
    func_002810E8();
    v = 1;
    if (func_00105860() == 0) {
        BattleSetup_Finish();
        func_002A2AF0();
        func_00281360();
        v = 0;
    }
    return v;
}
