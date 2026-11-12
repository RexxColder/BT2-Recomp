#include "common.h"

s32 func_002CBE18(s32 arg0);
void func_002CBD60(s32 arg0);
s32 func_002CE750(void);
void func_00316210(s32 arg0);
void sceMpegReset(s32 arg0);
void func_002CC388(s32 arg0);

void func_002CC300(u8 *arg0) {
    u8 *s0;
    s32 a0;

    if (func_002CBE18((s32)arg0) != 0) {
        s0 = *(u8 **)(arg0 + 0x1FC0);
        func_002CBD60((s32)(s0 + 0x1198));
        a0 = (s32)(s0 + 0x1150);
        if (func_002CE750() != 1) {
            func_00316210(a0);
            return;
        }
        sceMpegReset(a0);
        func_002CC388((s32)arg0);
    }
}
