#include "common.h"

void func_00113860(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, f32 farg0);
void func_00113D80(s32 arg0, s32 arg1);
void func_00113B00(s32 arg0, s32 arg1, s32 arg2);

f32 func_0010ED48(u8 *arg0, f32 farg0) {
    u8 *p;
    u8 *q;
    u8 *end;
    f32 t;
    s32 r;

    t = farg0 * 16.0f;
    func_00113860((s32)(arg0 + 0xC), 0xA0, 0, 0xB5, 0x10, 7, farg0);
    func_00113D80((s32)arg0, 0);
    func_00113B00((s32)arg0, 0x2E, 0x2A);

    end = arg0 + 0x60;
    p = arg0;
    q = arg0 + 0x120;
    do {
        *(s64 *)(q + 0x00) = *(s64 *)(p + 0x00);
        *(s64 *)(q + 0x08) = *(s64 *)(p + 0x08);
        *(s64 *)(q + 0x10) = *(s64 *)(p + 0x10);
        *(s64 *)(q + 0x18) = *(s64 *)(p + 0x18);
        p += 0x20;
        q += 0x20;
    } while (p != end);
    *(s32 *)(arg0 + 0x120) = *(s32 *)(arg0 + 0x120) | 0x10000;

    p = arg0;
    q = arg0 + 0xC0;
    do {
        *(s64 *)(q + 0x00) = *(s64 *)(p + 0x00);
        *(s64 *)(q + 0x08) = *(s64 *)(p + 0x08);
        *(s64 *)(q + 0x10) = *(s64 *)(p + 0x10);
        *(s64 *)(q + 0x18) = *(s64 *)(p + 0x18);
        p += 0x20;
        q += 0x20;
    } while (p != end);

    func_00113860((s32)(arg0 + 0xCC), 0xC0, 0, 0xD5, 0x10, 7, 0.0f);
    *(s32 *)(arg0 + 0xC0) = *(s32 *)(arg0 + 0xC0) | 0x80;

    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)t;
    *(u16 *)(arg0 + 0xC6) = (u16)(*(u16 *)(arg0 + 0xC6) - r);
    *(u16 *)(arg0 + 0xCA) = (u16)(*(u16 *)(arg0 + 0xCA) - r);
    return t;
}
