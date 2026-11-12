#include "common.h"

s32 func_002582E8(s32 arg0);
s32 func_00298158(s32 arg0, s32 arg1);
void func_002AC480(void);
extern u8 D_00344F34[] __attribute__((section(".data")));
extern u8 D_003B2600[] __attribute__((section(".data")));

void func_002AC4A0(void) {
    s32 base;
    s32 temp_a1;
    s32 var_s0;

    base = (s32)D_003B2600;
    temp_a1 = base + 0x54;
    var_s0 = 0;
    if (*(s32 *)(base + 0x4) + 1 == *(s32 *)((s32)D_00344F34 + *(s32 *)base * 0x10)) {
        var_s0 = (*(s32 *)(temp_a1 + 0x38) == 2);
    }
    func_00298158(0, temp_a1);
    if (func_002582E8(var_s0) == 0) {
        func_002AC480();
    }
    func_00298158(1, temp_a1);
}
