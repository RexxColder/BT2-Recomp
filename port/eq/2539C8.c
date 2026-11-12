#include "common.h"

void func_00251100(s32 arg0);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002438E8(void);
void func_00252C18(void);
void func_002518F0(void);
void BattleSetup_Finish(void);
void func_00250DC0(s32 arg0);
void func_002437E8(void);
void func_00271240(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_00252C68(s32 arg0);
void func_00251890(s32 arg0);
void func_0028B218(void);
extern u8 *D_003876A4;
extern u8 *D_003879C0;

s32 func_002539C8(s32 arg0) {
    s32 sp0;
    s32 var_a0;
    s32 temp;
    s32 c4;
    s32 a1;
    s32 var;

    sp0 = 1;
    func_00251100(arg0);
    func_00243968(0, 0, 0);
    for (;;) {
        func_002711A0();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        func_002438E8();
        func_00252C18();
        func_002518F0();
        BattleSetup_Finish();
        func_00250DC0(*(s32 *)(D_003879C0 + 0xE0));
        func_002437E8();
        func_00271240();
        if (ColorFade_IsFadingOut() != 0) {
            continue;
        }
        var_a0 = -1;
        if (ColorFade_IsOutDone() == 0) {
            if ((*(s32 *)(D_003879C0 + 0xAC) & 2) != 0) {
                temp = *(s32 *)(D_003879C0 + 0xD0) - 1;
                *(s32 *)(D_003879C0 + 0xD0) = temp;
                if (temp == -1) {
                    func_00243A80(0, 0, 0);
                    *(s32 *)(D_003876A4 + 0x4A0) = *(s32 *)(D_003879C0 + 0xC4);
                    *(s32 *)(D_003876A4 + 0x4A4) = *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0xB0);
                    *(s32 *)(D_003876A4 + 0x4A8) = *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0x2E34);
                    *(s32 *)(D_003876A4 + 0x4AC) = *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0x2E48);
                }
            } else {
                func_00252C68((s32)&sp0);
            }
            continue;
        }
        break;
    }

    if (sp0 != 0) {
        if (*(s32 *)(D_003876A4 + 0x1C) == 0x38) {
            *(s32 *)(D_003876A4 + 0x48C) = *(s32 *)(D_003876A4 + 0x48C) | 4;
            c4 = *(s32 *)(D_003879C0 + 0xC4);
            var_a0 = *(s32 *)(D_003876A4 + 0x1C);
            a1 = *(s32 *)(D_003879C0 + c4 * 4 + 0x2E34);
            if (var_a0 == 0x38) {
                var = ((a1 + *(s32 *)(D_003879C0 + 0xCC)) * 4) + c4 * 0x90C + 0xEC;
            } else {
                var = ((a1 + *(s32 *)(D_003879C0 + 0xCC)) * 4) + c4 * 0x90C + 0xF0;
            }
            *(s32 *)(D_003876A4 + 0x49C) = *(s32 *)(D_003879C0 + var + 8) + 1;
        }
    } else {
        var_a0 = (s32)D_003876A4;
        if (*(s32 *)(D_003876A4 + 0x1C) == 0x38) {
            *(s32 *)(D_003876A4 + 0x48C) = *(s32 *)(D_003876A4 + 0x48C) | 8;
        }
    }
    func_00251890(var_a0);
    func_0028B218();
    return sp0;
}
