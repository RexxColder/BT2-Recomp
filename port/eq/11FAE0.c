#include "common.h"

void func_0011FD48(s32 arg0);
void func_00124098(s32 arg0);

void func_0011FAE0(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *t1;
    s32 t2;
    s32 a3;
    s32 v1;
    s32 a2v;
    s32 a1v;
    s32 vv;
    u8 *var_a0;
    s32 v0;

    t1 = arg0 + 0x38;
    t2 = *(s32 *)(t1 + 0x10C);
    a3 = *(s32 *)(t1 + 0x108);
    v1 = t2 + 1;
    a2v = t2 + 0x20;
    a1v = v1 < 0;
    vv = (a1v != 0) ? a2v : v1;
    if (a3 != (v1 - (((vv) >> 5) << 5)) && arg1 >= 0) {
        if (arg1 < 0xED) {
            var_a0 = arg0 + 0x40;
        } else if (arg1 >= 0xF6) {
            if (arg1 < 0xFE) {
                var_a0 = arg0 + 0x40;
            } else if (arg1 == 0xFE) {
                func_0011FD48((s32)arg0);
                func_00124098((s32)arg0);
                return;
            } else {
                return;
            }
        } else {
            return;
        }
        *(s32 *)(var_a0 + t2 * 4) = arg1;
        *(s32 *)(var_a0 + t2 * 4 + 0x80) = arg2;
        v0 = *(s32 *)(t1 + 0x10C) + 1;
        *(s32 *)(t1 + 0x10C) = v0;
        if (v0 >= 0x20) {
            *(s32 *)(t1 + 0x10C) = 0;
        }
    }
}
