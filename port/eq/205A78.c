#include "common.h"

void func_001A0BE8(s32 arg0);
void func_001A0C28(s32 arg0);

/* 0x00205A78: s0 = arg0->0x338 (s64). If s0 & (0x8000 << 41): func_001A0BE8(arg0->0x1534). If s0 & (0x8000 << 42):
 * tail call func_001A0C28(a0). After the first call a0 is the callee's leftover: 0 is passed here (GUESS). */
void func_00205A78(u8 *arg0) {
    s64 s0 = *(s64 *)(arg0 + 0x338);
    s32 a0 = (s32)arg0;

    if ((s0 & ((s64)0x8000 << 41)) != 0) {
        func_001A0BE8(*(s32 *)(arg0 + 0x1534));
        a0 = 0;
    }
    if ((s0 & ((s64)0x8000 << 42)) != 0) {
        func_001A0C28(a0);
    }
}
