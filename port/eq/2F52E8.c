#include "common.h"

s32 func_002EA050(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002EFF18(s32 arg0, s32 arg1);
s32 func_002F1630(s32 arg0);
extern u8 D_0037CA10[] __attribute__((section(".data")));

s32 func_002F52E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;

    if (arg0 == NULL) {
        return func_002EA050(D_0037CA10, arg1, arg2, arg3);
    }
    *(s16 *)(arg0 + 0x40) = (s16)arg1;
    if (*(s8 *)(arg0 + 0xAD) == 1) {
        v0 = func_002F1630(*(s32 *)(arg0 + 4));
    } else {
        v0 = 0;
    }
    return func_002EFF18(*(s32 *)(arg0 + 0xC), (s32)*(s16 *)(arg0 + 0x40) + v0);
}
