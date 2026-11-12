#include "common.h"

extern u8 D_00378410[] __attribute__((section(".data")));

s32 func_002B8280(void *arg0);
void Rand_Range(void *arg0, s32 arg1);
void func_002B5138(void *arg0, s32 arg1);
s32 func_002B7CB8(void *arg0);
void func_002CEFD0(s32 arg0, s32 *arg1);
s32 func_002B59A8(void *arg0);
void func_002CF0C8(s32 arg0, s32 arg1);
void func_002B55D8(void *arg0, s32 arg1);
void func_002B51D0(void *arg0, s32 arg1, void *arg2);
void func_002B5180(void *arg0, void *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_002B4FD0(void *arg0, void *arg1) {
    s32 sp[4];
    s32 s1, s3, s4;
    u8 *s0 = (u8 *)arg0;
    u8 *s2 = (u8 *)arg1;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_00378410, 1);
        goto block_2;
    }
    func_002B5138(arg0, 1);
    s1 = func_002B7CB8(arg0);
    if (s1 == 0) {
        goto block_2;
    }
    func_002CEFD0(s1, sp);
    if (sp[0] != 0) {
        if (*(s32 *)(s0 + 0x54) == 0) {
            s3 = 0;
            s4 = *(s32 *)(s0 + 0x18);
            while (s3 < s4) {
                s3 += 1;
                if (func_002B59A8(arg0) != 1) {
                    break;
                }
                func_002CF0C8(s1, sp[0]);
                *(s32 *)(s0 + 0x84) += 1;
                func_002CEFD0(s1, sp);
            }
        }
        if (sp[0] != 0) {
            *(s32 *)(s0 + 0x78) = sp[0];
            *(s32 *)(s0 + 0x7C) += 1;
            func_002B55D8(arg0, sp[0]);
            func_002B51D0(arg0, sp[0], arg1);
            *(s32 *)(s2 + 4) = *(s32 *)(s2 + 0x24);
            *(s32 *)(s0 + 0xB8) = *(s32 *)(s2 + 0x30);
            func_002B5180(arg0, arg1);
            return;
        }
    }
    *(s32 *)s2 = 0;
    return;
block_2:
    memset(arg1, 0, 0x90);
    *(s32 *)s2 = 0;
}
