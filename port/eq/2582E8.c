#include "common.h"

void func_00256F10(s32 arg0, s32 arg1);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_002581F0(s32 *arg0);
void func_0028B218(void);
void func_001012D0(void);
void func_00101498(void);
void func_002578E0(void);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002438E8(void);
void func_002580E0(void);
void func_00257930(void);
void BattleSetup_Finish(void);
void func_002437E8(void);
void func_00271240(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
extern u8 *D_003879F8;

s32 func_002582E8(s32 arg0) {
    s32 out[4];
    u8 *ctx;
    s32 cnt;

    out[0] = 1;
    func_00256F10((s32)out, arg0);
    func_00243968(0, 0, 0);

    for (;;) {
        func_002711A0();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        func_002438E8();
        func_002580E0();
        func_00257930();
        BattleSetup_Finish();
        func_002437E8();
        func_00271240();
        if (ColorFade_IsFadingOut() != 0) {
            func_00101498();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            ctx = D_003879F8;
            if (*(s32 *)(ctx + 0xA4) & 2) {
                cnt = *(s32 *)(ctx + 0xAC) - 1;
                *(s32 *)(ctx + 0xAC) = cnt;
                if (cnt == -1) {
                    func_00243A80(0, 0, 0);
                }
            } else {
                func_002581F0(out);
            }
            continue;
        }
        break;
    }

    func_002578E0();
    func_0028B218();
    func_001012D0();
    return out[0];
}
