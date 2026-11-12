#include "common.h"

void func_00129C28(void *arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);

void func_00171380(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s3;
    s32 v;

    s0 = arg0 + 0x50;
    s3 = *(u8 **)(arg0 + 0xB0);
    s1 = arg0 + 0x70;

    if (**(s32 **)(s3 + 0x20) == 0x174) {
        v = *(s32 *)(arg0 + 0x8B0);
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) | 0x10;
        *(s32 *)(arg0 + 8) = v;
        func_00208DE8(*(s32 *)s3, s0, v);
        func_00129C28(s1, s0);
        func_00129C28(arg0 + 0x80, s1);
        func_00208DE8(*(s32 *)s3, arg0 + 0x90, 0x11);
        return;
    }
    if (**(s32 **)(s3 + 0x20) == 0x175) {
        v = *(s32 *)(arg0 + 0x8B0);
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) | 0x10;
        *(s32 *)(arg0 + 8) = v;
        func_00208DE8(*(s32 *)s3, s0, v);
        *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) - 80.0f;
        func_00129C28(s1, s0);
        func_00129C28(arg0 + 0x80, s1);
        func_00208DE8(*(s32 *)s3, arg0 + 0x90, 0x11);
        return;
    }
}
