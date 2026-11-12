#include "common.h"

s32 func_00212878(s32 arg0);

s32  func_0023FCE8(s32 arg0, u32 arg1) {
    u32 idx = (arg1 >= 3) ? 0 : arg1;
    u8 *p;
    u8 ret = 0x64;

    if (func_00212878(arg0) == 0) {
        p = (u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)arg0 + 0x1530) + 0x958);
        ret = *(u8 *)(p + idx + 0xBC);
    }
    return (u8)(ret);
}
