#include "common.h"

extern u8 *D_00427330 __attribute__((section(".data")));

void func_003DEC38(s32 arg0);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2711A0(void);
void func_28B090(void);
void func_28BDA0(void);
void func_297978(void);
void func_2438E8(void);
void func_003DF4A8(void);
void func_003DF028(void);
void func_2437E8(void);
void func_271240(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_101890(void);
void func_003DEFB8(void);
void func_28B218(void);
void func_003DF5C0(s32 *arg0);

/* 0x003DF8C8: sp[0] = 1; func_003DEC38(); func_243968(0,0,0); then loop: the common update calls, while
 * ColorFade_IsFadingOut() call func_101890 and repeat. When ColorFade_IsOutDone() == 0: if G->0xDC has bit 2, G->0xEC -= 1
 * and at -1 call func_243A80(0,0,0); otherwise func_003DF5C0(sp). Repeat. Once done: func_003DEFB8(), func_28B218(),
 * return sp[0]. (G = D_00427330.) */
s32 func_003DF8C8(s32 arg0) {
    s32 sp[4];
    u8 *g;
    s32 v;

    sp[0] = 1;
    func_003DEC38(arg0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003DF4A8();
        func_003DF028();
        func_2437E8();
        func_271240();

        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            g = D_00427330;
            if (*(s32 *)(g + 0xDC) & 2) {
                v = *(s32 *)(g + 0xEC) - 1;
                *(s32 *)(g + 0xEC) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                }
            } else {
                func_003DF5C0(sp);
            }
            continue;
        }
        break;
    }

    func_003DEFB8();
    func_28B218();
    return sp[0];
}
