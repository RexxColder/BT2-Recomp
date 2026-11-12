#include "common.h"

s32 func_002D68E8(s32 arg0, s32 arg1);
s32 func_002D6C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002D7B30(s32 arg0);
s32 func_002D7DA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002D7F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_0037AD20 __attribute__((section(".data")));
extern u8 D_0037AD28 __attribute__((section(".data")));
extern u8 D_0037AD58 __attribute__((section(".data")));

s32 func_002D7C70(u8 *arg0, u32 *arg1, s32 arg2, s32 arg3) {
    u32 v1;

    if (*(s32 *)(arg0 + 4) == 0) {
        *(s32 *)(arg0 + 4) = func_002D68E8((s32)arg1, (s32)&D_0037AD20);
    }
    if (func_002D7B30(*(s32 *)(arg0 + 0x24)) != 1) {
        return func_002D6C90((s32)arg0, (s32)arg1, (s32)&D_0037AD28, 2);
    }
    v1 = *arg1;
    if (v1 == 2) {
        return func_002D7F08((s32)arg0, (s32)arg1, arg2, arg3);
    }
    if (v1 == 3) {
        return func_002D7DA0((s32)arg0, (s32)arg1, arg2, arg3);
    }
    return func_002D6C90((s32)arg0, (s32)arg1, (s32)&D_0037AD58, 2);
}
