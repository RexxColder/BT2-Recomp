#include "common.h"

extern f32 D_00383E30;

s32 func_00113860(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* 0x0010D548: a0 = obj, a1 = src (0x60 bytes), a2 = cfg (word at +0x69C), a3 = X, a4 = Y,
   a5 = shift B (srav of obj+0x199), a6 = shift A (srav of obj+0x79), a7 = OR mask for obj+0x180.
   f21 = X / 10000, f20 = Y / 10000. Returns (s32)(f21 * 143). */
s32 func_0010D548(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u8 *obj = (u8 *)arg0;
    u8 *src = (u8 *)arg1;
    f32 f21;
    f32 f20;
    s32 a1v;
    s32 t;

    f21 = (f32)arg3 / D_00383E30;
    f20 = (f32)arg4 / D_00383E30;

    if (*(s32 *)((u8 *)arg2 + 0x69C) != 0 && arg3 != arg4) {
        __builtin_memcpy(obj + 0x60, src, 0x60);
        func_00113860(arg0 + 0x6C, 0, 0, 0x9A, 0xC, 7);
        *(s32 *)(obj + 0x60) = 0x20001;
        obj[0x79] = (u8)((s32)obj[0x79] >> arg6);
        __builtin_memcpy(obj, src, 0x60);
        func_00113860(arg0 + 0xC, 0, 0x30, 0x9A, 0x3C, 7);
        *(s32 *)obj |= 0x80;
        a1v = (s32)(143.0f - f20 * 143.0f);
        *(u16 *)(obj + 0x4) = (u16)(*(u16 *)(obj + 0x4) + 143 - a1v);
        *(u16 *)(obj + 0x8) = (u16)(*(u16 *)(obj + 0x8) + 143 - a1v);
    }

    __builtin_memcpy(obj + 0x180, src, 0x60);
    func_00113860(arg0 + 0x18C, 0, 0, 0x9A, 0xC, 7);
    *(s32 *)(obj + 0x180) |= arg7;
    obj[0x199] = (u8)((s32)obj[0x199] >> arg5);
    __builtin_memcpy(obj + 0x120, src, 0x60);
    func_00113860(arg0 + 0x12C, 0, 0x30, 0x9A, 0x3C, 7);
    *(s32 *)(obj + 0x120) |= 0x80;
    t = (s32)(f21 * 143.0f);
    *(u16 *)(obj + 0x124) = (u16)(*(u16 *)(obj + 0x124) + t);
    *(u16 *)(obj + 0x128) = (u16)(*(u16 *)(obj + 0x128) + t);
    return t;
}
