#include "common.h"

extern s32 func_00211418(u8 *obj, s32 flags);

/* 0x002198A8: key 0x10 -> ++obj->+0x9A0 and tail call func_00211418(obj, 0x2000); key 0x70 -> ++obj->+0x9A8 (returns it); else returns the key. */
s32 func_002198A8(u8 *obj, s32 key) {
    s32 v;

    if (key == 0x10) {
        *(s32 *)(obj + 0x9A0) = *(s32 *)(obj + 0x9A0) + 1;
        return func_00211418(obj, 0x2000);
    }
    if (key == 0x70) {
        v = *(s32 *)(obj + 0x9A8) + 1;
        *(s32 *)(obj + 0x9A8) = v;
        return v;
    }
    return 0x70;
}
