#include "common.h"

extern u8 *func_002BC170();

/* 0x002BBB10: looks up an entry from a0; if entry->+0xC (callback) is set, calls it with (a1, a2); else 0. */
s32 func_002BBB10(s32 key, s32 a1, s32 a2) {
    u8 *entry = func_002BC170(key);
    s32 ret = 0;

    if (entry != 0) {
        u8 *cb = *(u8 **)(entry + 0xC);
        if (cb != 0) {
            ret = ((s32 (*)(s32, s32))cb)(a1, a2);
        }
    }
    return ret;
}
