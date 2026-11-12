#include "common.h"

void func_002F1D30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F1E48(s32 arg0);
s32 func_002F1ED0(s32 arg0);

/* 0x002EB730 adxf_SetFileInfoRange(p, a1, a2, a3, t0): store the range fields, call func_002F1D30
 * (a0 = p->+4, the other four args pass through), then if func_002F1ED0 returns 4 store the 64-bit
 * (t0 << 11) at +0x10 and t0 at +0xC and return 0; otherwise call func_002F1E48 and return -1. */
s32 adxf_SetFileInfoRange(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(s32 *)(arg0 + 0x38) = arg2;
    *(s32 *)(arg0 + 0x40) = arg3;
    *(s32 *)(arg0 + 0x3C) = arg1;
    *(s32 *)(arg0 + 0x34) = arg3;
    *(s32 *)(arg0 + 0x44) = arg4;
    *(s32 *)(arg0 + 0x18) = 0;
    func_002F1D30(*(s32 *)(arg0 + 4), arg1, arg2, arg3, arg4);
    if (func_002F1ED0(*(s32 *)(arg0 + 4)) == 4) {
        *(s64 *)(arg0 + 0x10) = (s64)(s32)((u32)arg4 << 11);
        *(s32 *)(arg0 + 0xC) = arg4;
        return 0;
    }
    func_002F1E48(*(s32 *)(arg0 + 4));
    return -1;
}
