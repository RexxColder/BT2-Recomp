#include "common.h"

void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_001E70B0(f32 farg0, u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, u8 *arg6, s32 arg7);
void func_001E71D8(u8 *arg0, s32 arg1);
void func_001E7268(f32 farg0, u8 *arg1);
void func_001E7238(u8 *arg0, u8 *arg1);
extern f32 D_003848CC;
extern f32 D_003848D0;
extern f32 D_003848D4;

void func_00171838(u8 *arg0, u8 *arg1) {
    s32 sp[6];
    f32 f20;
    u8 *s0;
    u8 *s2;
    f32 t;

    s2 = *(u8 **)(arg1 + 0xB0);
    *(s32 *)(arg1 + 0xAB0) = *(s32 *)(arg1 + 0xAB0) + 1;
    if (*(s32 *)(*(u8 **)(s2 + 0x20)) == 0x175) {
        func_00208DE8(*(s32 *)s2, (u8 *)sp, 0x18);
        *(f32 *)((u8 *)sp + 4) = *(f32 *)((u8 *)sp + 4) - D_003848CC;
        if (*(s32 *)(arg1 + 0xAB0) == 0xA0) {
            f20 = D_003848D0;
            s0 = arg1 + 0xABC;
            func_001E70B0(f20, s0, *(s32 *)(arg0 + 0x658), 0, 0, 0, (u8 *)sp, arg0 + 0x680, *(s32 *)s2);
            *(f32 *)(arg1 + 0xAC0) = f20;
        } else {
            s0 = arg1 + 0xABC;
            if (*(s32 *)(arg1 + 0xAB0) > 0xA0) {
                t = *(f32 *)(arg1 + 0xAC0) + D_003848D4;
                *(f32 *)(arg1 + 0xAC0) = t;
                if (t > 1.0f) {
                    *(f32 *)(arg1 + 0xAC0) = 1.0f;
                }
            }
        }
        if (*(s32 *)(arg1 + 0xAB0) == 0xAF) {
            func_001E71D8(s0, 0);
        }
        func_001E7268(*(f32 *)(arg1 + 0xAC0), s0);
        func_001E7238(s0, (u8 *)sp);
    }
}
