#include "common.h"

void func_002822C8(s32 arg0, s32 arg1, f32 farg0);
void func_0019FFA8(s32 arg0);
extern s32 D_00387808;

void func_001A0C28(void) {
    s32 temp_a1;
    s32 temp_v3;

    if (D_00387808 == 0) {
        return;
    }
    temp_a1 = *(s32 *)(D_00387808 + 0x5B0);
    if (temp_a1 == 0) {
        return;
    }
    if (*(s32 *)(*(s32 *)(temp_a1 + 0x28)) != (s32)0x0019FFA8u) {
        return;
    }
    if ((*(u8 *)temp_a1 & 1) != 0) {
        return;
    }
    temp_v3 = *(s32 *)(temp_a1 + 0x38);
    *(s32 *)(temp_v3 + 0x28) = *(s32 *)(temp_v3 + 0x28) | 0x20;
    func_002822C8(2, 1, 1.0f);
}
