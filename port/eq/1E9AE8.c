#include "common.h"

void func_0012A360(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
void func_001EA658(f32 farg0, f32 farg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_001E9AE8(u8 *arg0, s32 arg1) {
    s32 s1;
    s32 s2;

    s1 = (s32)(arg0 + 0xA0);
    s2 = (s32)(arg0 + 0x70);
    if (!(*(s32 *)(*(u8 **)arg0 + 0x98) & 0x80)) {
        *(f32 *)(arg0 + 0xC8) = *(f32 *)(arg0 + 0xC8) + *(f32 *)(arg0 + ((arg1 & 0xFF) * 4) + 0xCC);
    }
    func_001EA658(*(f32 *)(arg0 + 0xC8), 0.5f, s1, s2, s1, (s32)(arg0 + 0xB0));
    func_0012A360(*(f32 *)(arg0 + 0xC8), s2, s1, s2);
}
