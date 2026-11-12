#include "common.h"

s32 func_002BC1A0(s32 arg0);

void func_002BBCC0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;
    s32 fp;

    if (func_002BC1A0(arg0) == 1) {
        temp_v0 = *(u8 **)((u8 *)arg0 + 8);
        if (temp_v0 != 0) {
            fp = *(s32 *)(temp_v0 + 0x20);
            if (fp != 0) {
                ((void (*)(s32, s32, s32))fp)(*(s32 *)((u8 *)arg0 + 0x1C), arg1, arg2);
            }
        }
    }
}
