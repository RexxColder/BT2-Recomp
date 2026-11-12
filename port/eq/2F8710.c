#include "common.h"

#define LW(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LH(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define LHU(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define LB(p, off) (*(s8 *)((u8 *)(p) + (off)))
#define LBU(p, off) (*(u8 *)((u8 *)(p) + (off)))

s32 func_002F0388(s32 arg0);
s32 func_002F1330(s32 arg0);
s32 func_002F1ED0(s32 arg0);
void func_002F44A0(u8 *arg0);
void func_002F8620(u8 *arg0);

void func_002F8710(u8 *arg0) {
    s32 s1;
    s32 var_v0;
    s32 temp_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 obj2;
    s16 h;
    s8 a0b;
    void **obj;

    s1 = LB(arg0, 1);
    if ((s1 == 3) && (LB(arg0, 0x72) == 0) && (func_002F0388(LW(arg0, 4)) != s1)) {
        temp_v0 = func_002F1330(LW(arg0, 4));
        if (LW(arg0, 0x64) != temp_v0) {
            LHU(arg0, 0x68) = 0;
        } else {
            h = (s16)(LHU(arg0, 0x68) + 1);
            LHU(arg0, 0x68) = (u16)h;
            if ((LW(arg0, 0x38) * 5) < h) {
                LH(arg0, 0x60) = -2;
            }
        }
        LW(arg0, 0x64) = temp_v0;
        if (LH(arg0, 0x60) != 0) {
            if ((u32)(LBU(arg0, 0x6D) - 1) < 2U) {
                func_002F44A0(arg0);
            }
            var_v0 = s1 - 1;
            if (LBU(arg0, 0x6D) != 0) {
                LH(arg0, 0x60) = 0;
                LHU(arg0, 0x68) = 0;
            }
        } else {
            var_v0 = s1 - 1;
        }
    } else {
        LHU(arg0, 0x68) = 0;
        var_v0 = s1 - 1;
    }

    if (((u32)var_v0 < 3U) && (LB(arg0, 0x72) == 0) && (func_002F0388(LW(arg0, 4)) != 3)) {
        obj = *(void ***)((u8 *)arg0 + 0x14);
        var_v0_2 = 0;
        if (obj != NULL) {
            var_v0_2 = (*(s32 (**)(void *, s32))((u8 *)*obj + 0x24))(obj, 1);
        }
        if (var_v0_2 < 0x40) {
            temp_v0 = (u16)(LHU(arg0, 0x6A) + 1);
            LHU(arg0, 0x6A) = (u16)temp_v0;
            if (s1 == 3) {
                var_v0_3 = LW(arg0, 0x38) * 5;
            } else {
                var_v0_3 = LW(arg0, 0x38) * 0x14;
            }
            if (var_v0_3 < (s16)temp_v0) {
                LH(arg0, 0x60) = -1;
            }
            if (LH(arg0, 0x60) != 0) {
                a0b = LB(arg0, 0x6D);
                if (a0b == 1) {
                    func_002F44A0(arg0);
                } else if (a0b == 2) {
                    func_002F8620(arg0);
                }
                if (LBU(arg0, 0x6D) != 0) {
                    LH(arg0, 0x60) = 0;
                    LHU(arg0, 0x6A) = 0;
                }
            }
        } else {
            LHU(arg0, 0x6A) = 0;
        }
    } else {
        LHU(arg0, 0x6A) = 0;
    }

    obj2 = LW(arg0, 8);
    if ((obj2 != 0) && (func_002F1ED0(obj2) == 4)) {
        a0b = LB(arg0, 0x6D);
        if (a0b == 1) {
            func_002F44A0(arg0);
        } else if (a0b == 2) {
            func_002F8620(arg0);
        }
        if (LBU(arg0, 0x6D) != 0) {
            LHU(arg0, 0x6A) = 0;
            LH(arg0, 0x60) = 0;
        }
    }
}
