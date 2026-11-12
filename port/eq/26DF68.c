#include "common.h"

void func_0026C770(s32 arg0, s32 arg1);
s32 func_0026CCF8(s32 arg0, s32 arg1, s32 arg2);
void func_0026DC60(u8 *arg0, s32 arg1);
void func_0026EA88(s32 arg0);

void func_0026DF68(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s2;
    s32 s4;
    s32 s5;
    s32 tmp_s2;
    s32 a1;
    s32 r;
    u8 tb;
    u8 v0b;

    s5 = arg2 & 0xFF;
    if (arg1 > 0) {
        s4 = arg1;
        do {
            if (*(s32 *)(arg0 + 0x10) & 0x1200) {
                tb = arg0[0x11];
                if (tb & 0x10) {
                    v0b = tb & 0xAF;
                    if (s5 == 0) {
                        tmp_s2 = *(s32 *)(arg0 + 0x8);
                        if (tb & 0x40) {
                            a1 = *(s32 *)(arg0 + 0xC);
                        } else {
                            func_0026EA88(*(s32 *)arg0);
                            a1 = 0;
                        }
                        s0 = a1;
                        arg0[0x11] = arg0[0x11] | 0x22;
                        if (s0 < tmp_s2) {
                            do {
                                r = func_0026CCF8(*(s32 *)(arg0 + 0x4), s0, 0);
                                s0 += 1;
                                func_0026DC60(arg0, r);
                            } while (s0 < tmp_s2);
                        }
                        *(s32 *)(arg0 + 0x8) = tmp_s2;
                        arg0[0x11] = arg0[0x11] & 0xDF;
                        v0b = arg0[0x11] & 0xAF;
                    }
                    arg0[0x11] = v0b;
                }
                r = func_0026CCF8(*(s32 *)(arg0 + 0x4), *(s32 *)(arg0 + 0x8), 0);
                func_0026DC60(arg0, r);
                tb = arg0[0x11];
                if (!(tb & 0x10)) {
                    if (tb & 0x4) {
                        arg0[0x11] = tb & 0xFB;
                    } else if (tb & 0x8) {
                        arg0[0x11] = tb & 0xF7;
                    } else if (tb & 0x1) {
                        arg0[0x11] = tb & 0xFC;
                    } else {
                        *(s32 *)(arg0 + 0x8) = *(s32 *)(arg0 + 0x8) + 1;
                    }
                }
                if (s5 != 0) {
                    if (*(u16 *)(arg0 + 0x12) != 0) {
                        s0 = 0;
                        s2 = 0;
                        do {
                            s0 += 1;
                            func_0026C770(*(s32 *)(arg0 + 0x14) + s2, arg1);
                            s2 += 0xC;
                        } while (s0 < *(u16 *)(arg0 + 0x12));
                    }
                }
            }
            s4 -= 1;
        } while (s4 != 0);
    }
    if (s5 == 0) {
        if (*(u16 *)(arg0 + 0x12) != 0) {
            s0 = 0;
            s2 = 0;
            do {
                s0 += 1;
                func_0026C770(*(s32 *)(arg0 + 0x14) + s2, arg1);
                s2 += 0xC;
            } while (s0 < *(u16 *)(arg0 + 0x12));
        }
    }
}
