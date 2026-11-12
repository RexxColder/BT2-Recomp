#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00129C38(void *arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
s32 func_001CC978(void *arg0);
void func_001CCC68(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0019BEE8(u8 *arg0) {
    s32 fr[0x30];
    u8 *fp = (u8 *)fr;
    u8 *s0, *s2, *s1;
    s32 *s3;
    s32 s5, i, v;

    s0 = *(u8 **)(arg0 + 0x38);
    s3 = (s32 *)(s0 + 0x34);
    s2 = *(u8 **)s0;
    s1 = s0;
    *(s32 *)(fp + 0x40) = *(s32 *)(s0 + 0x80);
    *(s32 *)(fp + 0x44) = (s32)s2[0x23];
    *(f32 *)(fp + 0x48) = *(f32 *)(s2 + 0x18);
    *(f32 *)(fp + 0x4C) = *(f32 *)(s2 + 0x1C);
    memset(fp + 0x50, 0, 0x10);
    memset(fp + 0x60, 0, 0x10);
    *(s32 *)(fp + 0x70) = *(s32 *)(s0 + 0x28);
    *(s32 *)(fp + 0x74) = *(s32 *)(s0 + 0x2C);
    *(s32 *)(fp + 0x78) = *(s32 *)(s0 + 0x30);
    for (i = 0; i < 16; i++) {
        fr[i] = fr[16 + i];
    }
    s5 = 1;
    do {
        func_00129C38(fp + 0x10, s1 + 0x40);
        func_00129C38(fp + 0x20, s1 + 0x60);
        s1 += 0x10;
        if (s2[0x27] == 0) {
            func_00129BD0(fp + 0x20, fp + 0x20, -1.0f);
        }
        s5 -= 1;
        v = func_001CC978(fp);
        *s3 = v;
        s3 += 1;
        func_001CCC68(v, *(s32 *)(s0 + 0x28), (s32)s2[0x23],
                      (s32)s2[0x23] + *(s32 *)(s0 + 0x84));
    } while (s5 >= 0);
}
