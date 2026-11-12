#include "common.h"

void func_002DDC08(void *arg0);
void func_002DE330(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002DE358(void *arg0, s32 arg1, s32 arg2);
void func_002E01D8(void *arg0);
void func_002E02C8(void *arg0);
void func_002E1A60(void *arg0, void *arg1, u32 arg2);
extern u8 D_00399DA8[] __attribute__((section(".data")));

void *func_002E0448(u8 *arg0) {
    s32 var_a1;
    s32 var_s1;

    var_s1 = 0;
    func_002E01D8(arg0);
    *(s32 *)(arg0 + 0x18C) = 0;
    func_002E1A60(arg0 + 0x190, D_00399DA8, 0x10);
    func_002DDC08(arg0 + 0x250);
    func_002E02C8(arg0 + 0x1D0);
    *(s32 *)(arg0 + 0x384) = 0;
    *(s32 *)(arg0 + 0x388) = 0;
    *(s32 *)(arg0 + 0x3A8) = *(s32 *)(arg0 + 0x1AC);
    *(s32 *)(arg0 + 0x35C) = 0;
    *(s32 *)(arg0 + 0x360) = 0;
    *(s32 *)(arg0 + 0x364) = 0;
    *(s32 *)(arg0 + 0x368) = 0;
    *(s32 *)(arg0 + 0x398) = 0;
    var_a1 = 0;
    do {
        var_s1 += 1;
        func_002DE330(arg0, var_a1, 0, 0, 0);
        var_a1 = var_s1;
    } while (var_s1 < 4);
    func_002DE358(arg0, 0, 0);
    *(s32 *)(arg0 + 0x408) = 0;
    *(s32 *)(arg0 + 0x188) = 2;
    return arg0;
}
