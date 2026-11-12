#include "common.h"

void func_002E19E0(s32 arg0, void *arg1);
s32 func_002E1A38(s32 arg0);
void func_002E1C98(s32 arg0, s32 arg1);
extern u8 D_0039D650[] __attribute__((section(".data")));
extern u8 StgSlot_Call07[] __attribute__((section(".data")));

void func_002E1930(s32 arg0, s32 arg1, void *arg2) {
    void *var_s1;

    var_s1 = arg2;
    if (arg1 == 8 && var_s1 == NULL) {
        var_s1 = StgSlot_Call07;
    }
    if (arg0 == 0) {
        func_002E19E0(arg1, var_s1);
        *(void **)(D_0039D650 + arg1 * 4) = var_s1;
        return;
    }
    if (func_002E1A38(arg0) != 0) {
        func_002E1C98(0, 0xFF030202);
        return;
    }
    *(void **)((u8 *)arg0 + 0x18 + arg1 * 4) = var_s1;
}
