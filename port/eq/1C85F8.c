#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))

void *memcpy(void *dst, const void *src, u32 n);
s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);

/* 0x001C85F8: copies the 16-byte vector at arg0 to a frame buffer and sets that buffer to one of seven preset
 * vectors chosen by arg1 (0..6); any other code sets (0, 0, 0, 0). */
void func_001C85F8(s32 arg0, s32 arg1) {
    u8 sp[0x10];
    s32 buf;

    memcpy(sp, PTR(arg0), 16);
    buf = (s32)(s32)sp;

    switch (arg1) {
    case 0:
        Vec4_Set(buf, 10.0f, 65.0f, 128.0f, 90.0f);
        break;
    case 1:
        Vec4_Set(buf, 65.0f, 20.0f, 128.0f, 90.0f);
        break;
    case 2:
        Vec4_Set(buf, 128.0f, 80.0f, 10.0f, 90.0f);
        break;
    case 3:
        Vec4_Set(buf, 128.0f, 40.0f, 10.0f, 90.0f);
        break;
    case 4:
        Vec4_Set(buf, 10.0f, 123.0f, 75.0f, 90.0f);
        break;
    case 5:
        Vec4_Set(buf, 55.0f, 86.0f, 128.0f, 90.0f);
        break;
    case 6:
        Vec4_Set(buf, 128.0f, 60.0f, 128.0f, 90.0f);
        break;
    default:
        Vec4_Set(buf, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
}
