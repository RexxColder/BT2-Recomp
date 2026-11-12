#include "common.h"

s32 Rand_Range();
s32 func_002B6538();
void func_002B6700(s32 arg0);
s32 func_002B8280(s32 arg0);
void func_002BD2E0(s32 arg0);
s32 func_002CCA78(s32 arg0, s32 arg1);
s32 func_002D0710(s32 arg0, s32 arg1, s32 arg2);
void func_002BBD28(s32 arg0, s32 arg1);
extern u8 D_00378CC0 __attribute__((section(".data")));
extern u8 D_00378CE8 __attribute__((section(".data")));
extern u8 D_00378D10 __attribute__((section(".data")));
extern u8 D_00378D18 __attribute__((section(".data")));

void func_002B7290(u8 *arg0, s32 arg1) {
    s32 sp[2];
    s32 r1;
    s32 r2;
    s32 r3;
    s32 s3;
    s32 s1;

    r1 = func_002B8280((s32)arg0);
    if (r1 != 1) {
        Rand_Range((s32)&D_00378CC0);
        return;
    }
    s3 = *(s32 *)(arg0 + 0x3C);
    if ((*(s8 *)(arg0 + 0x72) != 0) || (arg1 != 0)) {
        r2 = func_002B6538();
        if (r2 == r1) {
            s1 = *(s32 *)(arg0 + 8);
            if (s1 == r2) {
                if (func_002D0710(s3, 6, (s32)sp) == 0) {
                    if (sp[0] == s1) {
                        func_002BD2E0((s32)arg0);
                    }
                } else {
                    func_002BD2E0((s32)arg0);
                }
            }
        }
        r3 = func_002CCA78(s3, arg1);
        if (r3 != 0) {
            func_002B6700(-0x136);
            if (arg1 == 1) {
                Rand_Range((s32)&D_00378CE8, (s32)&D_00378D10);
            } else {
                Rand_Range((s32)&D_00378CE8, (s32)&D_00378D18);
            }
        }
        func_002BBD28((s32)(arg0 + 0x284), arg1);
        func_002BBD28((s32)(arg0 + 0x2A4), arg1);
        *(s8 *)(arg0 + 0x72) = arg1;
    }
}
