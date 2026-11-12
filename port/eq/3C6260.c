#include "common.h"

extern u8 *D_00421CF4 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_003C2DF0(void);
void func_003C2FF0(s32 arg0);
void func_003C3728(void);
void func_003C37B0(void);
void func_003C38A8(void);
void func_003C4838(void);
void func_003C48F8(s32 *out);
void func_003C5710(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_26EA88(u8 *p);
void func_26EAE0(u8 *p, s32 n);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003C6260: menu state loop on D = D_00421CF4 (the sibling of 0x405360). Fading-out and bit 0x2 of D->0x1FC select
 * the path; out-done with bit 0x2 clear re-arms D->0x208 from D->0x20C (and calls func_26EAE0/func_26EA88 when it is
 * 0); out-done with bit 0x2 set ends when D->0x678 == 4. */
s32 func_003C6260(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003C2FF0(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_003C2DF0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003C37B0();
        func_003C38A8();
        func_003C4838();
        func_003C5710();
        func_2437E8();
        func_271240();
        if (ColorFade_IsFadingOut() != 0 && (*(s32 *)(D_00421CF4 + 0x1FC) & 2)) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            if ((*(s32 *)(D_00421CF4 + 0x1FC) & 2) == 0) {
                *(s32 *)(D_00421CF4 + 0x208) = *(s32 *)(D_00421CF4 + 0x20C);
                if (*(s32 *)(D_00421CF4 + 0x208) == 0) {
                    func_26EAE0(D_00421CF4 + 0x60, 0x3C);
                    func_26EA88(D_00421CF4 + 0x60);
                }
                func_243968(0, 0, 0);
            } else {
                if (*(s32 *)(D_00421CF4 + 0x678) != 4) {
                    continue;
                }
                break;
            }
        }
        if (*(s32 *)(D_00421CF4 + 0x1FC) & 2) {
            v = *(s32 *)(D_00421CF4 + 0x200) - 1;
            *(s32 *)(D_00421CF4 + 0x200) = v;
            if (v == -1) {
                func_243A80(0, 0, 0);
            }
        } else {
            func_003C48F8(sp);
        }
    }
    sp[0] = 0;
    func_003C3728();
    func_28B218();
    return sp[0];
}
