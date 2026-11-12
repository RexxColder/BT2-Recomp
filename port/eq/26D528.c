#include "common.h"

void func_0026C380(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0026F888(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00270198(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0026D528(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8];
    s32 pos;
    u8 *base;
    s32 op;
    u16 val;
    s32 s0;
    s32 a0v;
    s32 a1v;

    pos = *(s32 *)arg2;
    base = (u8 *)arg1;
    sp[0] = base[pos];
    sp[1] = base[pos + 1];
    sp[2] = base[pos + 2];
    sp[4] = base[pos + 3];
    sp[5] = base[pos + 4];
    *(s32 *)arg2 = pos + 5;
    val = (u16)(sp[0] | (sp[1] << 8));
    op = sp[2];
    s0 = *(s32 *)(arg0 + 0x14) + (s32)(12 * val) - 12;

    if (op == 2) {
        a1v = *(s32 *)(s0 + 4);
        if (a1v != 0) {
            func_0026C380(*(s32 *)(*(s32 *)arg0 + 0x24), a1v, arg2, pos + 3);
            *(s32 *)(s0 + 4) = 0;
        }
        return;
    }
    if (op < 3) {
        if (op == 1) {
            a0v = *(s32 *)s0;
            if (a0v != 0) {
                func_0026F888(a0v, 1, arg2, pos + 3);
                *(s32 *)s0 = 0;
            }
        }
        return;
    }
    if (op == 3) {
        a0v = *(s32 *)(s0 + 8);
        if (a0v != 0) {
            func_00270198(a0v, 3, arg2, pos + 3);
            *(s32 *)(s0 + 8) = 0;
        }
    }
}
