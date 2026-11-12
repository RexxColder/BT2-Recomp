#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void func_002D1C18(u8 *arg0, s32 *arg1, s32 *arg2);

void func_002C7AF8(u8 *arg0, u8 *arg1) {
    s32 sp[2];
    u8 *s0;
    s32 diff;

    func_002D1C18(arg1 + 0x10, &sp[0], &sp[1]);
    s0 = arg0 + 0xD30;
    diff = sp[0] - *(s32 *)(s0 + 0x60);
    *(s32 *)(arg1 + 0xC) = 1;
    *(s32 *)(arg1 + 0x30) = diff;
    *(s32 *)(arg1 + 0x34) = sp[1];
    if (diff < *(s32 *)(s0 + 0x8C)) {
        return;
    }
    memcpy(arg0 + 0xD98, arg1 + 0xC, 0x2C);
}
