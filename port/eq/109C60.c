#include "common.h"

s32 func_0025AB48(void);
void func_0027ABE8(f32 farg0);

/* asm 0x109D08..0x109D24: returns 0 without a callback, else (callback(arg0->4) != 0) (was void: 105860 took garbage as next state) */
s32 func_00109C60(u8 *arg0) {
    u8 idx = *(u8 *)(arg0 + 8);

    if (idx < 7) {
        switch (idx) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (func_0025AB48() == 0) {
                func_0027ABE8(1.0f);
                *(u8 *)(arg0 + 8) = *(u8 *)(arg0 + 8) + 1;
            }
            break;
        case 4:
        case 5:
            if (func_0025AB48() == 0) {
                *(u8 *)(arg0 + 8) = *(u8 *)(arg0 + 8) + 1;
            }
            break;
        case 6:
            return 1; /* jtbl 0x36C528 -> 0x109D20: li v0,1 */
        default:
            break;
        }
    }
    if (*(s32 *)(arg0 + 0) != 0) {
        s32 (*fn)(s32) = (s32 (*)(s32))(u32)*(s32 *)(arg0 + 0);
        return fn(*(s32 *)(arg0 + 4)) != 0;
    }
    return 0;
}
