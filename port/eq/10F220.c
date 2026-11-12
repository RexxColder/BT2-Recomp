#include "common.h"

extern s32 func_0020C688(s32 a0);
extern s32 func_0020C6D0(s32 a0);

s32 func_0010F220(u8 *obj, s32 arg) {
    s32 v;

    func_0020C688(arg);
    *(s32 *)(obj + 0x744) = 1;
    if (func_0020C6D0(arg) != 0) {
        *(s32 *)(obj + 0x744) = 0;
    }
    v = *(s32 *)(obj + 0x748);
    if (*(s32 *)(obj + 0x744) != 0) {
        v += 0x40;
        *(s32 *)(obj + 0x748) = v;
        if (v > 0) {
            *(s32 *)(obj + 0x748) = 0;
        }
        return v;
    }
    v -= 0x40;
    *(s32 *)(obj + 0x748) = v;
    if (v < -0x100) {
        v = -0x100;
        *(s32 *)(obj + 0x748) = v;
    }
    return v;
}
