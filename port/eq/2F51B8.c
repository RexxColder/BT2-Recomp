#include "common.h"

void func_002EA050(s32 arg0);
void func_002EFF48(s32 arg0, s32 arg1);
extern s32 D_0034AED0 __attribute__((section(".data")));
extern u8 D_0037C9B0[] __attribute__((section(".data")));

void func_002F51B8(s32 arg0, s32 arg1) {
    s16 var_v0;

    if (arg0 == 0) {
        func_002EA050((s32) D_0037C9B0);
        return;
    }
    if (arg1 < -0xF) {
        var_v0 = -0xF;
    } else if (arg1 < 0x10) {
        var_v0 = (s16) arg1;
    } else {
        var_v0 = 0xF;
    }
    *(s16 *) (arg0 + 0x46) = var_v0;
    if (D_0034AED0 != 0) {
        func_002EFF48(*(s32 *) (arg0 + 0xC), 0);
        return;
    }
    func_002EFF48(*(s32 *) (arg0 + 0xC), *(s16 *) (arg0 + 0x46));
}
