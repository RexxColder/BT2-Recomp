#include "common.h"

void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
void func_00113B00(u8 *arg0, s32 arg1, s32 arg2);

/* Builds the shadow/outline copies of a 0x60-byte sprite block. */
s32 func_0010DEA8(u8 *obj, u8 *ctx, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8, s32 mask) {
    f32 fa = (f32)a2 / (f32)a7;
    f32 fb = (f32)a3 / (f32)a7;
    f32 fc = (f32)a4 / (f32)a8;
    s32 off;
    s32 v;

    func_00113860(obj + 0xC, 0, 0x20, 0x1D, 0x27, 7);
    func_00113D80(obj, 0);
    func_00113B00(obj, a5, a6);

    if (a2 == 0 && a3 == 0) {
        v = *(s32 *)obj | mask;
        *(s32 *)obj = v;
        return v;
    }
    if (*(s32 *)(ctx + 0x6C4) != 0 && a2 != a3 && a3 != 0) {
        __builtin_memcpy(obj + 0x120, obj, 0x60);
        *(s32 *)(obj + 0x120) |= 0x20000;
        __builtin_memcpy(obj + 0xC0, obj, 0x60);
        *(s32 *)(obj + 0xC0) |= 0x80;
        off = (s32)(23.0f - fb * 23.0f);
        *(u16 *)(obj + 0xC4) = *(u16 *)(obj + 0xC4) + 0x17 - off;
        *(u16 *)(obj + 0xC8) = *(u16 *)(obj + 0xC8) + 0x17 - off;
    }
    if (a4 != 0) {
        __builtin_memcpy(obj + 0x360, obj, 0x60);
        *(s32 *)(obj + 0x360) |= 0x100000;
        __builtin_memcpy(obj + 0x300, obj, 0x60);
        *(s32 *)(obj + 0x300) |= 0x80;
        off = (s32)(23.0f - fc * 23.0f);
        *(u16 *)(obj + 0x304) = *(u16 *)(obj + 0x304) + 0x17 - off;
        *(u16 *)(obj + 0x308) = *(u16 *)(obj + 0x308) + 0x17 - off;
    }
    __builtin_memcpy(obj + 0x240, obj, 0x60);
    *(s32 *)(obj + 0x240) |= 0x10000;
    __builtin_memcpy(obj + 0x1E0, obj, 0x60);
    *(s32 *)(obj + 0x1E0) |= 0x80;
    off = (s32)(23.0f - fa * 23.0f);
    v = *(s32 *)obj | mask;
    *(s32 *)obj = v;
    *(u16 *)(obj + 0x1E4) = *(u16 *)(obj + 0x1E4) + 0x17 - off;
    *(u16 *)(obj + 0x1E8) = *(u16 *)(obj + 0x1E8) + 0x17 - off;
    return v;
}
