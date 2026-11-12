#include "common.h"

s32 func_001F3758(void *a0);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void func_00208F18(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
s32 func_00157878(s32 arg0);
s32 func_00191600(s32 arg0);
s32 func_001918F8(s32 arg0, s32 arg1);

/* Spawns up to two blast objects for the object at arg0: each gets a 48-byte descriptor built on the frame
 * (owner, a 0x200000002 pair, a flag word, a float scale and a float radius) and is linked into the slot
 * returned by func_00157878. Returns the second slot pointer when no second blast is made. */
s32 func_00158328(s32 arg0) {
    u8 sp[0x140];
    s32 v1 = func_001F3758((void *)arg0);
    s32 s3 = arg0;
    s32 s4 = *(s32 *)(s3 + 0xA0);
    s32 s6 = *(s32 *)(v1 + 0x38);
    s32 s5 = s3 + 0x20;
    s32 s2 = s3 + 0x60;
    s32 s0;
    s32 s1;
    s32 v8;
    s32 v11;

    func_0012D3A0(s5, s2, *(s32 *)s4);
    func_00208F18(*(s32 *)s4, (s32)(sp + 0x30), 49);
    func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x30), 1.0f);
    Vec3_Add((s32)(sp + 0), s2, (s32)(sp + 0x20));
    func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x30), -1.0f);
    Vec3_Add((s32)(sp + 0x10), s2, (s32)(sp + 0x20));

    s0 = func_00157878(s3);
    v8 = s3 + 0xAA0;
    if (s0 != 0) {
        *(s32 *)(sp + 0xA0) = s4;
        *(s32 *)(sp + 0xA4) = s6;
        *(s32 *)(sp + 0xA8) = v8;
        *(s32 *)(sp + 0xAC) = (s32)sp;
        *(s32 *)(sp + 0xB0) = s5;
        *(s32 *)(sp + 0xB4) = 0;
        *(s32 *)(sp + 0xB8) = 2;
        *(s32 *)(sp + 0xBC) = 2;
        *(s32 *)(sp + 0xC0) = 1;
        *(s32 *)(sp + 0xC4) = 0;
        *(f32 *)(sp + 0xC8) = *(f32 *)(s3 + 0x1C);
        *(f32 *)(sp + 0xCC) = *(f32 *)(*(s32 *)(s4 + 0x24) + 8);
        __builtin_memcpy(sp + 0x70, sp + 0xA0, 48);
        *(s32 *)(s0 + 4) = func_00191600((s32)(sp + 0x70));
        func_001918F8(*(s32 *)(s0 + 4), 1);
    }

    s1 = func_00157878(s3);
    v11 = s1;
    if (v11 == 0) {
        return s3 + 0xCF0;
    }
    *(s32 *)(sp + 0xD0) = s4;
    *(s32 *)(sp + 0xD4) = s6;
    *(s32 *)(sp + 0xD8) = s3 + 0xCF0;
    *(s32 *)(sp + 0xDC) = (s32)(sp + 0x10);
    *(s32 *)(sp + 0xE0) = s5;
    *(s32 *)(sp + 0xE4) = 0;
    *(s32 *)(sp + 0xE8) = 2;
    *(s32 *)(sp + 0xEC) = 2;
    *(s32 *)(sp + 0xF0) = 1;
    *(s32 *)(sp + 0xF4) = 0;
    *(f32 *)(sp + 0xF8) = *(f32 *)(s3 + 0x1C);
    *(f32 *)(sp + 0xFC) = *(f32 *)(*(s32 *)(s4 + 0x24) + 8);
    __builtin_memcpy(sp + 0xA0, sp + 0xD0, 48);
    *(s32 *)(v11 + 4) = func_00191600((s32)(sp + 0xA0));
    return func_001918F8(*(s32 *)(v11 + 4), 1);
}
