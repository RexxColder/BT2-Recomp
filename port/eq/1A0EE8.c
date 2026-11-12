#include "m2c_macros.h"

void func_0014EEF8(s32 arg0, s32 arg1);
extern s32 *D_0038780C;

void func_001A0EE8(void *arg0) {
    u8 *temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);

    *(s32 *)(temp_s0 + 0x40) = 0;
    func_0014EEF8(*(s32 *)(temp_s0 + 0x34), (s32)(temp_s0 + 0x70));
    D_0038780C[*(s32 *)temp_s0] = 0;
}
