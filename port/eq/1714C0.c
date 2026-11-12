#include "common.h"

s32 func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

s32 func_001714C0(s32 arg0) {
    u8 *s1;
    u8 *s0;
    u8 *s2;
    s32 code;
    s32 v0;

    s1 = (u8 *)arg0;
    s0 = s1 + 0x40;
    s2 = (u8 *)*(s32 *)(s1 + 0xB0);
    code = *(s32 *)(*(s32 *)(s2 + 0x20));
    if (code == 0x174) {
        v0 = *(s32 *)(s1 + 0x870);
        *(s32 *)(s1 + 4) = v0;
        func_00208DE8(*(s32 *)s2, (s32)s0, v0);
        return func_0012D3A0((s32)(s1 + 0x30), (s32)s0, *(s32 *)s2);
    }
    if (code == 0x175) {
        v0 = *(s32 *)(s1 + 0x870);
        s0 = s1 + 0x40;
        *(s32 *)(s1 + 4) = v0;
        func_00208DE8(*(s32 *)s2, (s32)s0, v0);
        return func_0012D3A0((s32)(s1 + 0x30), (s32)s0, *(s32 *)s2);
    }
    /* no case matched: the asm returns the leftover v0 = 0x175 */
    return 0x175;
}
