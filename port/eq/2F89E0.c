#include "common.h"

s32 func_002F4590(u8 *arg0);
s32 func_002F1ED0(s32 arg0);
void func_002F0420(s32 arg0);

/* 0x002F89E0(obj): nothing when obj->+8 is 0 or func_002F4590(obj) is 0; else on the signed byte mode = obj->+2:
 * 0 and 1 call func_002F0420(obj->+4) when func_002F1ED0(obj->+8) == 3; 2 calls func_002F0420(obj->+4); 3, 4 and
 * the modes outside 0..4 do nothing (jump table jtbl_0037D060). */
void func_002F89E0(u8 *arg0) {
    s32 mode;

    if (*(s32 *)(arg0 + 8) == 0) {
        return;
    }
    if (func_002F4590(arg0) == 0) {
        return;
    }
    mode = (s8)arg0[2];
    if ((u32)mode >= 5U) {
        return;
    }
    switch (mode) {
    case 0:
    case 1:
        if (func_002F1ED0(*(s32 *)(arg0 + 8)) == 3) {
            func_002F0420(*(s32 *)(arg0 + 4));
        }
        return;
    case 2:
        func_002F0420(*(s32 *)(arg0 + 4));
        return;
    default:
        return;
    }
}
