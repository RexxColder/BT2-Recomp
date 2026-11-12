#include "common.h"

/* 0x002CBE70(obj, o1, o2, o3, o4): t = obj->0x1FC0 + 0x1198. *o1 = t[0x18]; *o3 = t[0xC] << 11; *o2 = remainder of
 * (((t[0xC] + t[0x10]) << 11) + t[0x14]) by t[0x18] (the original traps on a zero divisor: no store then);
 * *o4 = (t[0x10] << 11) + t[0x14]. */
void func_002CBE70(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    u8 *t = (u8 *)*(s32 *)(arg0 + 0x1FC0) + 0x1198;
    s32 w0C = *(s32 *)(t + 0xC);
    s32 w10 = *(s32 *)(t + 0x10);
    s32 w14 = *(s32 *)(t + 0x14);
    s32 w18 = *(s32 *)(t + 0x18);
    s32 num;

    *arg1 = w18;
    *arg3 = (s32)((u32)w0C << 11);
    num = (s32)((((u32)w0C + (u32)w10) << 11) + (u32)w14);
    if (w18 != 0) {
        *arg2 = num % w18;
    }
    *arg4 = (s32)(((u32)w10 << 11) + (u32)w14);
}
