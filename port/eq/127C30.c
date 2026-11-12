#include "common.h"

s32 EftHit_GetHitCount(s32 arg0);
s32 EftHit_GetMaxHits(s32 arg0);
s32 EftHit_HasDefFlag20(s32 arg0);
f32 func_00272FA8(void);
void func_003126C8(s32 arg0, s32 arg1);

s32 func_00127C30(u8 *obj) {
    u8 *data;
    s32 result;
    s32 flags;
    s32 hitCount;
    s32 maxHits;
    f32 speed;
    f32 len;
    f32 sumSq;
    f32 a;
    f32 b;

    result = 0;
    data = *(u8 **)(obj + 0x60);
    flags = *(s32 *)(data + 0x4);
    if ((flags & 0x4) != 0) {
        result = 5;
    }
    if ((flags & 0x8000) != 0) {
        result = 1;
        flags = flags & 0xFFFF7FFF;
        *(s32 *)(data + 0x4) = flags;
    }

    flags = *(s32 *)(data + 0x4);
    if ((flags & 0x1) != 0) {
        if ((flags & 0x4000) != 0) {
            hitCount = EftHit_GetHitCount((s32)obj);
            maxHits = EftHit_GetMaxHits((s32)obj);
            if (maxHits < hitCount) {
                if (EftHit_HasDefFlag20((s32)obj) == 0) {
                    result = 5;
                }
            }
        } else {
            result = 4;
        }
    }

    flags = *(s32 *)(data + 0x4);
    if ((flags & 0x8) != 0) {
        result = 4;
    }
    if ((flags & 0x2) != 0 && (flags & 0x4000) == 0) {
        result = 5;
    }
    if ((flags & 0x20) != 0) {
        result = 5;
    }
    if ((flags & 0x100) != 0) {
        result = 3;
    }

    speed = func_00272FA8() + 0.0f;
    sumSq = *(f32 *)(obj + 0x20) * *(f32 *)(obj + 0x20) + *(f32 *)(obj + 0x28) * *(f32 *)(obj + 0x28);
    len = __builtin_sqrtf(__builtin_fabsf(sumSq));

    data = *(u8 **)(obj + 0x60);
    flags = *(s32 *)(data + 0x4);
    if ((flags & 0x4) != 0) {
        return result;
    }
    if (!(speed < len)) {
        return result;
    }
    if ((flags & 0x10) != 0) {
        return result;
    }

    result = 5;
    func_003126C8((s32)(data + 0x10), (s32)(obj + 0x20));

    data = *(u8 **)(obj + 0x60);
    a = *(f32 *)(data + 0x10);
    b = *(f32 *)(data + 0x18);
    sumSq = a * a + b * b;
    len = __builtin_sqrtf(__builtin_fabsf(sumSq));

    a = func_00272FA8();
    *(f32 *)(data + 0x10) = *(f32 *)(data + 0x10) * (a / len);
    b = func_00272FA8();
    data = *(u8 **)(obj + 0x60);
    *(f32 *)(data + 0x18) = *(f32 *)(data + 0x18) * (b / len);

    flags = *(s32 *)(data + 0x4);
    *(s32 *)(data + 0x4) = flags | 0x10;

    return result;
}
