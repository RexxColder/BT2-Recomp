#include "common.h"

extern u8 *D_0042BB70 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_00402E58(s32 arg0);
void func_004033B0(u8 *g);
void func_00403420(void);
void func_00404998(void);
void func_004049F8(s32 *out);
void func_00405200(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x00405360: menu main loop. sp[0] is set to 1 before the first call and handed to func_004049F8. */
s32 func_00405360(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_00402E58(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_00404998();
        func_00403420();
        BattleSetup_Finish();
        func_00405200();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_0042BB70 + 0x128) == 0 &&
            func_26EB60(D_0042BB70 + 0x38) != 0) {
            *(s32 *)(D_0042BB70 + 0x128) = 1;
            func_2493C0(*(s32 *)(D_0042BB70 + 0x8), 0x36A3, 0x3ABC, 0, *(s32 *)(D_0042BB70 + 0x114));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if ((*(s32 *)(D_0042BB70 + 0x10C) & 2) == 0) {
                if (*(s32 *)(D_0042BB70 + 0x364) == 0) {
                    func_004049F8(sp);
                }
            } else {
                v = *(s32 *)(D_0042BB70 + 0x124) - 1;
                *(s32 *)(D_0042BB70 + 0x124) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                }
            }
            continue;
        }
        break;
    }
    func_004033B0(D_0042BB70);
    func_28B218();
    return sp[0];
}
