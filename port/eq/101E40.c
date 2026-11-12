#include "common.h"

extern u8 *D_003876A0;

void func_00101E40(s32 arg0, s32 arg1) {
    *(s32 *)(D_003876A0 + 0x484) = arg1;
    *(s32 *)(D_003876A0 + 0x480) = arg0;
}
