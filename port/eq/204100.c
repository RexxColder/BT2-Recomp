#include "common.h"

extern f32 D_00385900;
extern f32 D_00385904;
s32 func_0023F410();
void EftGlow_Request(s32 arg0, s32 arg1);
s32 EftAura_Command(s32 arg0, s32 arg1);
void *BtlChar_GetPos(s32 arg0);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00283770(s32 arg0, s32 arg1, s32 arg2);

s32 func_00204100(s32 arg0) {
    u8 *self;
    u64 cur;
    u64 prev;
    u64 released;
    u64 pressed;
    s32 ret;
    s32 obj;
    f32 x;

    self = (u8 *)arg0;
    cur = *(u64 *)(self + 0x338);
    prev = *(u64 *)(self + 0x400);
    released = prev & ~cur;
    pressed = cur & ~prev;

    ret = func_0023F410(arg0, ~prev);
    if ((ret & 0x10) == 0) {
        obj = *(s32 *)(self + 0x1534);
        if (cur & 0x20) {
            EftGlow_Request(obj, 2);
            EftAura_Command(obj, 5);
        } else {
            if (pressed & 8) {
                EftGlow_Request(obj, 0);
                EftAura_Command(obj, 6);
            }
            if (released & 8) {
                EftGlow_Request(obj, 1);
                EftAura_Command(obj, 5);
            }
        }
    }

    if (cur & 0x400) {
        x = *(f32 *)(self + 0x900) + D_00385900;
        *(f32 *)(self + 0x900) = x;
        if (1.0f < x) {
            *(f32 *)(self + 0x900) = 1.0f;
        }
    } else if (cur & 0x800) {
        *(f32 *)(self + 0x900) = 1.0f;
    } else {
        x = *(f32 *)(self + 0x900) - D_00385904;
        *(f32 *)(self + 0x900) = x;
        if (x < 0.0f) {
            *(f32 *)(self + 0x900) = 0.0f;
        }
    }

    x = *(f32 *)(self + 0x900);
    obj = *(s32 *)(self + 0x1538);
    func_002837C0(obj, 0x80, 0x80, 0x80, ((s32)(x * 8.0f)) & 0xFF);
    obj = *(s32 *)(self + 0x1538);
    func_00283800(obj, 0x80, 0x80, 0x80, ((s32)(x * 32.0f)) & 0xFF);
    obj = *(s32 *)(self + 0x1538);
    func_00283840(obj, 0x80, 0x80, 0x80, ((s32)(x * 128.0f)) & 0xFF);

    if (cur & 0x400) {
        obj = *(s32 *)(self + 0x1538);
        return func_00283770(obj, (s32)((u8 *)BtlChar_GetPos(arg0) + 0x20), 0);
    }
    return 0;
}
