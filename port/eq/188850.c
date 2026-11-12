#include "common.h"

s32 func_001267E8(s32 arg0, s32 arg1);
void func_001895D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1);
void func_001899F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void func_00189C98(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);

void func_00188850(u8 *arg0) {
    u8 *s1;
    u8 *s0;
    s32 flags;

    s1 = *(u8 **)(arg0 + 0x38);
    s0 = *(u8 **)(s1 + 0x30);
    if (func_001267E8(*(s32 *)(s1 + 0xD0), *(u8 *)(s1 + 0x1DC)) != 0) {
        return;
    }
    flags = *(s32 *)(s0 + 0xA4);
    if (flags & 2) {
        if (flags & 0x18) {
            func_001899F0((s32)s1, ((flags >> 10) ^ 1) & 1, (flags >> 3) & 1, (flags >> 9) & 1,
                          *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
        } else {
            func_001895D8((s32)s1, ((flags >> 10) ^ 1) & 1, 0, 1, (flags >> 9) & 1,
                          *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
        }
    }
    flags = *(s32 *)(s0 + 0xA4);
    if (flags & 1) {
        if (flags & 0x20) {
            func_00189C98((s32)s1, ((flags >> 10) ^ 1) & 1, (flags >> 9) & 1,
                          *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
            return;
        }
        func_001895D8((s32)s1, ((flags >> 10) ^ 1) & 1, 1, 0, (flags >> 9) & 1,
                      *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
    }
}
