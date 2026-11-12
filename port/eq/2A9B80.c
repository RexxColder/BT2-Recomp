#include "common.h"

void func_00272CB0(s32 arg0, s32 arg1, s32 arg2);
void func_00261378(s32 arg0, s32 arg1);
void func_002613F8(s32 arg0, s32 arg1);
void func_0025B9C8(s32 arg0, s32 arg1, s64 arg2, s64 arg3);
void func_00261468(s32 arg0, s32 arg1, s32 arg2);
void func_002ADBD0(s32 arg0);
extern u8 D_003779E0[] __attribute__((section(".data")));
extern u8 D_003779F0[] __attribute__((section(".data")));
extern u8 *D_00387A40;
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002A9B80(void) {
    u8 sp[0x20];
    u8 *v1;
    s32 s0;
    s32 s1;
    s32 a0;

    s1 = 0;
    s0 = 0;
    *(s32 *)(D_003B2654 + 0x10) = 0;
    *(s32 *)(D_003B2654 + 0x50) = 0;
    do {
        v1 = (u8 *)(s32)(*(s32 *)(D_00387A40 + 8) + s1);
        s1 += 0x1520;
        if (s0 == 0) {
            func_00272CB0(0xD, (s32)sp, (s32)(sp + 0x10));
            func_00261378(0, (s32)sp);
            func_002613F8(0, (s32)(sp + 0x10));
        } else {
            *(s32 *)(v1 + 0xAF0) = *(s32 *)(v1 + 0xAF0) & ~2;
        }
        s0 += 1;
    } while (s0 < 3);

    *(s64 *)(sp + 0x0) = *(s64 *)(D_003779E0 + 0x0);
    *(s64 *)(sp + 0x8) = *(s64 *)(D_003779E0 + 0x8);
    *(s64 *)(sp + 0x10) = *(s64 *)(D_003779F0 + 0x0);
    *(s64 *)(sp + 0x18) = *(s64 *)(D_003779F0 + 0x8);
    func_0025B9C8((s32)sp, (s32)(sp + 0x10), *(s64 *)(D_003779E0 + 0x0), *(s64 *)(D_003779E0 + 0x8));
    func_00261468(0, 0x1D, 1);
    func_002ADBD0(1);

    a0 = 0;
    s0 = 9;
    do {
        v1 = (u8 *)(s32)(*(s32 *)(D_00387A40 + 8) + a0);
        a0 += 0x1520;
        if (*(s32 *)(v1 + 0xC) != 0 && (*(s32 *)(v1 + 0xAF0) & 2)) {
            *(s32 *)(v1 + 0x14) = 1;
        }
        s0 -= 1;
    } while (s0 >= 0);
}
