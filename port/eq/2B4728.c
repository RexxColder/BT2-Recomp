#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void Rand_Range(s32 arg0);
s32 func_002B29F8(s32 arg0, s32 arg1);
void func_002B2A18(s32 arg0);
void func_002B2A20(s32 arg0, s32 arg1);
void func_002B2C70(s32 arg0, s32 arg1);
void func_002B4838(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003782C8[] __attribute__((section(".data")));
extern u8 D_0038BB30[] __attribute__((section(".data")));

void func_002B4728(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 a1;

    memset(arg3, 0, 0x2C);
    if (arg0 == 0 || arg1 <= 0 || (arg1 & 0x7FF) != 0) {
        Rand_Range((s32)D_003782C8);
        return;
    }
    if (arg2 != 0) {
        s2 = func_002B29F8((s32)D_0038BB30, 0x8C);
        func_002B2A20(s2, arg2);
        s1 = arg1 >> 11;
        if (s1 > 0) {
            s0 = arg0;
            a1 = s0;
            do {
                s0 += 0x800;
                s1 -= 1;
                func_002B2C70(s2, a1);
                a1 = s0;
            } while (s1 != 0);
        }
        func_002B2A18(s2);
    }
    func_002B4838(arg0, arg1, (s32)arg3);
}
