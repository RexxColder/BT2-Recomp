#include "common.h"

s32 Rand_Range();
s32 func_002B3F78(s32 arg0);
s32 func_002B61E0(s32 arg0);
void func_002BBFF8(s32 arg0, s32 arg1);
void func_002BA0F8(s32 arg0);
s32 func_002BA078(s32 arg0);
void func_002BA0D8(s32 arg0);
void func_002B5DC8(s32 arg0);
void func_002B6E40(s32 arg0);
void func_002B6B90(s32 arg0);
void func_002B7290(s32 arg0, s32 arg1);
void func_002BBD28(s32 arg0, s32 arg1);
void func_002BBBB0(s32 arg0);
extern u8 D_00378B08 __attribute__((section(".data")));
extern u8 D_00378B38 __attribute__((section(".data")));

s32 func_002B6D10(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;

    s0 = arg0;
    s1 = s0 + 0x284;
    s2 = s0 + 0x2A4;
    func_002B61E0((s32)s0);
    if (*(s32 *)(s0 + 0x3C) != 0) {
        if (func_002B3F78((s32)s0) != 0) {
            return Rand_Range((s32)&D_00378B08, 0);
        }
        func_002BBFF8((s32)s0, 0);
        func_002BBFF8((s32)s0, 1);
        func_002BA0F8((s32)s0);
        if (func_002BA078((s32)s0) != 0) {
            return Rand_Range((s32)&D_00378B38);
        }
        func_002BA0D8((s32)s0);
        func_002B5DC8((s32)s0);
    }
    func_002B6E40((s32)s0);
    func_002B6B90((s32)s0);
    func_002B7290((s32)s0, *(s8 *)(s0 + 0x72));
    func_002BBD28((s32)s1, 1);
    func_002BBD28((s32)s2, 1);
    func_002BBBB0((s32)s1);
    func_002BBBB0((s32)s2);
    *(s32 *)(s0 + 0x84) = 0;
    *(s32 *)(s0 + 0x2D4) = 0;
    *(s32 *)(s0 + 4) = 1;
    *(s8 *)(s0 + 0x71) = 0;
    return 1;
}
