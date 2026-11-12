#include "common.h"

extern s32 func_001F9758(u8 *obj);

/* 0x0023F9C0: (obj->+0x1530->+0x958->+0x70) / 30 + func_001F9758(obj) + obj->+0xAEC. */
s32 func_0023F9C0(u8 *obj) {
    u8 *a = *(u8 **)(obj + 0x1530);
    u8 *b = *(u8 **)(a + 0x958);
    s32 q = *(s32 *)(b + 0x70) / 30;
    s32 r = func_001F9758(obj);

    return q + r + *(s32 *)(obj + 0xAEC);
}
