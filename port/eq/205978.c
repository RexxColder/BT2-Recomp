#include "common.h"

void func_001C9448(s32 arg0);
void func_001C9510(s32 arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_00212900(void);

/* 0x00205978: when the object at arg0+0x1530 has type 0x2E: s1 = 1 if the 64-bit flags at +0x338 have bit 28
 * (0x8000 << 28); otherwise, unless bit 29 is set and func_00211310(arg0, 0, 2) is 0, s1 = 0 if
 * func_00211310(arg0, 0, 0x100) is non-zero, else the byte at +0x908 (flipped when func_00212900() & 3 is 0).
 * Then the byte at +0x908 is set to 1 (calling func_001C9448 on the 0 -> 1 edge), or to 0 (calling
 * func_001C9510 on the 1 -> 0 edge). */
void func_00205978(u8 *arg0) {
    s32 s1 = 0;
    s64 flags;
    u8 v;
    s32 t;

    flags = *(s64 *)(arg0 + 0x338);
    if (*(s32 *)(*(u8 **)(arg0 + 0x1530) + 4) == 0x2E) {
        if (flags & ((s64)0x8000 << 28)) {
            s1 = 1;
        } else if (!(flags & ((s64)0x8000 << 29)) && func_00211310(arg0, 0, 2) != 0) {
            t = func_00212900() & 3;
            v = *(u8 *)(arg0 + 0x908);
            if (t == 0) {
                v ^= 1;
            }
            s1 = (func_00211310(arg0, 0, 0x100) != 0) ? 0 : (v & 0xFF);
        }
        if (s1 == 0) {
            if (*(u8 *)(arg0 + 0x908) == 1) {
                func_001C9510(*(s32 *)(arg0 + 0x1534));
            }
            *(u8 *)(arg0 + 0x908) = 0;
        } else {
            if (*(u8 *)(arg0 + 0x908) == 0) {
                func_001C9448(*(s32 *)(arg0 + 0x1534));
            }
            *(u8 *)(arg0 + 0x908) = 1;
        }
    }
}
