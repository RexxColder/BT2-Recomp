#include "common.h"

s32 func_001D1C78(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_0036F2D0[] __attribute__((section(".data")));

void func_001F4398(s32 arg0) {
    u8 frame[32];
    u8 *buf;

    buf = frame + 0x10;
    *(s64 *)(frame + 0x0) = *(s64 *)(D_0036F2D0 + 0x0);
    *(s64 *)(frame + 0x8) = *(s64 *)(D_0036F2D0 + 0x8);
    memset(buf, 0, 0x10);
    *(f32 *)(buf + 0xC) = 1.0f;
    func_00208DE8(arg0, (s32)buf, 0xB);
    func_001D1C78((s32)buf, (s32)frame, arg0, 1.0f);
}
