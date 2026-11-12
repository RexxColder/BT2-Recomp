#include "common.h"

s32 func_00269A40(s32 arg0, s32 arg1);
void func_0026B068(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void BtlMove_ResetAnimStep(s32 arg0) {
    u8 sp[0x300];
    u8 *base;
    u8 *entry;
    u8 *cur;
    u8 *s2;
    s32 i;
    s8 kind;
    s8 idx;
    s8 a1v;
    s32 temp_v0;

    base = (u8 *)arg0;
    i = 0;
    if (*(s32 *)(base + 0x12D0) > 0) {
        s2 = base + 0xFD0;
        entry = base + 0xFF0;
        cur = s2;
        do {
            kind = *(s8 *)entry;
            idx = *(s8 *)(entry + 2);
            a1v = *(s8 *)(entry + 1);
            entry += 0x40;
            if (kind >= 0) {
                if (idx > 0) {
                    temp_v0 = (s32)sp + (idx << 6);
                    func_0026B068(arg0, (s32)cur, temp_v0 - 0x40, temp_v0);
                } else {
                    temp_v0 = func_00269A40(arg0, a1v);
                    if (temp_v0 != 0) {
                        func_0026B068(arg0, (s32)s2, temp_v0 + 0x40, (s32)sp);
                    }
                }
            }
            i += 1;
            cur += 0x40;
            s2 += 0x40;
        } while (i < *(s32 *)(base + 0x12D0));
    }
}
