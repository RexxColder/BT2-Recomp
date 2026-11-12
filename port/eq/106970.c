#include "common.h"

extern u8 *D_003876A0;

s32 func_00106970(s32 arg0) {
    u32 base = *(u32 *)(D_003876A0 + 0x24);
    u32 v = *(u32 *)(base + arg0 * 4);

    return (s32)(base + ((v >> 2) << 2));
}
