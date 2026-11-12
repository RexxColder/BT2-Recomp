#include "common.h"

s32 func_0010B078(void);
void *func_0010B080(void);
s32 func_0020A758(s32 arg0, s32 arg1);
s32 BtlCtrl_IsInterruptible(s32 arg0);
s32 func_0020A908(s32 arg0);
s32 func_0020C6D0(s32 arg0);
s32 func_0020B378(s32 arg0);
s32 func_0020A960(s32 arg0);
s32 func_0020A658(s32 arg0);
s32 func_0020AF80(s32 arg0);
void func_00112B28(s32 arg0);
void func_00116BE8(s32 arg0);
void func_0010C3B8(s32 arg0, s32 arg1);
s32 BtlObjVis_GetView(s32 arg0);
void func_00116A90(s32 arg0, s32 arg1);
void func_0010C4E0(void);
void func_00116CE0(s32 arg0);
extern u8 *D_003876A0;

void func_001172C8(void) {
    s32 s1;
    s32 s2;
    s32 s0;
    u8 *b080;
    s32 var_s1;

    s1 = func_0010B078();
    b080 = (u8 *)func_0010B080();
    s2 = !(*(s64 *)(D_003876A0 + 0x4D8) & 2) ? 1 : 2;
    if (func_0020A758(0, 1) == 0 && func_0020A758(1, 0) == 0
        && BtlCtrl_IsInterruptible(0) == 0 && BtlCtrl_IsInterruptible(1) == 0
        && func_0020A908(0) == 0 && func_0020A908(1) == 0
        && func_0020C6D0(0) == 0 && func_0020C6D0(1) == 0
        && func_0020B378(0) == 0 && func_0020B378(1) == 0
        && func_0020A960(0) == 0 && func_0020A960(1) == 0
        && func_0020A658(0) == 0 && func_0020A658(1) == 0
        && func_0020AF80(0) == 0 && func_0020AF80(1) == 0) {
        func_00112B28(*(s32 *)(b080 + 0x10));
        s0 = 0;
        if (s2 != 0) {
            var_s1 = s1 + 0x1130;
            do {
                func_00116BE8(s0);
                func_0010C3B8(0x80, 0x80);
                {
                    s32 a0 = var_s1;
                    var_s1 += 0x110;
                    func_00116A90(a0, BtlObjVis_GetView(s0));
                }
                func_0010C4E0();
                func_00116CE0(s0);
                s0 += 1;
            } while (s0 < s2);
        }
    }
}
