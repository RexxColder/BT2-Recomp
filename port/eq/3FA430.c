#include "m2c_macros.h"

s32 func_1018B8(s32);
void func_2493C0(s32, s32, s32, s32, s32);
void func_26E9E8(void *);
extern void *D_0042A580 __attribute__((section(".data")));

void func_003FA430(s32 arg0) {
    s32 i;
    s32 off;

    if (M2C_FIELD(D_0042A580, s32 *, 0xD8) == 0 && M2C_FIELD(D_0042A580, s32 *, 0xE4) != 0) {
        if (func_1018B8(arg0) == 5) {
            M2C_FIELD(D_0042A580, s32 *, 0xD8) = 1;
            func_2493C0(M2C_FIELD(D_0042A580, s32 *, 0xC), 0x37A6, 0x3BBF, 0, M2C_FIELD(D_0042A580, s32 *, 0xD8));
        }
    }
    i = 2;
    off = 0;
    do {
        i -= 1;
        func_26E9E8((u8 *)D_0042A580 + off + 0x14);
        off += 0x28;
    } while (i >= 0);
}
