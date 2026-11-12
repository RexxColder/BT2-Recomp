#include "common.h"

extern u8 D_003B0B00[] __attribute__((section(".data")));

/* 0x0028C4B8(i): rec = D_003B0B00 + i * 0x180. Returns 1 only when the bytes are 0xF9 at +0x10C, 0xFF at +0x10D,
 * 0 at +0x10E and 0 at +0x10F; otherwise 0. */
s32 func_0028C4B8(s32 arg0) {
    u8 *rec = D_003B0B00 + arg0 * 0x180;

    if (rec[0x10C] != 0xF9) {
        return 0;
    }
    if (rec[0x10D] != 0xFF) {
        return 0;
    }
    if (rec[0x10E] != 0) {
        return 0;
    }
    return rec[0x10F] == 0;
}
