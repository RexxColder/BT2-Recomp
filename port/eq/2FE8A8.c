#include "common.h"

s32 func_002EFA40(s32 arg0, s32 arg1);
s32 func_002FD2E8(s32 arg0, s32 arg1);
s32 func_002FE128(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002FE2C0(s32 arg0, s32 arg1);
s32 func_002FE448(s32 arg0, s32 arg1);
void func_002FE6A0(void);
s32 memset(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00356CF0 __attribute__((section(".data")));
extern u8 D_0037E5B0[] __attribute__((section(".data")));
extern u8 D_0037E5E0[] __attribute__((section(".data")));
extern u8 D_0037E610[] __attribute__((section(".data")));
extern u8 D_0037E638[] __attribute__((section(".data")));
extern u8 D_0039DE80[] __attribute__((section(".data")));

s32 func_002FE8A8(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {
    s32 var_v0;
    s32 r;
    u32 temp_lo;

    memset((s32)D_0039DE80, 0, 0x1000);
    if (D_00356CF0 != 0) {
        func_002FE6A0();
    }
    if ((arg0 == 0) || (arg1 == 0) || (arg2 == 0)) {
        func_002FE6A0();
    }
    var_v0 = 0;
    if (arg0 != 0) {
        if (arg1 == 0) {
            func_002EFA40((s32)D_0037E5B0, 0);
            return 0;
        }
        if (arg2 == 0) {
            func_002EFA40((s32)D_0037E5E0, 0);
            return 0;
        }
        memset(arg1, 0, (s32)arg2);
        if (func_002FE2C0(arg0, (s32)D_0039DE80) != 0) {
            temp_lo = arg2 / (u32)(arg3 + 9);
            r = func_002FE128(arg1, (s32)D_0039DE80, 0x1000, (s32)temp_lo, arg3);
            r = func_002FE448(arg1, r);
            var_v0 = (s32)(temp_lo * 8) + (r * (arg3 + 1));
            return var_v0;
        }
        func_002EFA40((s32)D_0037E610, arg0);
        func_002FD2E8(0, (s32)D_0037E638);
        return 0;
    }
    return var_v0;
}
