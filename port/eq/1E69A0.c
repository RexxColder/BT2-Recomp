#include "common.h"

void func_001DFB40(f32 f12, s32 a0, s32 a1, s32 a2, void *a3);
void func_001E01B0(s32 a0);
void func_001E0880(f32 f12, s32 a0, s32 a1, s32 a2, s32 a3);
void func_001E0A00(s32 a0, void *a1);
void func_001E0C70(s32 a0);

void func_001E69A0(void *arg0, void *arg1) {
    u8 *s0;
    u8 *s1;
    s32 kind;

    s0 = (u8 *)arg1;
    s1 = (u8 *)arg0;
    kind = *(s32 *)(s1 + 8);
    if (kind == 0) {
        func_001DFB40(*(f32 *)(s0 + 0x10), *(s32 *)(s1 + 0x40), *(s32 *)(s0 + 0), *(s32 *)(s0 + 0x30), s0 + 0x20);
        func_001E01B0(*(s32 *)(s1 + 0x40));
    } else if (kind == 1) {
        func_001E0880(*(f32 *)(s0 + 0x10), *(s32 *)(s1 + 0x44), *(s32 *)(s0 + 4), *(s32 *)(s0 + 0x30), *(u8 *)(s0 + 8));
        func_001E0A00(*(s32 *)(s1 + 0x44), s0 + 0x20);
        func_001E0C70(*(s32 *)(s1 + 0x44));
    }
}
