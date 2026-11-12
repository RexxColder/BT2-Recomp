#include "common.h"

void func_0016DD90(s32 arg0, s32 arg1);
void func_0016E1D8(s32 arg0, s32 arg1);
void func_0016E318(s32 arg0, s32 arg1);
void func_0016E400(s32 arg0, s32 arg1);
s32 func_00191728(s32 arg0);

s32 func_0016E588(s32 arg0) {
    u8 *p;
    s32 code;
    s32 s1;
    s32 s2;

    p = *(u8 **)(arg0 + 0x38);
    code = *(s32 *)*(s32 *)(*(u8 **)(p + 0xB0) + 0x20);
    s2 = 0;
    p += 0xAC0;

    if (code == 0x157) {
        func_0016E400(arg0, code);
    } else if (code < 0x158) {
        if (code == 0xA7) {
            func_0016E318(arg0, code);
        }
    } else if (code == 0x167) {
        func_0016DD90(arg0, code);
    } else if (code == 0x168) {
        func_0016E1D8(arg0, code);
    }

    s1 = 0xD;
    do {
        if (func_00191728(*(s32 *)(p + 0x20)) == 0) {
            *(s32 *)(p + 0x20) = 0;
        } else {
            s2 = 1;
        }
        s1 -= 1;
        p += 0x30;
    } while (s1 >= 0);
    return s2;
}
