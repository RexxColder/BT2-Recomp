#include "m2c_macros.h"

s32 func_0010B568(s32 arg0);
extern u8 *D_003876A0;

s32 func_0010A5F8(void) {
    u8 *p = D_003876A0;

    *(s64 *)(p + 0x4D8) = *(s64 *)(p + 0x4D8) & (s64)-0x201;
    p = D_003876A0;
    *(s64 *)(p + 0x4D8) = *(s64 *)(p + 0x4D8) & (s64)-0x401;
    func_0010B568((s32)p);
    return 1;
}
