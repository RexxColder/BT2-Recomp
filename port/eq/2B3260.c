#include "common.h"

s32 func_002B4B08();
extern s32 D_00345338 __attribute__((section(".data")));
extern s32 D_0034533C __attribute__((section(".data")));
extern u8 D_0038BAF0[] __attribute__((section(".data")));

s32 func_002B3260(s32 arg0, void *arg1, void *arg2) {
    s32 s2;
    s32 temp_a3;
    s32 temp_a1;
    s32 mode;
    u8 *out;

    out = (u8 *)arg2;
    s2 = 0;
    temp_a3 = *(s32 *)((u8 *)arg1 + 8) * *(s32 *)((u8 *)arg1 + 0xC);
    temp_a1 = (temp_a3 * 9) / 2 + 0x2840;
    mode = D_00345338;

    if (mode != 0) {
        if (mode < 2 || D_0034533C < temp_a1 || D_0034533C < 0x840D0) {
            *(s32 *)(out + 0) = 0;
            s2 = -1;
            *(s32 *)(out + 4) = 0;
        } else {
            *(s32 *)(out + 4) = *(s32 *)(D_0038BAF0 + 4);
            *(s32 *)(out + 0) = *(s32 *)(D_0038BAF0 + 0);
        }
    } else {
        /* a2 and a3 are the function's own arg2 and temp_a3 for the first call; a1 = temp_a1; t0 = 0x840D0 is the 5th */
        *(s32 *)(out + 0) = func_002B4B08(arg0, temp_a1, arg2, temp_a3, 0x840D0);
        /* second call: a1 = 0x840D0 from the stack slot, a2/a3 left over from the first call */
        *(s32 *)(out + 4) = func_002B4B08(arg0, 0x840D0);
    }
    if (*(s32 *)(out + 0) == 0 || *(s32 *)(out + 4) == 0) {
        s2 = -1;
    }
    return s2;
}
