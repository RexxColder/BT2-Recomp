#include "common.h"

extern s32 EftShot_TestBits(s32 a0, s32 a1);
extern void func_00153730(u8 *a0);
extern s32 func_00191728(s32 a0);

s32 func_001539D8(u8 *obj) {
    s32 alive = 0;
    s32 i;
    u8 *data;
    u8 *slot;

    data = *(u8 **)(obj + 0x38);
    if (EftShot_TestBits(**(s32 **)(data + 0xA0), 4) != 0) {
        func_00153730(obj);
        *(u32 *)data |= 0x200;
    }
    slot = data + 0xAA0;
    for (i = 4; i >= 0; i--) {
        if (func_00191728(*(s32 *)(slot + 4)) != 0) {
            alive = 1;
        } else {
            *(s32 *)(slot + 4) = 0;
        }
        slot += 8;
    }
    return alive;
}
