#include "common.h"

extern u8 *D_003876A0;

s32 func_0024B4F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 t0 = 1;
    u8 *a3 = (u8 *)(arg0 * 0x30 + arg2);
    s32 flags = *(s32 *)a3;

    if ((flags & 0x41) != 0 || (flags & 0x20) == 0) {
        return 0;
    }
    if (arg0 == 0xA2) {
        if ((u32)(arg1 - 0x24) < 3U) {
            t0 = 0;
        } else if (arg1 == 0x53 || arg1 == 0x76 || arg1 == 0x77) {
            t0 = 0;
        }
    } else {
        s32 temp_v1 = *(s32 *)(a3 + 0x14);
        if (temp_v1 != 0) {
            u8 *tbl = (u8 *)*(s32 *)(D_003876A0 + 0x74);
            u32 v = *(u16 *)(tbl + arg1 * 16 + 0xA);
            t0 = (s32)((v >> ((temp_v1 - 1) & 31)) & 1);
        }
    }
    return t0;
}
