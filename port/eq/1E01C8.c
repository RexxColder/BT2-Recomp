#include "common.h"

void func_001E0EA0(u8 *arg0);
void func_001E1E28(u8 *arg0, u8 *arg1);

void func_001E01C8(u8 *arg0, u8 *arg1) {
    s32 s2;
    s32 s5;
    s32 s6;
    f32 *s4;
    u8 *s0;
    u8 *s1;
    u8 v;

    s6 = 0;
    memcpy(arg0, arg1, (s32)*(u8 *)(arg1 + 0x21D8) * 0x21E0);
    v = *(u8 *)(arg1 + 0x21D8);
    *(u8 *)(arg0 + 0x10F00) = v;
    if (v != 0) {
        s4 = (f32 *)(arg0 + 0x10F04);
        s1 = arg0 + 0x21D0;
        s5 = 0;
        do {
            *(u8 *)(s1 + 0xD) = 1;
            *(s32 *)(s1 + 0) = 0;
            s0 = arg0 + s5 + 0x10;
            *s4 = 1.0f;
            s2 = 0;
            if (*(s32 *)(s1 - 0x2020) > 0) {
                do {
                    s2 += 1;
                    func_001E0EA0(s0);
                    func_001E1E28(s0 + 0x10, s0 + 0x60);
                    s0 += 0x1B0;
                } while (s2 < *(s32 *)(s1 - 0x2020));
            }
            s6 += 1;
            s4 += 1;
            s1 += 0x21E0;
            s5 += 0x21E0;
        } while (s6 < *(u8 *)(arg0 + 0x10F00));
    }
}
