#include "common.h"

s32 func_00105500(s32 arg0, s32 arg1);
s32 func_00105A88(void);
s32 func_00105DC8(void);
s32 func_00105EE0(s32 arg0, u8 *arg1);
s32 func_00105F08(void);
void func_00107740(void);
s32 func_001081E0(void);
void func_0010AF00(s32 arg0);
void func_0010AF08(void);
void func_0010B008(s32 arg0);
void func_001F8760(s32 arg0);
void func_00284CD8(void);
void func_00284E68(s32 arg0, s32 arg1, f32 farg0);
extern u8 *D_003876A0;
extern u8 *D_003876B4;

s32 func_00105860(void) {
    s32 idx;
    s32 s0;
    s32 v1;
    s32 v0;

    if (*(u8 *)(D_003876B4 + 0x110) == 0) {
        func_00284E68(0, 1, 1.0f);
        *(u8 *)(D_003876B4 + 0x110) = 1;
    }
    idx = *(s32 *)D_003876B4;
    s0 = func_00105500(*(s32 *)(*(u8 **)(D_003876B4 + 0x104) + idx * 20 + 8), idx);
    if (s0 != *(s32 *)D_003876B4) {
        idx = *(s32 *)D_003876B4;
        func_00105500(*(s32 *)(*(u8 **)(D_003876B4 + 0x104) + idx * 20 + 0xC), idx);
        *(s32 *)D_003876B4 = s0;
        v1 = *(s32 *)D_003876B4;
        if (v1 == 0x63) {
            if (func_00105DC8() != 0 ||
                (*(s32 *)(D_003876A0 + 0xB8) == 5 && func_00105EE0(5, D_003876A0) != 0)) {
                *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x8000;
                return 0;
            }
            if (func_00105F08() == 0) {
                return 1;
            }
            func_001F8760(func_00105A88());
            return 1;
        }
        if (*(s32 *)(*(u8 **)(D_003876B4 + 0x104) + v1 * 20) == 0) {
            *(s32 *)D_003876B4 = 6;
        }
        v0 = *(s32 *)D_003876B4;
        func_00105500(*(s32 *)(*(u8 **)(D_003876B4 + 0x104) + v0 * 20), v0);
    }
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        func_0010B008(6);
    } else {
        func_0010AF00(6);
        if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x2000) == 0) {
            func_0010AF08();
        }
        func_00284CD8();
        if (func_001081E0() != 0) {
            func_00107740();
        }
    }
    return 0;
}
