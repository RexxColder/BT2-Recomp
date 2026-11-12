#include "common.h"

s32 func_002F95C8(s32 arg0);

/* 0x002FB108: p = func_002F95C8(arg0); if p is null return 0; fn = p->+0x60; if fn is null return 0;
 * otherwise return fn(0, 100, 0, 0). */
s32 func_002FB108(s32 arg0) {
    u8 *p = (u8 *)func_002F95C8(arg0);
    s32 fn;

    if (p == NULL) {
        return 0;
    }
    fn = *(s32 *)(p + 0x60);
    if (fn == 0) {
        return 0;
    }
    return ((s32 (*)(s32, s32, s32, s32))(u32)fn)(0, 100, 0, 0);
}
