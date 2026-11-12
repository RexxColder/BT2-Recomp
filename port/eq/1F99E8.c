#include "common.h"

s32 func_001F9700(s32 arg0);
extern u8 *D_00387930;

s32  func_001F99E8(s32 arg0) {
    s32 r = func_001F9700(arg0);
    u8 *p = *(u8 **)(D_00387930 + 0x1C);

    return (s16)(*(s16 *)(p + (0x31 - r) * 2 + 0x384));
}
