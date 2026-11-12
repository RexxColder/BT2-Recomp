#include "common.h"

s32 func_00101578(s32 arg0, s32 arg1, s32 arg2);
void func_002F52A8(s32 arg0, s32 arg1);
void func_002F7040(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387F04;
extern s32 D_00387F20[];

void func_001018E8(s32 arg0, s32 arg1) {
    s32 temp_v0;

    if (((u32)(arg0 - 0x76A) < 0xF0U) || ((u32)(arg0 - 0x3C1B) < 0xCU)) {
        func_002F52A8(D_00387F04, func_00101578(arg1, 0, arg1));
    } else {
        func_002F52A8(D_00387F04, func_00101578(arg1, 1, arg1));
    }
    temp_v0 = arg0 < 0x33B2;
    /* gp-relative table at gp - 0x3ED0 (gp = 0x38BDF0), index 0 or 1 */
    func_002F7040(D_00387F04, *(s32 *)((u8 *)D_00387F20 + ((temp_v0 != 0) ? 0 : 4)), (temp_v0 != 0) ? arg0 : (arg0 - 0x33B2));
}
