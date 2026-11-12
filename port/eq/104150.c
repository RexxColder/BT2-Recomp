#include "common.h"

extern u8 *D_003876A0;
void func_002A86E8(s32 arg0, s32 arg1, s32 arg2);
void func_00103F50(s32 arg0);

s32 func_00104150(s32 arg0) {
    s32 sp[8] = {0}; /* func_002A86E8 copies 0x18 bytes from this block; asm leaves the tail unwritten */

    sp[0] = 0;
    sp[1] = arg0;
    if (*(s32 *)(D_003876A0 + 0xD4) != arg0) {
        *(s32 *)(D_003876A0 + 0xD4) = arg0;
        func_002A86E8((s32)sp, (s32)func_00103F50, 0);
    }
    return 0;
}
