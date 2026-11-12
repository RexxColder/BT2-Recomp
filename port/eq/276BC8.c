#include "common.h"

void func_003126C8(u8 *arg0, u8 *arg1);
extern u8 *gBtlStage;
extern u8 *D_003876A0;
extern u8 D_00344BC0[] __attribute__((section(".data")));

s32 func_00276BC8(u8 *arg0) {
    u8 *s0;

    if (gBtlStage == NULL || (*(s64 *)(D_003876A0 + 0x4D8) & 0x2000) != 0) {
        func_003126C8(arg0, D_00344BC0);
        return -1;
    }
    if (*(u8 **)(gBtlStage + 4) == NULL) {
        func_003126C8(arg0, D_00344BC0);
        return -1;
    }
    s0 = *(u8 **)(gBtlStage + 4) + 0x20;
    func_003126C8(arg0, s0);
    func_003126C8(D_00344BC0, s0);
    return 1;
}
