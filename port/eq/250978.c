#include "common.h"

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00101890(void);
void func_002437E8(void);
void func_002438E8(void);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_00248180(void);
s32 func_0024C148(void);
void func_0024CDD0(void);
void func_0024CF78(s32 arg0);
void func_0024DEF0(void);
void func_0024DFF8(void);
void func_0024F6A0(void);
void func_0024F768(void);
void func_0024F788(s32 arg0);
void func_00250760(void);
void func_00250DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002711A0(void);
void func_00271240(void);
void func_0028B090(void);
void func_0028B218(void);
void func_0028BDA0(void);
void func_00297978(void);
extern u8 *D_003876A4;
extern u8 *D_003879A0;

s32 func_00250978(s32 arg0) {
    s32 sp[4];
    s32 sp0v;
    s32 v;
    s32 a1;
    s32 a2;
    s32 a3;
    s32 v0;
    s32 t;
    s32 flag;
    s32 addr;

    sp[0] = 1;
    func_0024CF78(arg0);
    func_00243968(0, 0, 0);

loop_1:
    func_002711A0();
    func_0024CDD0();
    func_0028B090();
    func_0028BDA0();
    func_00297978();
    func_002438E8();
    func_0024F6A0();
    func_0024DFF8();
    BattleSetup_Finish();
    v = func_0024C148();
    a3 = *(s32 *)(D_003879A0 + 0x1CC);
    a2 = *(s32 *)(D_003879A0 + 0x1C8) + a3 * 7;
    a1 = *(s32 *)(D_003879A0 + 0x1DC) * 4 + a2 * 0x22 + v;
    func_00250DC0(*(s16 *)(a1 + 0x1408) - 1, a1, a2, a3);

    if (*(s32 *)(D_003876A4 + 0x1C) != 0x37) {
        func_00248180();
    }
    if (*(s32 *)(D_003876A4 + 0x1C) != 0x29) {
        func_00250760();
    }
    func_002437E8();
    func_00271240();
    if (ColorFade_IsFadingOut() != 0) {
        func_00101890();
        goto loop_1;
    }

    if (ColorFade_IsOutDone() != 0) {
        if (*(s32 *)(D_003879A0 + 0x3224) != 4) {
            goto loop_1;
        }
        sp0v = sp[0];
        if (sp0v != 0) {
            a1 = *(s32 *)(D_003879A0 + 0x1CC);
            v0 = *(s32 *)(D_003879A0 + 0x1C8);
            t = a1 * 8 - a1;
            *(s32 *)(D_003876A4 + 0x494) = v0 + t;
            *(s32 *)(D_003876A4 + 0x498) = *(s32 *)(D_003879A0 + 0x1DC);
            a2 = *(s32 *)(D_003879A0 + 0x1CC);
            a3 = *(s32 *)(D_003879A0 + 0x1C8);
            t = a2 * 8 - a2 + a3;
            flag = *(s32 *)(D_003876A4 + 0x48C) & 2;
            a1 = (flag == 0) ? 0x1E0 : 0x1E4;
            addr = *(s32 *)(D_003879A0 + a1 + 8) + t * 44;
            *(s32 *)(D_003876A4 + 0x4B0) = *(s32 *)addr;
        }
        func_0024DEF0();
        func_0028B218();
        return sp0v;
    }

    /* L250AC8: the fade-out is not done */
    if ((*(s32 *)(D_003879A0 + 0x1C4) & 0x400) == 0) {
        v0 = *(s32 *)(D_003879A0 + 0x3304);
        if (v0 == 0) {
            func_0024F788((s32)sp);
        }
        goto loop_1;
    }
    v0 = *(s32 *)(D_003879A0 + 0x3230) - 1;
    *(s32 *)(D_003879A0 + 0x3230) = v0;
    if (v0 != -1) {
        goto loop_1;
    }
    func_0024F768();
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x37) {
        goto loop_1;
    }
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x29) {
        goto loop_1;
    }
    a1 = *(s32 *)(D_003879A0 + 0x1CC);
    a2 = *(s32 *)(D_003879A0 + 0x1C8) + a1 * 7;
    *(s32 *)(D_003876A4 + 0x390) = a2;
    goto loop_1;
}
