#include "common.h"

void func_0025CD70(s32 arg0);
void func_0025D0A8(s32 arg0);
void func_0025DC38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0025E0B8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s2;
    s32 s1;
    s32 x;

    s2 = (u8 *)arg1;
    func_0025D0A8(arg1);
    func_0025CD70(*(s32 *)(s2 + 0xAF0 + 4));
    s1 = *(s32 *)(s2 + 0xE90);
    if (s1 != 0) {
        *(s8 *)(s1 + 0xC) = 0;
    }
    memset((void *)arg1, 0, 0x1520);
    func_0025DC38(arg0, arg1, arg2, 1);
    x = (s32)((u32)*(s32 *)(arg2 + 0xC) + 0xFFFF5345u);
    *(s32 *)(s2 + 4) = x / 9;
    x = (s32)((u32)*(s32 *)(arg2 + 0xC) + 0xFFFF5345u);
    *(s32 *)(s2 + 8) = x % 9;
}
