#include "common.h"

void func_002C0E78(s32 arg0, s32 arg1, s32 arg2);
void func_002CC4A8(s32 arg0, s32 arg1);

void func_002C4720(u8 *arg0, s32 arg1) {
    u8 *s0;
    s32 v;

    s0 = arg0 + 0x1F74;
    v = *(s32 *)(s0 + 0x18);
    if (v != 8) {
        func_002C0E78((s32)arg0, v, 1);
    }
    v = *(s32 *)(s0 + 0x14);
    if (v != 8) {
        func_002C0E78((s32)arg0, v, 1);
    }
    v = *(s32 *)(s0 + 0x1C);
    if (v != 8) {
        func_002C0E78((s32)arg0, v, 1);
    }
    func_002CC4A8((s32)arg0, arg1);
}
