#include "common.h"

void func_00258418(s32 arg0);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002438E8(void);
void BattleSetup_Finish(void);
void func_002587A8(void);
void func_002437E8(void);
void func_00271240(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_00258770(void);
void func_0028B218(void);
extern u8 *D_00387A00;

s32 func_00259288(s32 arg0) {
    s32 temp_v0;

    func_00258418(arg0);
    func_00243968(0, 0, 0);
loop_5:
    func_002711A0();
    func_0028B090();
    func_0028BDA0();
    func_00297978();
    func_002438E8();
    BattleSetup_Finish();
    func_002587A8();
    func_002437E8();
    func_00271240();
    if (ColorFade_IsFadingOut() != 0) {
        goto loop_5;
    }
    if (ColorFade_IsOutDone() == 0) {
        if (*(s32 *)(D_00387A00 + 0xC) & 2) {
            temp_v0 = *(s32 *)(D_00387A00 + 0x10) - 1;
            *(s32 *)(D_00387A00 + 0x10) = temp_v0;
            if (temp_v0 == -1) {
                func_00243A80(0, 0, 0);
            }
        }
        goto loop_5;
    }
    func_00258770();
    func_0028B218();
    return 1;
}
