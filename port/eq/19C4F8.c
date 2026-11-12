#include "common.h"

extern void func_001EC328(u8 *arg0, s32 arg1);
extern void func_00129C28(void *arg0, void *arg1);
extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern f32 Mathf_Asin(f32 farg0);
extern f32 EftMath_WrapAngle(f32 farg0);
extern f32 atan2f(f32 y, f32 x);
extern void func_0014EAE8(s32 arg0, u8 *arg1);

s32 func_0019C4F8(u8 *arg0, u8 *src) {
    u8 *dst;
    u8 *base;
    u8 *ent;
    u8 *prm;
    u8 *p;
    s32 i;
    f32 len;
    f32 a;
    f32 b;

    f32 zero;

    dst = *(u8 **)(arg0 + 0x38);
    prm = src + 0x14;
    __builtin_memset(dst, 0, 0xC30);
    func_001EC328(dst + 0xAB0, *(s32 *)src);
    base = *(u8 **)(*(u8 **)src + 0x48);
    if (*(s32 *)(base + 0x200) > 0) {
        ent = base;
        p = dst;
        i = 0;
        do {
            i++;
            __builtin_memcpy(p + 0x50, ent, 16);
            __builtin_memcpy(p + 0x60, ent, 16);
            ent += 16;
            p += 0x20;
        } while (i < *(s32 *)(base + 0x200));
    }
    func_00129C28(dst + 0xB40, src + 0x40);
    func_00129C28(dst + 0xB30, src + 0x40);
    func_00208DE8(*(s32 *)(src + 0x80), dst + 0xB50, 0x11);
    func_00129C28(dst + 0xB70, dst + 0xB50);
    func_00129C28(dst + 0xB60, src + 0x50);
    func_00129C28(dst + 0xBC0, src + 0x30);
    *(f32 *)(dst + 0xBFC) = *(f32 *)(src + 0x70);
    *(f32 *)(dst + 0xBF8) = *(f32 *)(src + 0x74);
    *(f32 *)(dst + 0xC00) = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(src + 0x54)));
    *(f32 *)(dst + 0xC04) = EftMath_WrapAngle(atan2f(*(f32 *)(src + 0x50), *(f32 *)(src + 0x58)));
    *(f32 *)(dst + 0xC08) = EftMath_WrapAngle(atan2f(*(f32 *)(src + 0x60), -*(f32 *)(src + 0x64)));
    *(s32 *)(dst + 0xC14) = *(s32 *)(src + 0x78);
    *(s32 *)(dst + 0xC18) = *(s32 *)(src + 0x7C);
    *(s32 *)(dst + 0xC1C) = *(s32 *)(src + 0x80);
    *(f32 *)(dst + 0xC10) = *(f32 *)(src + 0x20) * 30.0f;
    __builtin_memcpy(dst + 0xA90, prm, 0x1C);
    *(s32 *)dst = *(s32 *)(src + 0xC);
    a = *(f32 *)(dst + 0xBCC);
    len = *(f32 *)(dst + 0xC10);
    *(f32 *)(dst + 0xBE4) = a / *(f32 *)prm;
    *(s32 *)(dst + 0xBCC) = 0;
    *(f32 *)(dst + 0xBE8) = a / *(f32 *)(src + 0x18);
    zero = *(f32 *)(dst + 0xBCC);
    *(f32 *)(dst + 0xBE0) = len - *(f32 *)(src + 0x18);
    *(f32 *)(dst + 0xBF0) = (*(f32 *)(prm + 0x14) - *(f32 *)(prm + 0x10)) / (len * *(f32 *)(prm + 8));
    *(f32 *)(dst + 0xBF4) = (*(f32 *)(prm + 0x18) - *(f32 *)(prm + 0x14)) / (len * (1.0f - *(f32 *)(prm + 8)));
    b = *(f32 *)(prm + 0x10);
    *(f32 *)(dst + 0xBEC) = b;
    if (b <= zero) {
        *(f32 *)(dst + 0xBEC) = 1.0f;
    }
    if (*(s32 *)dst != 0) {
        func_0014EAE8(*(s32 *)dst, dst + 0x90);
    }
    p = *(u8 **)(src + 0x10);
    if (p != 0) {
        __builtin_memcpy(dst + 0x840, p, 0x250);
    }
    *(s32 *)(dst + 4) = *(s32 *)(src + 8);
    p = *(u8 **)(src + 4);
    if (p != 0) {
        __builtin_memcpy(dst + 0x10, p, 0x40);
    }
    *(s16 *)(dst + 0xC24) = 0x201;
    if (*(s32 *)dst != 0 && *(s32 *)(dst + 4) != 0) {
        *(s16 *)(dst + 0xC24) = 0x241;
    }
    return *(s32 *)dst == 0 ? 0x201 : 0x241;
}
