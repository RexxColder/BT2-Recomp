#include "common.h"

void func_0014EEF8(s32 arg0, s32 arg1, s32 arg2);

void func_001826E8(u8 *arg0) {
    u8 *a = *(u8 **)(arg0 + 0x38);

    func_0014EEF8(*(s32 *)(a + 0xA00 + 0x24), (s32)a, (s32)a);
}
