#include "common.h"

extern u8 D_0039DE80[] __attribute__((section(".data")));
extern s32 D_00356CF0 __attribute__((section(".data")));
extern u8 D_0037E5B0[] __attribute__((section(".data")));
extern u8 D_0037E5E0[] __attribute__((section(".data")));

void *memset(void *dst, s32 c, u32 n);
void func_002FE6A0(void);
void func_002EFA40();
s32 func_002FE128(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002FE448(s32 arg0, s32 arg1);

/* 0x002FEA28: clears the 4 KB work area D_0039DE80 and, when all of arg0..arg3 are set, returns
 * (arg3 / (arg4 + 9)) * 8 + func_002FE448(arg2, func_002FE128(arg2, arg0, arg1, quotient, arg4)) * (arg4 + 1).
 * Otherwise it reports the missing argument through func_002EFA40 and returns 0. */
s32 func_002FEA28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 q;
    s32 r;
    s32 v;

    memset(D_0039DE80, 0, 0x1000);
    if (D_00356CF0 != 0) {
        func_002FE6A0();
    }
    if (arg0 == 0 || arg2 == 0 || arg1 == 0 || arg3 == 0) {
        func_002FE6A0();
    }

    if (arg0 == 0) {
        return 0;
    }
    if (arg2 == 0) {
        func_002EFA40(D_0037E5B0, 0);
        return 0;
    }
    if (arg1 == 0 || arg3 == 0) {
        func_002EFA40(D_0037E5E0, 0);
        return 0;
    }

    q = (u32)arg3 / (u32)(arg4 + 9);
    r = func_002FE128(arg2, arg0, arg1, (s32)q, arg4);
    v = func_002FE448(arg2, r);
    return (s32)((q << 3) + (u32)v * (u32)(arg4 + 1));
}
