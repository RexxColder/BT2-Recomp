#include "common.h"

/* 0x0011AD58: unless the 64-bit flags at D_003876A0 + 0x4D8 have bit 0x100 set: func_0011AC70 (the four arguments
 * pass through; arity GUESS), func_0011BCD0(), func_0011C588(), then tail call func_0011B3C0(). */
extern u8 *D_003876A0;
void func_0011AC70();
void func_0011BCD0();
void func_0011C588();
void func_0011B3C0();

void func_0011AD58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    func_0011AC70(arg0, arg1, arg2, arg3);
    func_0011BCD0();
    func_0011C588();
    func_0011B3C0();
}
