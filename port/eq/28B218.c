#include "common.h"

extern u8 D_00387EB0;
extern u32 D_0038A628[] __attribute__((section(".data")));
extern s32 gDmaCur;

void func_0028B218(void) {
    s64 temp_a1;
    s32 i;

    temp_a1 = (s64)0xE000 << 47;
    for (i = 0; i < 4; i++) {
        *(s64 *)((u8 *)D_0038A628[i] + 0) = temp_a1;
        *(s64 *)((u8 *)D_0038A628[i] + 8) = 0;
    }
    gDmaCur = (s32)D_0038A628[D_00387EB0];
}
