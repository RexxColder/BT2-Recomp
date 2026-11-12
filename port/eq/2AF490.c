#include "common.h"

s32 func_002ADFC8(s32 arg0);
extern u8 D_00345138[] __attribute__((section(".data")));

void func_002AF490(s32 arg0) {
    u8 *s0;
    u8 *s2;
    s32 s1;
    s32 idx;

    s0 = (u8 *)arg0;
    s2 = D_00345138;
    idx = func_002ADFC8(arg0);
    s1 = ((s32 (*)(s32))(*(s32 *)(s2 + idx * 16 + 8)))(arg0);
    if (s1 != -1) {
        idx = func_002ADFC8(arg0);
        ((void (*)(s32, s32))(*(s32 *)(s2 + idx * 16 + 0xC)))(arg0, s1);
        *(s32 *)(s0 + 0x180) = s1;
        *(s8 *)(s0 + 0x188) = 0;
        *(s32 *)(s0 + 0x184) = 0;
        idx = func_002ADFC8(arg0);
        ((void (*)(s32))(*(s32 *)(s2 + idx * 16)))(arg0);
    }
    idx = func_002ADFC8(arg0);
    ((void (*)(s32))(*(s32 *)(s2 + idx * 16 + 4)))(arg0);
    *(s32 *)(s0 + 0x184) = *(s32 *)(s0 + 0x184) + 1;
}
