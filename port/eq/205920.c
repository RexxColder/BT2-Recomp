#include "common.h"

void func_00210618(s32 arg0, s32 arg1);
void func_001A1748(s32 arg0);

/* 0x00205920: if (arg0->0x338 as s64) & (0x8000 << 27) is zero, return; otherwise func_00210618(arg0, 0x3C25) and
 * tail call func_001A1748(arg0->0x1534). */
void func_00205920(u8 *arg0) {
    if ((*(s64 *)(arg0 + 0x338) & ((s64)0x8000 << 27)) == 0) {
        return;
    }
    func_00210618((s32)arg0, 0x3C25);
    func_001A1748(*(s32 *)(arg0 + 0x1534));
}
