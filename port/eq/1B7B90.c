#include "common.h"

s32 func_001B8088(s32 arg0);
s32 func_001B80F0(f32 farg0, s32 arg0);
void func_001B8510(s32 arg0, s32 arg1);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00312680(f32 farg0, void *arg1, void *arg2);
void func_003126C8(void *arg0, void *arg1);
void sceVu0Normalize(void *arg0, void *arg1);
extern f32 D_0038503C;
extern u8 *D_003876A0;

void func_001B7B90(void *arg0) {
    f32 buf[8];
    f32 *sp;
    f32 *sp10;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    f32 f20;
    s32 s2;
    s32 cnt;

    sp = buf;
    sp10 = buf + 4;
    s3 = *(u8 **)((u8 *)arg0 + 0x38);
    f20 = *(f32 *)(s3 + 0x48);
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    *(f32 *)(s3 + 0x54) = *(f32 *)(s3 + 0x54) + 1.0f;
    cnt = func_001B8088((s32)s3);
    if (cnt > 0) {
        s2 = cnt;
        do {
            s1 = (u8 *)func_001B80F0(1.0f, (s32)s3);
            s0 = s1 + 0x10;
            if (s1 != NULL) {
                func_00312650(sp10, s3, s1);
                sceVu0Normalize(sp10, sp10);
                func_003126C8(s0, sp10);
                func_00312680(*(f32 *)(s1 + 0x44), s1 + 0x20, s0);
            }
            s2 -= 1;
        } while (s2 != 0);
    }
    s1 = *(u8 **)(s3 + 0x68);
    s2 = 9;
    do {
        if (*(s32 *)(s1 + 0x5C) & 1) {
            s0 = s1 + 0x20;
            func_00312680(f20, s0, s0);
            func_00312680(D_0038503C, sp, s3 + 0x20);
            func_00312638(s0, s0, sp);
            func_00312638(s1, s1, s0);
            func_001B8510((s32)s3, (s32)s1);
        }
        s2 -= 1;
        s1 += 0x60;
    } while (s2 >= 0);
}
