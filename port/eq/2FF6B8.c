#include "common.h"

void func_002EFA40(s32 arg0, s32 arg1);
s32 func_002FEF90(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
s32 func_002FF130(s32 arg0, s32 arg1);
s32 func_002FF290(s32 arg0, s32 arg1);
void func_002FF448(void);
void func_002FF640(void);
void func_0030B138(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s32 D_00356E98 __attribute__((section(".data")));
extern u8 D_0037E768[] __attribute__((section(".data")));
extern u8 D_0037E798[] __attribute__((section(".data")));
extern u8 D_0037E7C8[] __attribute__((section(".data")));
extern u8 D_0037E7F0[] __attribute__((section(".data")));
extern u8 D_0039EE80[] __attribute__((section(".data")));

s32 func_002FF6B8(s32 arg0, u8 *arg1, u32 arg2, s32 arg3) {
    u32 temp_lo;
    s32 r;
    s32 v;

    memset(D_0039EE80, 0, 0x1000);
    if (D_00356E98 == 0) {
        func_002FF640();
    }
    func_002FF448();
    if (arg0 == 0) {
        return 0;
    }
    if (arg1 == NULL) {
        func_002EFA40((s32)D_0037E768, 0);
        return 0;
    }
    if (arg2 == 0) {
        func_002EFA40((s32)D_0037E798, 0);
        return 0;
    }
    memset(arg1, 0, arg2);
    if (func_002FF130(arg0, (s32)D_0039EE80) != 0) {
        temp_lo = arg2 / (u32)(arg3 + 9);
        r = func_002FEF90((s32)arg1, (s32)D_0039EE80, temp_lo, arg3 + 1);
        v = func_002FF290((s32)arg1, r);
        return (s32)((temp_lo * 8) + (u32)(v * (arg3 + 1)));
    }
    func_002EFA40((s32)D_0037E7C8, arg0);
    func_0030B138(0, (s32)D_0037E7F0);
    return 0;
}
